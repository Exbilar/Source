#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int dpt[maxm],que[maxm],nxt[maxm],to[maxm],fst[maxm],cur[maxm],cap[maxm];
int cnt = 1,n,m,k,S,T;

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
	int x,p;
	scanf("%d%d",&k,&n);
	S = n + k + 1,T = n + k + 2;
	for(int i = 1;i <= k;i++) scanf("%d",&x),ins(S,i + n,x),m += x;
	for(int i = 1;i <= n;i++){
		scanf("%d",&p),ins(i,T,1);
		for(int j = 1;j <= p;j++) scanf("%d",&x),ins(x + n,i,1);
	}
	
	if(dinic() != m) return puts("No Solution!"),0;
	
	for(int i = n + 1;i <= n + k;i++){
		printf("%d: ",i - n);
		for(int u = fst[i];u;u = nxt[u])
			if(to[u] >= 1 && to[u] <= n && !cap[u]) printf("%d ",to[u]);
		putchar(10);
	}
	
	return 0;
}
