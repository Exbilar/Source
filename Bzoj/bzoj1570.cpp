#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 5e3 + 10;
static const int INF = 1 << 30;

int cap[maxm],fst[maxm],cur[maxm],to[maxm],nxt[maxm],que[maxn],dpt[maxn],old[maxm];
int Ex[maxn],Ey[maxn],Ez[maxn];
int cnt = 1,S,T,n,m,t;

void ins(int f,int t,int v){
    nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,old[cnt] = v,fst[f] = cnt;
    nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,old[cnt] = 0,fst[t] = cnt;
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
	scanf("%d%d%d",&n,&m,&t);
	for(int i = 1;i <= m;i++)
		scanf("%d%d%d",&Ex[i],&Ey[i],&Ez[i]);

	S = (n + t) * n + 1,T = (n + t) * n + 2;
	
	ins(S,1,t);
	for(int i = 1;i <= n + t;i++){
		for(int j = 2;j <= cnt;j++) cap[j] = old[j];
		for(int j = 1;j <= m;j++) ins(i * n - n + Ex[j],i * n + Ey[j],Ez[j]);
		for(int j = 1;j <= n;j++) ins(i * n - n + j,i * n + j,INF);
		ins(i * n + n,T,INF);
		if(dinic() == t) return printf("%d\n",i),0;
	}

	return 0;
}
