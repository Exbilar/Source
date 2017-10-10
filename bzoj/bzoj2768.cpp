#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int cur[maxm],fst[maxm],nxt[maxm],to[maxm],cap[maxm],que[maxm],dpt[maxm];
int cnt = 1,n,m,S,T;

void ins(int f,int t,int v1,int v2){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v1,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = v2,fst[t] = cnt;
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
	int x,y;
	scanf("%d%d",&n,&m);
	S = n + 1,T = n + 2;
	for(int i = 1;i <= n;i++){
		scanf("%d",&x);
		if(x) ins(S,i,1,0);
		else ins(i,T,1,0);
	}

	for(int i = 1;i <= m;i++) scanf("%d%d",&x,&y),ins(x,y,1,1);
	
	printf("%d\n",dinic());

	return 0;
}
