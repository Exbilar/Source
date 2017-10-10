#include <queue>
#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

using std :: queue;

int low[maxm],dfn[maxm],ddf[maxm],stk[maxm],vis[maxm],f[maxm],val[maxm],_val[maxm],inq[maxm];
int fst[maxm],to[maxm],nxt[maxm],_fst[maxm],_nxt[maxm],_to[maxm],bar[maxm];
int top,cnt,_cnt,scc,sz,n,m,S,P,ans;

queue<int> Q;

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
}

void _ins(int f,int t){
	_nxt[++_cnt] = _fst[f];
	_to[_cnt] = t;
	_fst[f] = _cnt;
}

void tarjan(int x){
	vis[x] = 1;
	stk[++top] = x;
	low[x] = dfn[x] = ++sz;

	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(!dfn[v]) tarjan(v),low[x] = std :: min(low[x],low[v]);
		else if(vis[v]) low[x] = std :: min(low[x],dfn[v]);
	}

	if(low[x] == dfn[x]){
		scc++;
		while(stk[top + 1] != x){
			vis[stk[top]] = 0;
			_val[scc] += val[stk[top]];
			ddf[stk[top--]] = scc;
		}
	}
	
}

void rebuild(){
	for(int i = 1;i <= n;i++){
		for(int u = fst[i];u;u = nxt[u]){
			int v = to[u];
			if(ddf[v] != ddf[i]) _ins(ddf[i],ddf[v]);
		}
	}
}

void SPFA(){
	f[ddf[S]] = _val[ddf[S]];
	Q.push(ddf[S]);
	inq[ddf[S]] = 1;

	while(!Q.empty()){
		int x = Q.front(); Q.pop();
		inq[x] = 0;
		for(int u = _fst[x];u;u = _nxt[u]){
			int v = _to[u];
			if(f[v] < f[x] + _val[v]){
				f[v] = f[x] + _val[v];
				if(!inq[v]){
					Q.push(v);
					inq[v] = 1;
				}
			}
		}
	}
	
}

int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++)
		scanf("%d%d",&x,&y),ins(x,y);

	for(int i = 1;i <= n;i++) scanf("%d",&val[i]);
	scanf("%d%d",&S,&P);
	for(int i = 1;i <= P;i++) scanf("%d",&bar[i]);

	for(int i = 1;i <= n;i++)
		if(!dfn[i]) tarjan(i);

	rebuild();
	SPFA();

	for(int i = 1;i <= P;i++)
		ans = std :: max(ans,f[ddf[bar[i]]]);

	printf("%d\n",ans);
	
	return 0;
}
