#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int cap[maxm],cst[maxm],fst[maxm],nxt[maxm],to[maxm],_d[maxm],_u[maxm];
int que[maxm],vis[maxm],inq[maxm],link[maxm],dis[maxm];
int cnt = 1,n,m,S,T,allc,_S;

void ins(int f,int t,int v,int c){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,cst[cnt] = c,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,cst[cnt] = -c,fst[t] = cnt;
}

bool spfa(){
	for(int i = 1;i <= n + 2;i++) dis[i] = INF,inq[i] = 0;
	int head = 1,tail = 0;
	dis[S] = 0,inq[S] = 1;
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
	allc += dis[T] * f;
	return true;
}

int mcmf(){
	while(spfa());
}

int main(){
	scanf("%d%d%d",&n,&m,&_S);
	for(int i = 1;i <= n;i++) scanf("%d",&_u[i]);
	for(int i = 1;i <= n;i++) scanf("%d",&_d[i]);
	S = n + 1,T = n + 2;

	for(int i = 1;i <= n;i++) ins(S,i,INF,_d[i]),ins(i,T,_u[i],0);
	for(int i = 1;i < n;i++) ins(i,i + 1,_S,m);

	mcmf();
	
	printf("%d\n",allc);
	
	return 0;
}
