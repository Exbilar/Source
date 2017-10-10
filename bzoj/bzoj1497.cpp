#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int dpt[maxm],nxt[maxm],to[maxm],fst[maxm],cur[maxm],cap[maxm];
int A[maxm],B[maxm],C[maxm],P[maxm],que[maxm];
int cnt = 1,n,m,S,T,sum;

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

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&P[i]);
	for(int i = 1;i <= m;i++) scanf("%d%d%d",&A[i],&B[i],&C[i]),sum += C[i];
	
	S = n + m + 1,T = n + m + 2;

	for(int i = 1;i <= m;i++) ins(S,i + n,C[i]);
	for(int i = 1;i <= m;i++) ins(i + n,A[i],INF),ins(i + n,B[i],INF);
	for(int i = 1;i <= n;i++) ins(i,T,P[i]);

	printf("%d\n",sum - dinic());
	
	return 0;
}
