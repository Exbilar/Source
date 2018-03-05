#include <cstdio>
#include <cstring>
#include <algorithm>

#define REP(i,l,r) for(int i = l;i <= r;i++)

static const int maxm = 1e6 + 10;
static const int maxn = 2e3 + 10;
static const int INF = 1 << 30;

int que[maxm],dpt[maxm],sc[maxn][maxn],_sc[maxn][maxn],art[maxn][maxn],_art[maxn][maxn];
int nxt[maxm],to[maxm],fst[maxm],cur[maxm],cap[maxm],idx[maxn][maxn];
int cnt = 1,S,T,n,m,ID,sum;

void ins(int f,int t,int v){
    nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
    nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,fst[t] = cnt;
}
 
bool bfs(){
    memset(dpt,0,sizeof dpt);
    int head = 0,tail = 1;
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
    int flow = 0,res = 0;
    while(bfs()){
        memcpy(cur,fst,sizeof cur);
        while(flow = dfs(S,INF)) res += flow;
    }
    return res;
}

bool OK(int i,int j){
	return (i >= 1 && i <= n) && (j >= 1 && j <= m);
}

int main(){
	scanf("%d%d",&n,&m);

	S = ++ID,T = ++ID;
	
	REP(i,1,n) REP(j,1,m)
		scanf("%d",&art[i][j]),sum += art[i][j];

	REP(i,1,n) REP(j,1,m)
		scanf("%d",&sc[i][j]),sum += sc[i][j];
	
	REP(i,1,n) REP(j,1,m)
		scanf("%d",&_art[i][j]),sum += _art[i][j];

	REP(i,1,n) REP(j,1,m)
		scanf("%d",&_sc[i][j]),sum += _sc[i][j];

	REP(i,1,n) REP(j,1,m) idx[i][j] = ++ID;
		
	REP(i,1,n) REP(j,1,m)
		ins(S,idx[i][j],art[i][j]),ins(idx[i][j],T,sc[i][j]);
	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			ins(S,++ID,_art[i][j]);
			if(OK(i - 1,j)) ins(ID,idx[i - 1][j],INF);
			if(OK(i + 1,j)) ins(ID,idx[i + 1][j],INF);
			if(OK(i,j - 1)) ins(ID,idx[i][j - 1],INF);
			if(OK(i,j + 1)) ins(ID,idx[i][j + 1],INF);
			ins(ID,idx[i][j],INF);
		}
	}

	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			ins(++ID,T,_sc[i][j]);
			if(OK(i - 1,j)) ins(idx[i - 1][j],ID,INF);
			if(OK(i + 1,j)) ins(idx[i + 1][j],ID,INF);
			if(OK(i,j - 1)) ins(idx[i][j - 1],ID,INF);
			if(OK(i,j + 1)) ins(idx[i][j + 1],ID,INF);
			ins(idx[i][j],ID,INF);
		}
	}
	
	printf("%d\n",sum - dinic());
	
	return 0;
}
