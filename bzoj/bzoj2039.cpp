#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

static const int maxm = 2e6 + 10;
static const int maxn = 1e3 + 10;
static const LL INF = 1LL << 60;

LL cap[maxm],cur[maxm],fst[maxm],nxt[maxm],to[maxm];
LL que[maxm],dpt[maxm],E[maxn][maxn],C[maxn],A[maxn];
LL cnt = 1,n,m,S,T;

void ins(LL f,LL t,LL v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
}

bool bfs(){
	memset(dpt,0,sizeof dpt);
	int head = 1,tail = 0;
	que[++tail] = S;
	dpt[S] = 1;

	while(head <= tail){
		LL x = que[head++];
		for(LL u = fst[x];u;u = nxt[u]){
			LL v = to[u];
			if(cap[u] && !dpt[v]){
				dpt[que[++tail] = v] = dpt[x] + 1;
				if(v == T) return true;
			}
		}
	}
	
	return false;
}

LL dfs(LL x,LL flow){
	if(x == T || !flow) return flow;
	for(LL &u = cur[x];u;u = nxt[u]){
		LL v = to[u];
		if(dpt[v] == dpt[x] + 1 && cap[u]){
			LL res = dfs(v,std :: min(flow,cap[u]));
			if(res) return cap[u] -= res,cap[u ^ 1] += res,res;
		}
	}
}

LL dinic(){
	LL res = 0,flow = 0;
	while(bfs()){
		memcpy(cur,fst,sizeof cur);
		while(flow = dfs(S,INF)) res += flow;
	}
	return res;
}

int main(){
	LL sum = 0;
	scanf("%lld",&n);
	S = n + 1,T = S + 1;
	for(int i = 1;i <= n;i++) scanf("%lld",&C[i]);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			scanf("%lld",&E[i][j]),sum += E[i][j],A[i] += E[i][j];
		}
	}

	for(int i = 1;i <= n;i++) ins(S,i,A[i]),ins(i,S,0);
	for(int i = 1;i <= n;i++) ins(i,T,C[i]),ins(T,i,0);
	
	for(int i = 1;i < n;i++)
		for(int j = i + 1;j <= n;j++)
			ins(i,j,E[i][j] << 1),ins(j,i,E[i][j] << 1);
	
	printf("%lld\n",sum - dinic());
	
	return 0;
}
