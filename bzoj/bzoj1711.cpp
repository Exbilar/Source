#include <cstdio>
#include <cstring>
#include <algorithm>
 
static const int maxm = 1e5 + 10;
static const int INF = 1 << 30;
 
int dpt[maxm],que[maxm];
int cap[maxm],nxt[maxm],to[maxm],fst[maxm],cur[maxm];
int k,n,F,D,S,T,cnt = 1;
 
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
            if(cap[u] && !dpt[v]){
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
	int x,y,z;
    scanf("%d%d%d",&n,&F,&D);
	S = n * 2 + F + D + 1,T = S + 1;
	for(int i = 1;i <= F;i++) ins(S,i,1);
	for(int i = 1;i <= D;i++) ins(F + i,T,1);
	for(int i = 1;i <= n;i++){
		scanf("%d%d",&x,&y);
		for(int j = 1;j <= x;j++) scanf("%d",&z),ins(z,F + D + i,1);
		for(int j = 1;j <= y;j++) scanf("%d",&z),ins(F + D + n + i,F + z,1);
		ins(F + D + i,F + D + n + i,1);
	}
	
	printf("%d\n",dinic());
	
    return 0;
}
