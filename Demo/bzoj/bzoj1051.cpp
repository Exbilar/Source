#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int fst[maxm],nxt[maxm],to[maxm],_fst[maxm],_nxt[maxm],_to[maxm];
int stk[maxm],low[maxm],dfn[maxm],vis[maxm],ddf[maxm],size[maxm];
int top,cnt,_cnt,scc,sz,n,m;

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
	stk[++top] = x;
	vis[x] = 1;
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
		while(x != stk[top + 1])
			vis[stk[top]] = 0,size[scc]++,ddf[stk[top--]] = scc;
	}
}

void rebuild(){
	for(int i = 1;i <= n;i++){
		for(int u = fst[i];u;u = nxt[u]){
			int v = to[u];
			if(ddf[i] != ddf[v]) _ins(ddf[i],ddf[v]);
		}
	}
}

int main(){
	int u,v;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++) scanf("%d%d",&u,&v),ins(u,v);
	
	for(int i = 1;i <= n;i++)
		if(!dfn[i]) tarjan(i);

	rebuild();

	int ans = 0;
	for(int i = 1;i <= scc;i++){
		if(!_fst[i]){
			if(ans) return puts("0"),0;
			else ans = size[i];
		}
	}
	
	printf("%d\n",ans);
	
	return 0;
}
