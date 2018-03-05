#include <cstdio>
#include <cstring>
#include <bitset>
#include <algorithm>
 
using std :: bitset;
 
static const int maxn = 2e3 + 10;
static const int maxm = 2e5 + 10;
static const int INF = 1 << 30;
 
int nxt[maxm],to[maxm],cur[maxm],fst[maxm],cap[maxm],dpt[maxm],que[maxm],f[maxn][maxn];
int n,m,ans,S,T,cnt = 1;
 
void ins(int f,int t,int v){
    nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
    nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,fst[t] = cnt;
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
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= m;i++){
        scanf("%d%d",&x,&y);
        f[x][y] = 1;
    }
 
    for(int k = 1;k <= n;k++)
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= n;j++)
				f[i][j] |= (f[i][k] & f[k][j]);
	
    S = (n << 1) + 1,T = (n << 1) + 2;
	
    for(int i = 1;i <= n;i++) ins(S,i,1),ins(i + n,T,1);
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            if(f[i][j] && i != j) ins(i,j + n,1);
	
    printf("%d\n",n - dinic());
	
    return 0;
}
