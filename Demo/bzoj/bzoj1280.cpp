#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 2e3 + 10;
static const int INF = 1 << 30;

int dpt[maxm],que[maxm],A[maxn][maxn],num[maxn],fw[maxn],vis[maxn],pig[maxn];
int cap[maxm],nxt[maxm],to[maxm],fst[maxm],cur[maxm],pre[maxm];
int k,n,m,S,T,cnt = 1;

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
		if(cap[u] && dpt[v] == dpt[x] + 1){
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
	scanf("%d%d",&m,&n);
	S = n + 1,T = n + 2;
	for(int i = 1;i <= m;i++) scanf("%d",&pig[i]); 
	for(int i = 1;i <= n;i++){
		scanf("%d",&num[i]);
		for(int j = 1;j <= num[i];j++) scanf("%d",&A[i][j]);
		scanf("%d",&fw[i]);
	}

	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= num[i];j++)
			if(!vis[A[i][j]]) ins(S,i,pig[A[i][j]]),vis[A[i][j]] = 1,pre[A[i][j]] = i;
			else ins(pre[A[i][j]],i,INF),pre[A[i][j]] = i;

	for(int i = 1;i <= n;i++) ins(i,T,fw[i]);

	printf("%d\n",dinic());
	
	return 0;
}
