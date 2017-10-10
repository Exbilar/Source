#include <cstdio>
#include <algorithm>

static const int maxm = 1e3 + 10;

int fst[maxm],to[maxm],nxt[maxm],_fst[maxm],_to[maxm],_nxt[maxm];
int stk[maxm],low[maxm],dfn[maxm],ddf[maxm],vis[maxm],f[maxm][maxm];
int val[maxm],_val[maxm],w[maxm],_w[maxm],ind[maxm];
int top,cnt,_cnt,sz,scc,n,m;

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
}

void _ins(int f,int t){
	ind[t] = 1;
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
		if(!dfn[v])
			tarjan(v),low[x] = std :: min(low[x],low[v]);
		else if(vis[v])
			low[x] = std :: min(low[x],dfn[v]);
	}

	if(low[x] == dfn[x]){
		scc++;
		while(stk[top + 1] != x){
			vis[stk[top]] = 0;
			_val[scc] += val[stk[top]];
			_w[scc] += w[stk[top]];
			ddf[stk[top--]] = scc;
		}
	}
}

void rebuild(){
	for(int i = 1;i <= n;i++){
		for(int u = fst[i];u;u = nxt[u]){
			int v = to[u];
			if(ddf[i] != ddf[v])
				_ins(ddf[i],ddf[v]);
		}
	}
	
	for(int i = 1;i <= scc;i++)
		if(!ind[i]) _ins(scc + 1,i);
}

void dfs(int x){
	for(int u = _fst[x];u;u = _nxt[u]){
		int v = _to[u];
		dfs(v);
		for(int i = m - _w[x];i >= 0;i--){
			for(int j = 0;j <= i;j++){
				f[x][i] = std :: max(f[x][i],f[x][j] + f[v][i - j]);
			}
		}
	}
	
	for(int i = m;i >= 0;i--){
		if(i >= _w[x]) f[x][i] = f[x][i - _w[x]] + _val[x];
		else f[x][i] = 0;
	}
}

int main(){
	int in;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&w[i]);
	for(int i = 1;i <= n;i++) scanf("%d",&val[i]);
	for(int i = 1;i <= n;i++){
		scanf("%d",&in);
		if(in) ins(in,i);
	}

	for(int i = 1;i <= n;i++)
		if(!dfn[i]) tarjan(i);

	rebuild();

	dfs(scc + 1);

	printf("%d\n",f[scc + 1][m]);
	
	return 0;
}
