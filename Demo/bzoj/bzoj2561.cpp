#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

struct Edge{
	int x,y,v;
	bool operator < (const Edge &E) const {
		return v < E.v;
	}
}E[maxm];

int fst[maxm],cur[maxm],cap[maxm],nxt[maxm],to[maxm],dpt[maxm],que[maxm];
int cnt = 1,n,m,S,T,L,ans;

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = v,fst[t] = cnt;
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
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++) scanf("%d%d%d",&E[i].x,&E[i].y,&E[i].v);
	scanf("%d%d%d",&S,&T,&L);
	
	std :: sort(E + 1,E + m + 1);
	
	for(int i = 1;i <= m;i++)
		if(E[i].v < L) ins(E[i].x,E[i].y,1);
		else break;
	
	ans += dinic();

	memset(fst,0,sizeof fst),cnt = 1;
	
	for(int i = m;i;i--)
		if(E[i].v > L) ins(E[i].x,E[i].y,1);
		else break;

	ans += dinic();

	printf("%d\n",ans);
	
	return 0;
}
