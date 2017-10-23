#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int fst[maxm],nxt[maxm],to[maxm],cap[maxm],cur[maxm];
int que[maxm],dpt[maxm],id[maxm],ans[maxm];
int n,m,S,T,cnt = 1;

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
	int x,y,up,down,tot = 0;;
	scanf("%d%d",&n,&m); S = n + 1,T = n + 2;
	
	for(int i = 1;i <= m;i++){
		scanf("%d%d%d%d",&x,&y,&down,&up);
		ins(x,y,up - down); id[i] = cnt;
		ins(S,y,down),ins(x,T,down);
		ans[i] = down,tot += down;
	}
	
	if(dinic() != tot) return puts("NO"),0;

	puts("YES");

	for(int i = 1;i <= m;i++) printf("%d\n",cap[id[i]] + ans[i]);

	return 0;
}
