#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int cur[maxm],fst[maxm],nxt[maxm],to[maxm],que[maxm],dpt[maxm];
LL cap[maxm];
int n,m,S,T,cnt = 1;

void ins(int f,int t,LL v){
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

LL dfs(int x,LL flow){
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

LL dinic(){
	LL res = 0,flow = 0;
	while(bfs()){
		memcpy(cur,fst,sizeof cur);
		while(flow = dfs(S,INF)) res += flow;
	}
	return res;
}

int main(){
	int k,x; LL sum = 0;
	scanf("%d",&n);
	S = n + n + 1,T = n + n + 2;
	for(int i = 1;i <= n;i++){
		ins(i + n,T,INF);
		scanf("%d",&k);
		while(k--) scanf("%d",&x),ins(i,x + n,INF);
	}
	
	for(int i = 1;i <= n;i++){
		scanf("%d",&x);
		ins(S,i,INF - x);
		sum += INF - x;
	}

	printf("%lld\n",dinic() - sum);
	
	return 0;
}
