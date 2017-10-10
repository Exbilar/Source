#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 3e6 + 10;
static const int maxn = 3e3 + 10;
static const int INF = 1 << 30;

int cap[maxm],fst[maxn],nxt[maxm],to[maxm],cur[maxn];
int que[maxn],dpt[maxn];
int sz,n,m,S,T,cnt = 1;

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,fst[t] = cnt;
}

bool bfs(){
	for(int i = 1;i <= n + m + 2;i++) dpt[i] = 0;
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
	int res = 0,flow;
	while(bfs()){
		memcpy(cur,fst,sizeof cur);
		while(flow = dfs(S,INF)) res += flow;
	}
	return res;
}

int main(){
	int x,y,z,w,sum = 0;
	scanf("%d%d",&n,&m); S = n + m + 1,T = n + m + 2;

	for(int i = 1;i <= n;i++){
		scanf("%d%d",&x,&w); ins(S,i,x),sum += x;
		for(int j = 1;j <= w;j++){
			scanf("%d%d",&z,&y); ins(i,z + n,y);
		}
	}

	for(int i = 1;i <= m;i++) scanf("%d",&x),ins(i + n,T,x);
	
	printf("%d\n",sum - dinic());
	
	return 0;
}
