#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 29;

int fst[maxm],nxt[maxm],to[maxm],cur[maxm],cap[maxm];
int que[maxm],dpt[maxm],dp[maxm],A[maxm];
int n,m,S,T,ans,cnt = 1;

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
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);

	for(int i = 1;i <= n;i++) dp[i] = 1;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j < i;j++)
			if(A[j] <= A[i]) dp[i] = std :: max(dp[i],dp[j] + 1);

	S = (n << 1) + 1,T = (n << 1) + 2;
	
	for(int i = 1;i <= n;i++) ans = std :: max(ans,dp[i]);
	printf("%d\n",ans);

	if(ans == 1) return printf("%d\n%d\n",n,n),0;
	
	for(int i = 1;i <= n;i++){
		ins(i,i + n,1);		
		if(dp[i] == 1) ins(S,i,1);
		if(dp[i] == ans) ins(i + n,T,1);
		for(int j = 1;j < i;j++)
			if(A[j] <= A[i] && dp[i] == dp[j] + 1) ins(j + n,i,1);
	}
	
	printf("%d\n",dinic());

	memset(fst,0,sizeof fst),cnt = 1;
	
	for(int i = 1;i <= n;i++){
		if(i != 1 && i != n){
			ins(i,i + n,1);
			if(dp[i] == 1) ins(S,i,1);
			if(dp[i] == ans) ins(i + n,T,1);
		}
		else{
			ins(i,i + n,INF);
			if(dp[i] == 1) ins(S,i,INF);
			if(dp[i] == ans) ins(i + n,T,INF);
		}
		for(int j = 1;j < i;j++)
			if(A[j] <= A[i] && dp[i] == dp[j] + 1) ins(j + n,i,1);
	}

	printf("%d\n",dinic());
	
	return 0;
}
