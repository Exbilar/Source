#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int stk[maxm],vis[maxm],low[maxm],dfn[maxm],ddf[maxm],size[maxm],ind[maxm];
int fst[maxm],nxt[maxm],to[maxm],_fst[maxm],_nxt[maxm],_to[maxm];
int top,cnt,_cnt,sz,scc,n,m,ans;

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
}

void _ins(int f,int t){
	ind[t]++;
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
			size[scc]++;
            vis[stk[top]] = 0;
            ddf[stk[top--]] = scc;
        }
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

bool chk(int x){
	if(size[x] != 1 || ind[x] != 0) return false;
	
	for(int u = _fst[x];u;u = _nxt[u])
		if(ind[_to[u]] == 1) return false;
	
	return true;
}

int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++) scanf("%d%d",&x,&y),ins(x,y);

	for(int i = 1;i <= n;i++)
		if(!dfn[i]) tarjan(i);

	rebuild();

	for(int i = 1;i <= scc;i++)
		if(!ind[i]) ans++;

	for(int i = 1;i <= scc;i++)
		if(chk(i)){ans--;break;}

	printf("%.6lf\n",(double) (n - ans) / n);

	return 0;
}
