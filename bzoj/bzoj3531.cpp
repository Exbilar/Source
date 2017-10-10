#include <cstdio>
#include <algorithm>

static const int maxm = 2e5 + 10;
static const int maxn = 2e6 + 10;
static const int INF = ~(1 << 31);

int dpt[maxm],size[maxm],pos[maxm],ftr[maxm],son[maxm],top[maxm];
int fst[maxm],nxt[maxm],to[maxm];
int lc[maxn],rc[maxn],sum[maxn],rt[maxm],smax[maxn],W[maxm],C[maxm];
char opt[10];
int cnt,sz,num,n,m;

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
		dpt[v] = dpt[x] + 1,ftr[v] = x;
		dfs1(v);
		size[x] += size[v];
		if(size[v] > size[son[x]]) son[x] = v;
	}
}

void dfs2(int x,int chain){
	pos[x] = ++sz,top[x] = chain;
	if(son[x]) dfs2(son[x],chain);
	for(int u = fst[x];u;u = nxt[u])
		if(to[u] != ftr[x] && to[u] != son[x]) dfs2(to[u],to[u]);
}

void pushup(int x){
	int ls = lc[x],rs = rc[x];
	sum[x] = sum[ls] + sum[rs];
	smax[x] = std :: max(smax[ls],smax[rs]);
}

void modify(int &x,int l,int r,int pos,int v){
	if(!x) x = ++num;
	if(l == r) return smax[x] = sum[x] = v,void();
	int mid = (l + r) >> 1;
	if(pos <= mid) modify(lc[x],l,mid,pos,v);
	else modify(rc[x],mid + 1,r,pos,v);
	pushup(x);
}

int Qrysum(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return sum[x];
	int mid = (l + r) >> 1,ret = 0;
	if(L <= mid && lc[x]) ret += Qrysum(lc[x],l,mid,L,R);
	if(R > mid && rc[x]) ret += Qrysum(rc[x],mid + 1,r,L,R);
	return ret;
}

int Qrymax(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return smax[x];
	int mid = (l + r) >> 1,ret = -INF;
	if(L <= mid && lc[x]) ret = std :: max(ret,Qrymax(lc[x],l,mid,L,R));
	if(R > mid && rc[x]) ret = std :: max(ret,Qrymax(rc[x],mid + 1,r,L,R));
	return ret;
}

int solve_max(int root,int x,int y){
	int ret = -INF;
	while(top[x] != top[y]){
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		ret = std :: max(ret,Qrymax(root,1,n,pos[top[x]],pos[x]));
		x = ftr[top[x]];
	}
	if(pos[x] > pos[y]) std :: swap(x,y);
	ret = std :: max(ret,Qrymax(root,1,n,pos[x],pos[y]));
	return ret;
}

int solve_sum(int root,int x,int y){
	int ret = 0;
	while(top[x] != top[y]){
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		ret += Qrysum(root,1,n,pos[top[x]],pos[x]);
		x = ftr[top[x]];
	}
	if(pos[x] > pos[y]) std :: swap(x,y);
	ret += Qrysum(root,1,n,pos[x],pos[y]);
	return ret;
}

int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d%d",&W[i],&C[i]);
	for(int i = 1;i < n;i++) scanf("%d%d",&x,&y),ins(x,y),ins(y,x);
	
	dfs1(1);
	dfs2(1,1);
	
	for(int i = 1;i <= n;i++) modify(rt[C[i]],1,n,pos[i],W[i]);
	
	while(m--){
		scanf("%s%d%d",opt,&x,&y);
		if(opt[0] == 'C' && opt[1] == 'C'){
			modify(rt[C[x]],1,n,pos[x],0);
			C[x] = y;
			modify(rt[C[x]],1,n,pos[x],W[x]);
		}
		if(opt[0] == 'C' && opt[1] == 'W') W[x] = y,modify(rt[C[x]],1,n,pos[x],y);
		if(opt[0] == 'Q' && opt[1] == 'S') printf("%d\n",solve_sum(rt[C[x]],x,y));
		if(opt[0] == 'Q' && opt[1] == 'M') printf("%d\n",solve_max(rt[C[x]],x,y));
	}
	

	return 0;
}
