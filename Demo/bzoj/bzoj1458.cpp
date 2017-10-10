#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 2e3 + 10;
static const int INF = 1 << 30;

int dpt[maxm],que[maxm],L[maxm],C[maxm],ddf[maxn][maxn];
int cap[maxm],nxt[maxm],fst[maxm],cur[maxm],to[maxm],_f[maxm],_g[maxm];
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
			int res = dfs(v,std :: min(flow,cap[u]));
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

int main(){
	int x,y;
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i <= n;i++) scanf("%d",&L[i]);
	for(int i = 1;i <= m;i++) scanf("%d",&C[i]);
	for(int i = 1;i <= k;i++) scanf("%d%d",&x,&y),ddf[x][y] = 1,_f[x]++,_g[y]++;
	S = n + m + 1,T = n + m + 2;
	
	for(int i = 1;i <= n;i++) _f[i] = m - _f[i] - L[i];
	for(int i = 1;i <= m;i++) _g[i] = n - _g[i] - C[i];

	for(int i = 1;i <= n;i++)
		if(_f[i] < 0) return puts("JIONG!"),0;

	for(int i = 1;i <= m;i++)
		if(_g[i] < 0) return puts("JIONG!"),0;

	for(int i = 1;i <= n;i++) ins(S,i,_f[i]);
	for(int i = 1;i <= m;i++) ins(i + n,T,_g[i]);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) ins(i,j + n,1);

	printf("%d\n",n * m - dinic() - k);
	
	return 0;
}
