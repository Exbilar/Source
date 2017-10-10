#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int fst[maxm],nxt[maxm],to[maxm],cap[maxm],cst[maxm],dis[maxm];
int vis[maxm],inq[maxm],que[maxm],link[maxm],A[maxm];
int allf,allc,n,m,S,T,cnt = 1;

void ins(int f,int t,int v,int c){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,cst[cnt] = c,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,cst[cnt] = -c,fst[t] = cnt;
}

bool spfa(){
	for(int i = 1;i <= n + 3;i++) dis[i] = INF,inq[i] = 0;
	int head = 1,tail = 0;
	inq[S] = 1,dis[S] = 0;
	que[++tail] = S;

	while(head <= tail){
		int x = que[head++]; inq[x] = 0;
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(dis[v] > dis[x] + cst[u] && cap[u]){
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
	allf += f,allc += f * dis[T];
	
	return true;
}

int mcmf(){
	while(spfa());
	return allc;
}

int main(){
	int x,y,z;
	scanf("%d%d",&n,&m);
	S = n + 2,T = n + 3;
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),ins(i + 1,i,INF,0);
	for(int i = 1;i <= m;i++) scanf("%d%d%d",&x,&y,&z),ins(x,y + 1,INF,z);
	for(int i = 1;i <= n + 1;i++){
		if(A[i] - A[i - 1] > 0) ins(S,i,A[i] - A[i - 1],0);
		if(A[i] - A[i - 1] < 0) ins(i,T,A[i - 1] - A[i],0);
	}

	printf("%d\n",mcmf());
	
	return 0;
}
