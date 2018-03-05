#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = ~(1 << 31);

int fst[maxm],nxt[maxm],to[maxm],cst[maxm],cap[maxm];
int inq[maxm],vis[maxm],dis[maxm],que[maxm];
int S,T,allc,n,m,cnt = 1;

void ins(int f,int t,int v,int c){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,cst[cnt] = c,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,cst[cnt] = -c,fst[t] = cnt;
}

bool spfa(){
	for(int i = 1;i <= n;i++) dis[i] = INF,inq[i] = 0;
	int head = 1,tail = 0;
	inq[S] = 1,dis[S] = 0;
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

int main(){
	int x,y,z,w;
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d%d%d%d",&x,&y,&z,&w);
		ins(x,y,z,w);
	}

	S = 1,T = n;

	int ans = mcmf();

	printf("%d %d\n",ans,allc);
	
	return 0;
}
