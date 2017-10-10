#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e6 + 10;

int nxt[maxm],fst[maxm],to[maxm],dis[maxm];
int rt[maxm],lc[maxm],rc[maxm],v[maxm],L[maxm],C[maxm];
LL sum[maxm],size[maxm];
int sz,n,m,cnt;
LL ans;

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
}

int merge(int x,int y){
	if(!x || !y) return x ^ y;
	if(v[x] < v[y]) std :: swap(x,y);
	rc[x] = merge(rc[x],y);
	if(!lc[x] || dis[lc[x]] < dis[rc[x]]) std :: swap(lc[x],rc[x]);    // maintain left
	dis[x] = dis[rc[x]] + 1;
	return x;
}

int top(int x){
	return v[x];
}

void pop(int &x){
	x = merge(lc[x],rc[x]);
}

void dfs(int x){
	rt[x] = ++sz,v[sz] = C[x],size[x] = 1,sum[x] = C[x];
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		dfs(v);
		sum[x] += sum[v],size[x] += size[v];
		rt[x] = merge(rt[x],rt[v]);
	}
	while(sum[x] > m){
		sum[x] -= top(rt[x]);
		pop(rt[x]),size[x]--;
	}
	ans = std :: max(ans,size[x] * L[x]);
}

int main(){
	int x;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
		scanf("%d%d%d",&x,&C[i],&L[i]),ins(x,i);
	
	dfs(1);

	printf("%lld\n",ans);

	return 0;
}
