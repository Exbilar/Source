#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int cap[maxm],fst[maxm],nxt[maxm],to[maxm],cur[maxm],vis[maxm],frm[maxm];
int dpt[maxm],que[maxm],stk[maxm],low[maxm],dfn[maxm],ddf[maxm];
int n,m,top,sz,scc,cnt = 1,S,T;

void addedge(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,frm[cnt] = f,cap[cnt] = v,fst[f] = cnt;
}

void ins(int f,int t,int v){
	addedge(f,t,v),addedge(t,f,0);
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

void tarjan(int x){
	vis[x] = 1;
	stk[++top] = x;
	low[x] = dfn[x] = ++sz;
	
	for(int u = fst[x];u;u = nxt[u]){
		if(!cap[u]) continue;
		int v = to[u];
		if(!dfn[v]) tarjan(v),low[x] = std :: min(low[x],low[v]);
		else if(vis[v]) low[x] = std :: min(low[x],dfn[v]);
	}

	if(low[x] == dfn[x]){
		scc++;
		while(x != stk[top + 1]) vis[stk[top]] = 0,ddf[stk[top--]] = scc;
	}
}

int main(){
	int x,y,z;
	scanf("%d%d%d%d",&n,&m,&S,&T);
	for(int i = 1;i <= m;i++) scanf("%d%d%d",&x,&y,&z),ins(x,y,z);

	dinic();
	
	for(int i = 1;i <= n;i++)
		if(!dfn[i]) tarjan(i);
	
	for(int i = 2;i <= cnt;i += 2){
		if(!cap[i] && ddf[frm[i]] == ddf[S] && ddf[to[i]] == ddf[T]) puts("1 1");
		else if(!cap[i] && ddf[frm[i]] != ddf[to[i]]) puts("1 0");
		else puts("0 0");
	}
		
	return 0;
}
