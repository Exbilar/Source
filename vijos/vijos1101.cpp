#include <cstdio>
#include <vector>
#include <algorithm>

using std :: max;
using std :: min;
using std :: vector;

static const int maxm = 1e6 + 10;

int fst[maxm],nxt[maxm],to[maxm];
int vis[maxm],size[maxm],ftr[maxm],dfn[maxm],fnl[maxm];
int n,m,cnt,sz,ans;

vector<int> vec[maxm];

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

void dfs(int x,int dpt){
	size[x] = 1; dfn[x] = ++sz;
	vec[dpt].push_back(x);
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == ftr[x]) continue;
		ftr[v] = x;
		dfs(v,dpt + 1);
		size[x] += size[v];
	}
	fnl[x] = sz;
}

void mark(int l,int r,int v){
	for(int i = l;i <= r;i++) vis[i] = v;
}

void _dfs(int dpt,int res){
	for(int i = 0;i < vec[dpt].size();i++){
		int v = vec[dpt][i];
		if(vis[dfn[v]]) continue;
		mark(dfn[v],fnl[v],1);
		_dfs(dpt + 1,res + size[v]);
		mark(dfn[v],fnl[v],0);
	}
	ans = max(ans,res);
}

int main(){
	int u,v;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++) scanf("%d%d",&u,&v),ins(u,v);
	
	dfs(1,0);
	_dfs(1,0);
	
	printf("%d\n",n - ans);
	
	return 0;
}
