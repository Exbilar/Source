#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 2e3 + 10;
static const int INF = 1 << 30;

int cur[maxm],cap[maxm],fst[maxm],nxt[maxm],to[maxm];
int que[maxm],dpt[maxm],idx[maxn][maxn],A[maxm],v[maxn][maxn];
int n,m,S,T,ID,cnt = 1;

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
			int res = dfs(v,std :: min(cap[u],flow));
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

int main(){
	int sum = 0,Amax = 0;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),Amax = std :: max(Amax,A[i]);
	for(int i = 1;i <= n;i++)
		for(int j = i;j <= n;j++) scanf("%d",&v[i][j]),idx[i][j] = ++ID;
	
	S = ID + Amax + 1,T = ID + Amax + 2;

	for(int i = 1;i <= Amax;i++) ins(ID + i,T,m * i * i);
	for(int i = 1;i <= n;i++) ins(idx[i][i],ID + A[i],INF),v[i][i] -= A[i];

	for(int i = 1;i <= n;i++){
		for(int j = i;j <= n;j++){
			if(v[i][j] > 0) ins(S,idx[i][j],v[i][j]),sum += v[i][j];
			if(v[i][j] < 0) ins(idx[i][j],T,-v[i][j]);
			if(i < j) ins(idx[i][j],idx[i][j - 1],INF),ins(idx[i][j],idx[i + 1][j],INF);
		}
	}

	printf("%d\n",sum - dinic());
	
	return 0;
}
