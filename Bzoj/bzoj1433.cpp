#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int cur[maxm],fst[maxm],to[maxm],nxt[maxm],cap[maxm],insch[maxm],que[maxm],dpt[maxm];
int cnt = 1,S,T,cas,n,m;

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
			if(cap[u] && !dpt[v]){
				dpt[que[++tail] = v] = dpt[x] + 1;
				if(v == T) return true;
			}
		}
	}
	return false;
}

int dfs(int x,int flow){
	int res = 0;
	if(x == T || !flow) return flow;

	for(int &u = cur[x];u;u = nxt[u]){
		int v = to[u];
		if(dpt[v] == dpt[x] + 1 && cap[u]){
			res = dfs(v,std :: min(flow,cap[u]));
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
	scanf("%d",&cas);

	while(cas--){
		memset(fst,0,sizeof fst),cnt = 1;
		
		scanf("%d",&n);
		S = n * 2 + 1,T = n * 2 + 2;
		int tot = 0;
		for(int i = 1;i <= n;i++){
			scanf("%d",&insch[i]);
			if(insch[i]) ins(S,i,1);
			else ins(i + n,T,1),tot++;
		}
		for(int i = 1;i <= n;i++){
			scanf("%d",&x);
			if(insch[i] && !x) ins(i + n,T,1),tot++;
		}

		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= n;j++){
				scanf("%d",&x);
				if(x || i == j) ins(i,j + n,1);
			}
		}

		puts(dinic() == tot ? "^_^" : "T_T");
	}

	return 0;
}
