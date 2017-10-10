#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int fst[maxm],cur[maxm],nxt[maxm],to[maxm],cap[maxm];
int que[maxm],dpt[maxm],vis[maxm];
int cnt = 1,n,m,C,S,T;

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
	int res = 0,flow = 0;
	while(bfs()){
		memcpy(cur,fst,sizeof cur);
		while(flow = dfs(S,INF)) res += flow;
	}
	return res;
}

int main(){
	int x,y;
	scanf("%d%d%d",&n,&m,&C);
	S = (n << 1) + 1,T = S + 1;
	
	ins(S,1,INF),ins(1,1 + n,INF);
	for(int i = 1;i <= m;i++){
		scanf("%d%d",&x,&y);
		ins(x + n,y,INF),ins(y + n,x,INF);
	}

	for(int i = 1;i <= C;i++){
		scanf("%d",&x),vis[x] = 1;
		ins(x,x + n,INF),ins(x + n,T,INF);
	}

	for(int i = 2;i <= n;i++){
		if(!vis[i]) ins(i,i + n,1);
	}

	printf("%d\n",dinic());
	
	return 0;
}
