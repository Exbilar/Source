#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 4e6 + 10;
static const int maxn = 1e3 + 10;
static const int INF = 1 << 30;

int cap[maxm],cur[maxm],fst[maxm],nxt[maxm],to[maxm];
int que[maxm],dpt[maxm],B[maxn][maxn],C[maxn],idx[maxn][maxn];
int cnt = 1,n,m,S,T,ID,sum;

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

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++) scanf("%d",&B[i][j]),sum += B[i][j];
	
	for(int i = 1;i <= n;i++) scanf("%d",&C[i]);

	S = maxm >> 1,T = S + 1;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			ins(S,i * n + j,B[i][j]);
			ins(i * n + j,i,INF),ins(i * n + j,j,INF);
		}
	}

	for(int i = 1;i <= n;i++) ins(i,T,C[i]);

	printf("%d\n",sum - dinic());
	
	return 0;
}
