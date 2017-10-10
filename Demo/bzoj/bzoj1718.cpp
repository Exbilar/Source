#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 5e3 + 10;

int stk[maxm],low[maxm],dfn[maxm],vis[maxm],ddf[maxm];
int fst[maxm],to[maxm],nxt[maxm],outd[maxm],conct[maxm][maxm];
int top,cnt,sz,scc,n,m,ans;

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	fst[f] = cnt;
	to[cnt] = t;
}

void tarjan(int x,int fa){
    vis[x] = 1;
    stk[++top] = x;
    low[x] = dfn[x] = ++sz;
 
    for(int u = fst[x];u;u = nxt[u]){
        int v = to[u];
		if(v == fa) continue;
        if(!dfn[v]) tarjan(v,x),low[x] = std :: min(low[x],low[v]);
        else if(vis[v]) low[x] = std :: min(low[x],dfn[v]);
    }
 
    if(low[x] == dfn[x]){
        scc++;
        while(stk[top + 1] != x)
            vis[stk[top]] = 0,ddf[stk[top--]] = scc;
    }
}

void rebuild(){
	for(int i = 1;i <= n;i++){
		for(int u = fst[i];u;u = nxt[u]){
			int v = to[u];
			if(ddf[i] != ddf[v]) outd[ddf[i]]++,outd[ddf[v]]++;
		}
	}
}

int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++){
		scanf("%d%d",&x,&y);
		if(!conct[x][y] && !conct[y][x]) ins(x,y),ins(y,x);
		conct[x][y] = conct[y][x] = 1;
	}
	for(int i = 1;i <= n;i++)
		if(!dfn[i]) tarjan(i,0);

	rebuild();

	for(int i = 1;i <= scc;i++)
		if(outd[i] == 2) ans++;
		
	printf("%d\n",(ans + 1) >> 1);
	
	return 0;
}
