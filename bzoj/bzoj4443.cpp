#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 1e3 + 10;
static const int INF = 1 << 30;

int cur[maxm],fst[maxm],nxt[maxm],to[maxm],cap[maxm];
int ddf[maxn][maxn],que[maxm],dpt[maxm];
int cnt = 1,n,m,k,S,T;

void addedge(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
}

void ins(int f,int t,int v){
	addedge(f,t,v),addedge(t,f,0);
}

bool bfs(){
	memset(dpt,0,sizeof dpt);
	int head = 1,tail = 0;
	que[++tail] = S;
	dpt[S] = 1;

	while(head <= tail){
		int x = que[head++];
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(!dpt[v] && cap[u]){
				dpt[que[++tail] = v] = dpt[x] + 1;
				if(v == T) return true;
			}
		}
	}
	return false;
}

int dfs(int x,int flow){
	if(x == T || !flow) return flow;
	for(int &u = cur[x];u;u = nxt[u]){
		int v = to[u];
		if(dpt[v] == dpt[x] + 1 && cap[u]){
			int res = dfs(v,std :: min(cap[u],flow));
			if(res) return cap[u] -= res,cap[u ^ 1] += res,res;
		}
	}
	return 0;
}

int dinic(){
	int res = 0,flow = 0;
	while(bfs()){
		memcpy(cur,fst,sizeof cur);
		while(flow = dfs(S,INF)) res += flow;
	}
	return res;
}

bool chk(int x){
	memset(fst,0,sizeof fst),cnt = 1;
	
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			if(ddf[i][j] <= x) ins(i,j + n,1);

	for(int i = 1;i <= n;i++) ins(S,i,1);
	for(int i = 1;i <= m;i++) ins(i + n,T,1);

	return dinic() >= n - k + 1;
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			scanf("%d",&ddf[i][j]);

	int l = 1,r = INF,ans = 0;
	S = n + m + 1,T = n + m + 2;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(chk(mid)) ans = mid,r = mid - 1;
		else l = mid + 1;
	}

	printf("%d\n",ans);
	
	return 0;
}

// Algorithm : build graph : separate x and y
