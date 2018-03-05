#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 2e5 + 10;
static const int INF = ~(1 << 31);

int fst[maxm],nxt[maxm],to[maxm],cap[maxm],cst[maxm],dis[maxm],link[maxm];
int que[maxm],vis[maxm],inq[maxm],r[maxm];
int cnt = 1,S,T,n,m,allc,allf;

void ins(int f,int t,int v,int c){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,cst[cnt] = c,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,cst[cnt] = -c,fst[t] = cnt;
}

bool spfa(){
	for(int i = 1;i <= n + n;i++) dis[i] = INF,inq[i] = 0;
	int head = 1,tail = 0;
	dis[S] = 0,inq[S] = 1;
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
	allc += dis[T] * f;
	allf += f;
	return true;
}

int mcmf(){
	while(spfa());
}

int main(){
	int x,y,z;
	scanf("%d%d",&n,&m); S = 1,T = n + n;
	for(int i = 1;i <= m;i++) scanf("%d%d%d",&x,&y,&z),ins(x + n,y,1,z);
	for(int i = 2;i < n;i++) ins(i,i + n,1,0);
	ins(S,S + n,INF,0),ins(n,T,INF,0);
	
	mcmf();
	
	printf("%d %d\n",allf,allc);
	
	return 0;
}
