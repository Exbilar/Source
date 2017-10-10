#include <bitset>
#include <cstdio>
#include <algorithm>

using std :: bitset;

static const int maxm = 3e3 + 10;
static const int maxn = 4e6 + 10;

int low[maxm],dfn[maxm],stk[maxm],vis[maxm],ddf[maxm],size[maxm];
int fst[maxn],nxt[maxn],to[maxn];
int cnt,_cnt,scc,sz,top,n,ans;

bitset<maxm> bit[maxm];

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
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
		while(x != stk[top + 1])
			vis[stk[top]] = 0,size[scc]++,ddf[stk[top--]] = scc;
	}
	
}

int main(){
	int in;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			scanf("%1d",&in);
			if(in) ins(i,j);
		}
	}
	
	for(int i = 1;i <= n;i++)
		if(!dfn[i]) tarjan(i);

	for(int i = 1;i <= n;i++)
		bit[ddf[i]][i] = 1;

	for(int i = 1;i <= scc;i++){
		ans += size[i] * size[i];
		bitset<maxm> tmp;
		for(int x = 1;x <= n;x++){
			if(ddf[x] == i){
				for(int u = fst[x];u;u = nxt[u]){
					int v = to[u];
					if(ddf[v] != i) tmp |= bit[ddf[v]];
				}
			}
		}
		ans += size[i] * tmp.count();
		bit[i] |= tmp;
	}

	printf("%d\n",ans);
	
	return 0;
}
