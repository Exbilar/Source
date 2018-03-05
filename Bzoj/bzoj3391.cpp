#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int dfn[maxm],low[maxm],size[maxm],ans[maxm];
int fst[maxm],to[maxm],nxt[maxm];
int cnt,sz,n,m,fans;

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
}

void tarjan(int x){
	size[x] = 1;
	low[x] = dfn[x] = ++sz;

	int tmp = 0,res = n - 1;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(!dfn[v]){
			tarjan(v);
			size[x] += size[v];
			low[x] = std :: min(low[x],low[v]);
			if(low[v] >= dfn[x]) tmp = std :: max(size[v],tmp),res -= size[v];
		}
		else low[x] = std :: min(low[x],dfn[v]);
	}

	tmp = std :: max(tmp,res);

	if(tmp <= n / 2) fans = 1,ans[x] = 1;
	
}

int main(){
	int x,y;
	scanf("%d",&n);
	for(int i = 1;i < n;i++) scanf("%d%d",&x,&y),ins(x,y),ins(y,x);

	for(int i = 1;i <= n;i++)
		if(!dfn[i]) tarjan(i);

	if(!fans) return puts("NONE"),0;

	for(int i = 1;i <= n;i++)
		if(ans[i]) printf("%d\n",i);
	
	return 0;
}
