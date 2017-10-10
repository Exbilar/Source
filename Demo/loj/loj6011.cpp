#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e5 + 10;
static const int maxn = 2e3 + 10;
static const int INF = ~(1 << 31);

int fst[maxm],nxt[maxm],to[maxm],cst[maxm],cap[maxm];
int inq[maxm],vis[maxm],dis[maxm],que[maxm];
int A[maxm],B[maxm],C[maxn][maxn];
int S,T,allc,n,m,cnt = 1;

void ins(int f,int t,int v,int c){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,cst[cnt] = c,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,cst[cnt] = -c,fst[t] = cnt;
}

bool spfa(){
	for(int i = 1;i <= n + m + 2;i++) dis[i] = INF,inq[i] = 0;
	int head = 1,tail = 0;
	dis[S] = 0,inq[S] = 1;
	que[++tail] = S;

	while(head <= tail){
		int x = que[head++]; inq[x] = 0;
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(cap[u] && dis[v] > dis[x] + cst[u]){
				dis[v] = dis[x] + cst[u];
				if(!inq[v]) inq[que[++tail] = v] = 1;
			}
		}
	}

	return dis[T] ^ INF;
}

int dfs(int x,int flow){
	if(vis[x]) return 0;
	if(x == T || !flow) return allc += dis[T] * flow,flow;
	
	vis[x] = 1; int res = 0,f = 0;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(dis[v] == dis[x] + cst[u] && cap[u]){
			if(f = dfs(v,std :: min(flow,cap[u]))){
				cap[u] -= f,cap[u ^ 1] += f;
				res += f,flow -= f;
			}
		}
	}

	vis[x] = 0;
	return res;
}

int mcmf(){
	int res = 0,flow = 0;
	while(spfa()) res += dfs(S,INF);
	return res;
}

void build(int k){
	cnt = 1,memset(fst,0,sizeof fst);
	for(int i = 1;i <= n;i++) ins(S,i,A[i],0);
	for(int i = 1;i <= m;i++) ins(i + n,T,B[i],0);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			ins(i,j + n,INF,k * C[i][j]);
}

int main(){
	scanf("%d%d",&n,&m);
	S = n + m + 1,T = n + m + 2;
	
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	for(int i = 1;i <= m;i++) scanf("%d",&B[i]);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			scanf("%d",&C[i][j]);
	
	build(1);
	mcmf();
	printf("%d\n",allc);
	build(-1);
	allc = 0;
	mcmf();
	printf("%d\n",-allc);
	
	
	return 0;
}
