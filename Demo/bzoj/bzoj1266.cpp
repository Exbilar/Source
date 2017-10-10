#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 2e3 + 10;
static const int INF = 1 << 29;

struct Edge{
	int x,y,w,d;
}E[maxm];

int cur[maxm],fst[maxm],nxt[maxm],cap[maxm],to[maxm];
int que[maxm],dpt[maxm],dis[maxn][maxn];
int cnt = 1,n,m,S,T;

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

void floyd(){
	for(int k = 1;k <= n;k++)
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= n;j++)
				dis[i][j] = std :: min(dis[i][j],dis[i][k] + dis[k][j]);
}

int main(){
	scanf("%d%d",&n,&m);
	S = 1,T = n;
	
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++) dis[i][j] = INF;

	for(int i = 1;i <= n;i++) dis[i][i] = 0;
	
	for(int i = 1;i <= m;i++){
		scanf("%d%d%d%d",&E[i].x,&E[i].y,&E[i].d,&E[i].w);
		dis[E[i].x][E[i].y] = dis[E[i].y][E[i].x] = E[i].d;
	}

	floyd();

	printf("%d\n",dis[1][n]);

	for(int i = 1;i <= m;i++){
		if(dis[1][E[i].x] + dis[E[i].y][n] + E[i].d == dis[1][n]) ins(E[i].x,E[i].y,E[i].w);
		if(dis[1][E[i].y] + dis[E[i].x][n] + E[i].d == dis[1][n]) ins(E[i].y,E[i].x,E[i].w);
	}

	printf("%d\n",dinic());
	
	return 0;
}
