#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;

template <class T> inline bool chkmax (T &x, T y) {
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin (T &x, T y) {
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in) {
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if (ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

int fst[maxm],nxt[maxm << 1],to[maxm << 1];
int _fst[maxm],_nxt[maxm << 1],_to[maxm << 1];
int ftr[maxm],dpt[maxm],dfn[maxm];
LL _val[maxm << 1];
int cnt,_cnt,n,m;

inline void ins(int f,int t) {
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

inline void _ins(int f,int t,LL v) {
	if(f == t) return ;
	_nxt[++_cnt] = _fst[f],_to[_cnt] = t,_val[_cnt] = v,_fst[f] = _cnt;
	_nxt[++_cnt] = _fst[t],_to[_cnt] = f,_val[_cnt] = v,_fst[t] = _cnt;
}

namespace __DFS__ {
	int son[maxm],size[maxm],top[maxm];
	int sz;
	
	void dfs1(int x) {
		size[x] = 1,dfn[x] = ++sz;
		for(int u = fst[x];u;u = nxt[u]) {
			int v = to[u];
			if(v == ftr[x]) continue;
			ftr[v] = x,dpt[v] = dpt[x] + 1;
			dfs1(v);
			size[x] += size[v];
			if(size[son[x]] < size[v]) son[x] = v;
		}
	}

	void dfs2(int x,int chain) {
		top[x] = chain;
		if(son[x]) dfs2(son[x],chain);
		for(int u = fst[x];u;u = nxt[u]) {
			if(to[u] != son[x] && to[u] != ftr[x]) dfs2(to[u],to[u]);
		}
	}
	
}

int LCA(int x,int y){
	using namespace __DFS__;
	while(top[x] != top[y]){
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		x = ftr[top[x]];
	}
	return dpt[x] < dpt[y] ? x : y;
}

namespace Sol {
	int stk[maxm],Nds[maxm],vis[maxm];
	LL f[maxm],smin[maxm],smax[maxm],size[maxm];
	LL top,ans1,ans2,K,sz,tot;

	bool cmp(const int &x,const int &y){
		return dfn[x] < dfn[y];
	}
	
	void buildVirtualTree() {
		read(K); _cnt = 0,top = 0;
		for(int i = 1;i <= K;i++) read(Nds[i]),vis[Nds[i]] = 1;
		std :: sort(Nds + 1,Nds + K + 1,cmp);
		stk[++top] = 1;

		for(int i = 1;i <= K;i++) {
			int cur = Nds[i],lca = LCA(cur,stk[top]);
			while(dpt[stk[top]] > dpt[lca]) {
				if(dpt[stk[top - 1]] < dpt[lca]) {
					_ins(lca,stk[top],dpt[stk[top]] - dpt[lca]);
					stk[top] = lca;
				}
				else _ins(stk[top - 1],stk[top],dpt[stk[top]] - dpt[stk[top - 1]]),top--;
			}
			if(stk[top] != cur) stk[++top] = cur;
		}
		
		while(--top) {
			_ins(stk[top],stk[top + 1],dpt[stk[top + 1]] - dpt[stk[top]]);
		}
		
	}

	void _dfs(int x,int fa) {
		size[x] = vis[x]; f[x] = 0;
		
		if(vis[x]) smax[x] = 0,smin[x] = 0;
		else smax[x] = -INF,smin[x] = INF;

		for(int u = _fst[x];u;u = _nxt[u]) {
			int v = _to[u];
			if(v == fa) continue;
			_dfs(v,x);
			tot += f[x] * size[v] + f[v] * size[x] + _val[u] * size[x] * size[v];
			size[x] += size[v];
			f[x] += f[v] + _val[u] * size[v];
			chkmin(ans1,smin[x] + smin[v] + _val[u]);
			chkmax(ans2,smax[x] + smax[v] + _val[u]);
			chkmax(smax[x],smax[v] + _val[u]);
			chkmin(smin[x],smin[v] + _val[u]);
		}		
		_fst[x] = 0;
	}

	void solve() {
		buildVirtualTree();
		tot = 0,ans1 = INF,ans2 = -INF;
		_dfs(1,0);
		printf("%lld %lld %lld\n",tot,ans1,ans2);
		for(int i = 1;i <= K;i++) vis[Nds[i]] = 0;
	}
}


int main() {

	read(n);

	int u,v;
	for(int i = 1;i < n;i++) {
		read(u),read(v),ins(u,v);
	}

	read(m);

	__DFS__ :: dfs1(1);
	__DFS__ :: dfs2(1,1);

	while(m--){
		Sol :: solve();
	}

	return 0;
}
