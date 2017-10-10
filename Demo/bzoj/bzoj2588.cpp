#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int pos[maxm],top[maxm],dpt[maxm],size[maxm],ftr[maxm],son[maxm],A[maxm],V[maxm],B[maxm];
int fst[maxm],nxt[maxm],to[maxm];
int rt[maxm],lc[maxm << 1],rc[maxm << 1],rnk[maxm << 1];
int cnt,sz,num,n,m,tot;

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
}

void insert(int &x,int lst,int l,int r,int val){
	x = ++sz,lc[x] = lc[lst],rc[x] = rc[lst],rnk[x] = rnk[lst] + 1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(val <= mid) insert(lc[x],lc[lst],l,mid,val);
	else insert(rc[x],rc[lst],mid + 1,r,val);
}

int Qry(int x,int y,int LCA,int fLCA,int l,int r,int rank){
	if(l == r) return l;
	int mid = (l + r) >> 1;
	int tmp = rnk[lc[y]] + rnk[lc[x]] - rnk[lc[LCA]] - rnk[lc[fLCA]];
	if(rank <= tmp) return Qry(lc[x],lc[y],lc[LCA],lc[fLCA],l,mid,rank);
	else return Qry(rc[x],rc[y],rc[LCA],rc[fLCA],mid + 1,r,rank - tmp);
}

int lca(int x,int y){
	while(top[x] != top[y]){
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		x = ftr[top[x]];
	}
	return dpt[x] < dpt[y] ? x : y;
}

void dfs1(int x){
	size[x] = 1;
	insert(rt[x],rt[ftr[x]],1,tot,V[x]);
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
	pos[x] = ++num,top[x] = chain;
	if(son[x]) dfs2(son[x],chain);
	for(int u = fst[x];u;u = nxt[u])
		if(to[u] != ftr[x] && to[u] != son[x]) dfs2(to[u],to[u]);
}

int main(){
	int u,v,w,lstans = 0;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),B[i] = A[i];
	for(int i = 1;i < n;i++) scanf("%d%d",&u,&v),ins(u,v),ins(v,u);
	
	std :: sort(B + 1,B + n + 1);
	tot = std :: unique(B + 1,B + n + 1) - B - 1;
	for(int i = 1;i <= n;i++) V[i] = std :: lower_bound(B + 1,B + tot + 1,A[i]) - B;
	
	dfs1(1),dfs2(1,1);
	
	while(m--){
		scanf("%d%d%d",&u,&v,&w);
		u ^= lstans;
		int LCA = lca(u,v);
		lstans = B[Qry(rt[u],rt[v],rt[LCA],rt[ftr[LCA]],1,tot,w)];
		printf("%d",lstans);
		if(m) putchar(10);
	}
	
	return 0;
}
