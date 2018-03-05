#include <cstdio>
#include <cstring>
#include <algorithm>

template <class T>T Max(const T &a, const T &b) {return a > b ? a : b;}
template <class T>T Min(const T &a, const T &b) {return a < b ? a : b;}

static const int maxm = 2e5 + 10;
static const int maxn = 2e2 + 10;
static const int INF = 1 << 30;

int A[maxn][maxn],B[maxn][maxn],C[maxn][maxn],col[maxn][maxn],que[maxm],dpt[maxm];
int fst[maxm],cur[maxm],nxt[maxm],to[maxm],cap[maxm],idx[maxn][maxn];
int cnt = 1,n,m,sum,S,T,ID;

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,fst[t] = cnt;
}

bool bfs(){
    memset(dpt,0,sizeof dpt);
    int head = 0,tail = 1;
    que[++tail] = S;
    dpt[S] = 1;

	int x, v;
	
    while(head <= tail){
        x = que[head++];
        for(int u = fst[x];u;u = nxt[u]){
            v = to[u];
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
	int res = 0;
    for(int &u = cur[x];u;u = nxt[u]){
        int v = to[u];
        if(dpt[v] == dpt[x] + 1 && cap[u]){
            res = dfs(v,Min(flow,cap[u]));
            if(res) return cap[u] -= res,cap[u ^ 1] += res,res;
        }
    }
    return 0;
}
 
int dinic(){
    int flow,res = 0;
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
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			scanf("%d",&A[i][j]),sum += A[i][j];

	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			scanf("%d",&B[i][j]),sum += B[i][j];

	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			scanf("%d",&C[i][j]);

	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			col[i][j] = (i + j) & 1,idx[i][j] = ++ID;

	S = ++ID,T = ++ID;
	
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			if(col[i][j]) ins(S,idx[i][j],A[i][j]),ins(idx[i][j],T,B[i][j]);
			else ins(S,idx[i][j],B[i][j]),ins(idx[i][j],T,A[i][j]);

	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(OK(i - 1,j)) ins(idx[i][j],idx[i - 1][j],C[i][j]),ins(idx[i - 1][j],idx[i][j],C[i][j]),sum += C[i][j];
			if(OK(i + 1,j)) ins(idx[i][j],idx[i + 1][j],C[i][j]),ins(idx[i + 1][j],idx[i][j],C[i][j]),sum += C[i][j];
			if(OK(i,j - 1)) ins(idx[i][j],idx[i][j - 1],C[i][j]),ins(idx[i][j - 1],idx[i][j],C[i][j]),sum += C[i][j];
			if(OK(i,j + 1)) ins(idx[i][j],idx[i][j + 1],C[i][j]),ins(idx[i][j + 1],idx[i][j],C[i][j]),sum += C[i][j];
		}
	}
	
	printf("%d\n",sum - dinic());
	
	return 0;
}
