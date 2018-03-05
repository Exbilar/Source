#include <cstdio>
#include <algorithm>

static const int maxm = 2e6 + 10;
static const int INF = 1 << 29;

int nxt[maxm],fst[maxm],to[maxm],ftr[maxm],top[maxm],son[maxm],pos[maxm];
int same[maxm],tag[maxm],ct[maxm],smin[maxm],size[maxm],dpt[maxm];
int sz,cnt,n,m;

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
}

void dfs1(int x){
	size[x] = 1;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == ftr[x]) continue;
		ftr[v] = x,dpt[v] = dpt[x] + 1;
		dfs1(v);
		size[x] += size[v];
		if(size[son[x]] < size[v]) son[x] = v;
	}
}

void dfs2(int x,int chain){
	pos[x] = ++sz,top[x] = chain;
	if(son[x]) dfs2(son[x],chain);
	for(int u = fst[x];u;u = nxt[u])
		if(to[u] != son[x] && to[u] != ftr[x]) dfs2(to[u],to[u]);
}

void pushup(int x){
	int lc = x << 1,rc = x << 1 | 1;
	smin[x] = std :: min(smin[lc],smin[rc]),ct[x] = 0;
	if(smin[x] == smin[lc]) ct[x] += ct[lc];
	if(smin[x] == smin[rc]) ct[x] += ct[rc];
}

void pushdown(int x,int l,int r){
	int lc = x << 1,rc = x << 1 | 1,mid = (l + r) >> 1;
	if(same[x] != -1){
		tag[lc] = tag[rc] = 0;
		smin[lc] = smin[rc] = same[x];
		ct[lc] = mid - l + 1,ct[rc] = r - mid;
		same[lc] = same[rc] = same[x],same[x] = -1;
	}
	if(tag[x]){
		smin[lc] += tag[x],smin[rc] += tag[x];
		tag[lc] += tag[x],tag[rc] += tag[x],tag[x] = 0;
	}
}

void build(int x,int l,int r){
	same[x] = -1;
	if(l == r) return smin[x] = 0,ct[x] = 1,void();
	int mid = (l + r) >> 1;
	build(x << 1,l,mid);
	build(x << 1 | 1,mid + 1,r);
	pushup(x);
}

void modify(int x,int l,int r,int L,int R,int v,int f){
	if(l >= L && r <= R){
		if(f == 1) tag[x] = 0,smin[x] = v,same[x] = v,ct[x] = r - l + 1;
		if(f == 2) tag[x] += v,smin[x] += v;
		return;
	}
	pushdown(x,l,r);
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1,l,mid,L,R,v,f);
	if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,v,f);
	pushup(x);
}

int Qry_smin(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return smin[x];
	pushdown(x,l,r);
	int mid = (l + r) >> 1,ret = INF;
	if(L <= mid) ret = std :: min(ret,Qry_smin(x << 1,l,mid,L,R));
	if(R > mid) ret = std :: min(ret,Qry_smin(x << 1 | 1,mid + 1,r,L,R));
	return ret;
}

int Qry_ct(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return smin[x] == 0 ? ct[x] : 0;
	pushdown(x,l,r);
	int mid = (l + r) >> 1,ret = 0;
	if(L <= mid) ret += Qry_ct(x << 1,l,mid,L,R);
	if(R > mid) ret += Qry_ct(x << 1 | 1,mid + 1,r,L,R);
	return ret;
}

int solve_Qry_smin(int x,int y){
	int ret = INF;
	while(top[x] != top[y]){
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		ret = std :: min(ret,Qry_smin(1,1,n,pos[top[x]],pos[x]));
		x = ftr[top[x]];
	}
	if(pos[x] > pos[y]) std :: swap(x,y);
	if(x != y) ret = std :: min(ret,Qry_smin(1,1,n,pos[x] + 1,pos[y]));
	return ret;
}

void solve_modify(int x,int y,int v,int f){
	if(f == 2){
		int tmp = solve_Qry_smin(x,y);
		if(tmp + v < 0) v = -tmp;
	}
	while(top[x] != top[y]){
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		modify(1,1,n,pos[top[x]],pos[x],v,f);
		x = ftr[top[x]];
	}
	if(pos[x] > pos[y]) std :: swap(x,y);
	if(x != y) modify(1,1,n,pos[x] + 1,pos[y],v,f);
}

int main(){
	int x,y,opt,v;
	scanf("%d%d",&n,&m);
	for(int i = 1;i < n;i++) scanf("%d%d",&x,&y),ins(x,y),ins(y,x);
	dfs1(1),dfs2(1,1);
	build(1,1,n);
	while(m--){
		scanf("%d%d%d%d",&opt,&x,&y,&v);
		if(opt == 1) solve_modify(x,y,v,opt);
		if(opt == 2) solve_modify(x,y,v,opt);
		printf("%d\n",Qry_ct(1,1,n,2,n));
	}

	return 0;
}
