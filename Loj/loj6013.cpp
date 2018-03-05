#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = ~(1 << 31);

int cap[maxm],cst[maxm],fst[maxm],nxt[maxm],to[maxm];
int que[maxm],vis[maxm],inq[maxm],dis[maxm],A[maxm];
int cnt = 1,n,m,S,T,allc,ave;

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
				if(!inq[v]) inq[que[++tail] = v] = 1;
			}
		}
	}
	
	return dis[T] ^ INF;
}

int dfs(int x,int flow){
	if(vis[x]) return 0;
	if(x == T || !flow) return allc += flow * dis[T],flow;
	
	vis[x] = 1; int res = 0,f = 0;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(dis[v] == dis[x] + cst[u] && cap[u]){
			if(f = dfs(v,std :: min(flow,cap[u]))){
				cap[u] -= f,cap[u ^ 1] += f;
				flow -= f,res += f;
			}
		}
	}
	vis[x] = 0;
	return res;
}

int mcmf(){
	int res = 0;
	while(spfa()) res += dfs(S,INF);
	return res;
}

int main(){
	scanf("%d",&n);
	S = n + 1,T = n + 2;
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),ave += A[i]; ave /= n;
	
	for(int i = 1;i <= n;i++) ins(S,i,A[i],0),ins(i,T,ave,0);
	for(int i = 1;i < n;i++) ins(i,i + 1,INF,1),ins(i + 1,i,INF,1);
	ins(1,n,INF,1),ins(n,1,INF,1);

	mcmf();
	printf("%d\n",allc);
	
	return 0;
}
