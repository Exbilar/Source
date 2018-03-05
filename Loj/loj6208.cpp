#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int fst[maxm],nxt[maxm],to[maxm];
LL tagv[maxm],tagt[maxm],valv[maxm],valvi[maxm],valt[maxm];
int size[maxm],dpt[maxm],ftr[maxm],son[maxm],top[maxm],pos[maxm];
int n,m,cnt,sz;

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
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
		if(to[u] != ftr[x] && to[u] != son[x]) dfs2(to[u],to[u]);
}

void pushtag(int x,int fa){
	valt[x] += valt[fa] + tagt[fa] * valv[x];
	valvi[x] += tagv[fa];
	tagv[x] += tagv[fa],tagt[x] += tagt[fa];
}

void pushdown(int x){
	pushtag(x << 1,x),pushtag(x << 1 | 1,x);
	tagv[x] = 0,tagt[x] = 0,valt[x] = 0;
}

void _pushdown(int x){
	int lc = x << 1,rc = x << 1 | 1;
	valt[lc] += valt[x] + tagt[x] * valv[lc];
	valt[rc] += valt[x] + tagt[x] * valv[rc];
	valvi[lc] += tagv[x],valvi[rc] += tagv[x];
	tagv[lc] += tagv[x],tagv[rc] += tagv[x];
	tagt[lc] += tagt[x],tagt[rc] += tagt[x];
	tagt[x] = 0,tagv[x] = 0,valt[x] = 0;
}

void modify_v(int x,int l,int r,int L,int R,int v){
	if(l >= L && r <= R){
		tagv[x] += v,valv[x] += v,valvi[x] += v;
		return ;
	}
	_pushdown(x);
	int mid = (l + r) >> 1;
	if(l != r) pushdown(x);
	if(L <= mid) modify_v(x << 1,l,mid,L,R,v);
	if(R > mid) modify_v(x << 1 | 1,mid + 1,r,L,R,v);
}

void modify_t(int x,int l,int r,int L,int R,int v){
	if(l >= L && r <= R){
		tagt[x] += v,valt[x] += valvi[x] * v;
		return ;
	}
	_pushdown(x);
	int mid = (l + r) >> 1;
	if(l != r) pushdown(x);
	if(L <= mid) modify_t(x << 1,l,mid,L,R,v);
	if(R > mid) modify_t(x << 1 | 1,mid + 1,r,L,R,v);
}

void solve(int x,int y,int v,int opt){
	while(top[x] != top[y]){
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		if(opt == 1) modify_v(1,1,n,pos[top[x]],pos[x],v);
		if(opt == 2) modify_t(1,1,n,pos[top[x]],pos[x],v);
		x = ftr[top[x]];
	}
	if(pos[x] > pos[y]) std :: swap(x,y);
	if(opt == 1) modify_v(1,1,n,pos[x],pos[y],v);
	if(opt == 2) modify_t(1,1,n,pos[x],pos[y],v);	
}

LL Qry(int x,int l,int r,int pos){
	if(l == r) return valt[x];
	_pushdown(x);
	int mid = (l + r) >> 1;
	if(pos <= mid) return Qry(x << 1,l,mid,pos);
	else return Qry(x << 1 | 1,mid + 1,r,pos);
}

int main(){
	
	int x,y,opt;
	scanf("%d",&n);
	for(int i = 1;i < n;i++) scanf("%d%d",&x,&y),ins(x,y);	
	
	dfs1(1),dfs2(1,1);

	scanf("%d",&m);
	
	while(m--){
		scanf("%d",&opt);
		if(opt == 1) scanf("%d%d",&x,&y),solve(1,x,y,opt);
		if(opt == 2) scanf("%d%d",&x,&y),solve(1,x,y,opt);
		if(opt == 3) scanf("%d",&x),printf("%lld\n",Qry(1,1,n,pos[x]));
	}
	
	return 0;
}
