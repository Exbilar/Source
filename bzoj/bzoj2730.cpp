#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

static const int maxm = 1e6 + 10;

int ddf[maxm],low[maxm],dfn[maxm],vis[maxm],size[maxm],cut[maxm],pt[maxm],num[maxm];
int fst[maxm],to[maxm],nxt[maxm];
int cnt,n,m,sz;

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
}

void tarjan(int x,int fa){
	low[x] = dfn[x] = ++sz;
	int son = 0;
	
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == fa) continue;
		if(!dfn[v]){
			tarjan(v,x),son++;
			low[x] = min(low[x],low[v]);
			if(dfn[x] <= low[v] && fa) cut[x] = 1;
		}
		else low[x] = min(low[x],dfn[v]);
	}
	
	if(!fa && son > 1) cut[1] = 1;
}

void dfs(int x,int col){
	ddf[x] = col;
	size[ddf[x]]++;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(ddf[v] || cut[v]) continue;
		dfs(v,col);
	}
}

void init(){
	cnt = 0,sz = 0,n = 0;
	memset(fst,0,sizeof fst);
	memset(nxt,0,sizeof nxt);
	memset(to,0,sizeof to);
	memset(size,0,sizeof size);
	memset(dfn,0,sizeof dfn);
	memset(cut,0,sizeof cut);
	memset(ddf,0,sizeof ddf);
	memset(low,0,sizeof low);
	memset(dfn,0,sizeof dfn);
	memset(pt,0,sizeof pt);
	memset(num,0,sizeof num);
}

int main(){
	int x,y,cas = 0;
	while(scanf("%d",&m) != EOF && m){
		init();
		for(int i = 1;i <= m;i++){
			scanf("%d%d",&x,&y);
			n = max(n,x),n = max(n,y);
			ins(x,y),ins(y,x);
			pt[x] = pt[y] = 1;
		}

		for(int i = 1;i <= n;i++)
			if(!dfn[i]) tarjan(i,0);

		for(int i = 1;i <= n;i++)
			if(!ddf[i] && !cut[i]) dfs(i,i);

		for(int i = 1;i <= n;i++)
			if(cut[i]){
				for(int u = fst[i];u;u = nxt[u]){
					int v = to[u];
					if(!vis[ddf[v]]) vis[ddf[v]] = 1,num[ddf[v]]++;
				}
				memset(vis,0,sizeof vis);
			}

		LL tot = 0,ans = 1;
		for(int i = 1;i <= n;i++)
			if(num[i] == 1) tot++,ans *= size[i];

		if(!tot){
			for(int i = 1;i <= n;i++) if(pt[i]) tot++;
			
			printf("Case %d: 2 %lld\n",++cas,tot * (tot - 1) >> 1);
			continue;
		}

		printf("Case %d: %lld %lld\n",++cas,tot,ans);
		
	}

	return 0;
}
