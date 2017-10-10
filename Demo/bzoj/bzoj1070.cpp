#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 2e3 + 10;
static const int INF = 1 << 30;

int cap[maxm],nxt[maxm],fst[maxm],to[maxm],cst[maxm],dis[maxm];
int vis[maxm],inq[maxm],que[maxm],link[maxm],w[maxn][maxn];
int n,m,S,T,allf,allc,cnt = 1;

void ins(int f,int t,int v,int c){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,cst[cnt] = c,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,cst[cnt] = -c,fst[t] = cnt;
}

bool spfa(){
	for(int i = 1;i <= n * m + n + 2;i++) dis[i] = INF,inq[i] = 0;
	int head = 1,tail = 0;
	inq[S] = 1,dis[S] = 0;
	que[++tail] = S;

	while(head <= tail){
		int x = que[head++]; inq[x] = 0;
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(cap[u] && dis[v] > dis[x] + cst[u]){
				dis[v] = dis[x] + cst[u];
				link[v] = u;
				if(!inq[v]) inq[que[++tail] = v] = 1;
			}
		}
	}

	if(dis[T] == INF) return false;
	
	int f = INF;

	for(int u = link[T];u;u = link[to[u ^ 1]]) f = std :: min(f,cap[u]);
	for(int u = link[T];u;u = link[to[u ^ 1]]) cap[u] -= f,cap[u ^ 1] += f;
	allc += dis[T] * f,allf += f;
	
	return true;
}

int mcmf(){
	while(spfa());
	return allc;
}

int get(int x,int k){
	return x * n + k;
}

int main(){
	scanf("%d%d",&m,&n);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) scanf("%d",&w[i][j]);
	
	S = n * m + n + 1,T = n * m + n + 2;

	for(int i = 1;i <= n;i++) ins(S,i,1,0);
	for(int i = 1;i <= m;i++)
		for(int j = 1;j <= n;j++) ins(get(i,j),T,1,0);

	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			for(int k = 1;k <= n;k++) ins(i,get(j,k),1,w[i][j] * k);

	printf("%.2lf\n",(double) mcmf() / n);
	
	return 0;
}
