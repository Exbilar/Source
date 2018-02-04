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

int fst[maxm],nxt[maxm << 1],to[maxm << 1],dfn[maxm];
int _fst[maxm],_nxt[maxm << 1],_to[maxm << 1];
int dpt[maxm],ftr[maxm],top[maxm],size[maxm],son[maxm];

int stk[maxm],h[maxm];

LL f[maxm],dis[maxm],val[maxm];

int cnt,_cnt,n,m,tp,sz;

bool cmp(const int &x,const int &y){
	return dfn[x] < dfn[y];
}

inline void ins(int f,int t,int v) {
	nxt[++cnt] = fst[f],to[cnt] = t,val[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,val[cnt] = v,fst[t] = cnt;
}

inline void _ins(int f,int t) {
	if(f == t) return ;
	_nxt[++_cnt] = _fst[f],_to[_cnt] = t,_fst[f] = _cnt;
}

void dfs1(int x) {
	size[x] = 1;
	dfn[x] = ++sz;
	for(RG int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(v == ftr[x]) continue;
		ftr[v] = x,dpt[v] = dpt[x] + 1;
		dis[v] = min(dis[x],val[u]);
		dfs1(v);
		size[x] += size[v];
		if(size[son[x]] < size[v]) son[x] = v;
	}
}

void dfs2(int x,int chain) {
	top[x] = chain;
	if(son[x]) dfs2(son[x],chain);
	for(int u = fst[x];u;u = nxt[u]) {
		if(to[u] != ftr[x] && to[u] != son[x]) dfs2(to[u],to[u]);
	}
}

inline int LCA(int x,int y) {
	while(top[x] != top[y]) {
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		x = ftr[top[x]];
	}
	return dpt[x] < dpt[y] ? x : y;
}

void _dfs(int x,int fa) {
	f[x] = dis[x];
	LL tmp = 0;
	for(RG int u = _fst[x];u;u = _nxt[u]) {
		int v = _to[u];
		if(v == fa) continue;
		_dfs(v,x);
		tmp += f[v];
	}
	_fst[x] = 0;
	if(tmp) chkmin(f[x],tmp);
}

inline void solve() {
	int tot = 0,K = 0; _cnt = 0;
	
	read(K);
	for(RG int i = 1;i <= K;i++) read(h[i]);

	std :: sort(h + 1,h + K + 1,cmp);
	
	h[++tot] = h[1];

	for(RG int i = 2;i <= K;i++)
		if(LCA(h[tot],h[i]) != h[tot]) h[++tot] = h[i];
	
	stk[++tp] = 1;
	
	for(RG int i = 1;i <= tot;i++) {
		int cur = h[i],lca = LCA(cur,stk[tp]);
		while(true) {
			if(dpt[lca] >= dpt[stk[tp - 1]]) {
				_ins(lca,stk[tp--]);
				if(stk[tp] != lca) stk[++tp] = lca;
				break;
			}
			_ins(stk[tp - 1],stk[tp]),tp--;
		}
		if(stk[tp] != cur) stk[++tp] = cur;
	}
	while(--tp) _ins(stk[tp],stk[tp + 1]);
	_dfs(1,0);
	printf("%lld\n",f[1]);
}

int main() {

	freopen("bzoj2286.in","r",stdin);

	read(n);

	int x,y,v;
	for(RG int i = 1;i < n;i++) {
		read(x),read(y),read(v);
		ins(x,y,v);
	}

	dis[1] = oo;
	dfs1(1),dfs2(1,1);

	read(m);
	for(int i = 1;i <= m;i++) solve();

	return 0;
}
