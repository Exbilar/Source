#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: vector;
using std :: make_pair;

typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 4e5 + 10;

template <class T> inline bool chkmax(T &x, T y) {
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x, T y) {
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in) {
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if (ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

int fst[maxm],nxt[maxm],to[maxm],val[maxm],size[maxm],sizmax[maxm];
int vis[maxm],ftr[maxm];
int cnt,rt,__sum,p;

struct Element {
	LL x,y;

	Element() {}
	Element(LL _,LL __) {x = _; y = __;}
	
	bool operator < (const Element &rhs) const {
		return x == rhs.x ? y < rhs.y : x < rhs.x;
	}

	Element operator - (const Element &rhs) const {
		return Element(x - rhs.x,y - rhs.y);
	}
};

typedef vector<Element> van;

namespace __DFS__ {
	int size[maxm],son[maxm],dpt[maxm],top[maxm],ftr[maxm];
	LL dis[maxm];

	void dfs1(int x) {
		size[x] = 1;
		for(int u = fst[x];u;u = nxt[u]) {
			int v = to[u];
			if(v == ftr[x]) continue;
			ftr[v] = x,dpt[v] = dpt[x] + 1;
			dis[v] = dis[x] + val[u];
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

	int LCA(int x,int y) {
		while(top[x] != top[y]) {
			if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
			x = ftr[top[x]];
		}
		return dpt[x] < dpt[y] ? x : y;
	}
	
}

void ins(int f,int t,int v) {
	nxt[++cnt] = fst[f],to[cnt] = t,val[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,val[cnt] = v,fst[t] = cnt;
}

void getRoot(int x,int fa) {
	size[x] = 1; sizmax[x] = 0;
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(vis[v] || v == fa) continue;
		getRoot(v,x);
		size[x] += size[v];
		chkmax(sizmax[x],size[v]);
	}
	chkmax(sizmax[x],__sum - size[x]);
	if(sizmax[x] < sizmax[rt]) rt = x;
}

LL getDis(int x,int y) {
	using namespace __DFS__;
	return dis[x] + dis[y] - 2 * dis[LCA(x,y)];
}

int xi[maxm];

van boy1[maxm],boy2[maxm];

int n,m;

void dfs(int x,int fa,int dpt,van &ddf) {
	ddf.push_back(Element(xi[x],dpt));
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(vis[v] || v == fa) continue;
		dfs(v,x,dpt + val[u],ddf);
	}
}

void transform(int x) {
	vis[x] = 1; dfs(x,0,0,boy1[x]);
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(vis[v]) continue;
		rt = 0; __sum = size[v];
		getRoot(v,x); ftr[rt] = x;
		dfs(v,0,val[u],boy2[rt]);
		transform(rt);
	}
}

void solve(van &ddf) {
	ddf.push_back(Element(-1,0));
	std :: sort(ddf.begin(),ddf.end());
	for(int i = 1;i < (int) ddf.size();i++) {
		ddf[i].y += ddf[i - 1].y;
	}
}

Element query(int L,int R,van &ddf) {
	using std :: lower_bound;
	if(ddf.empty()) return Element(0,0);
	int l = lower_bound(ddf.begin(),ddf.end(),Element(L,0)) - ddf.begin();
	int r = lower_bound(ddf.begin(),ddf.end(),Element(R + 1,0)) - ddf.begin();
	l--; r--;
	return Element(ddf[r].y - ddf[l].y,r - l);
}

int main() {

	read(n); read(m); read(p);
	for(int i = 1;i <= n;i++) read(xi[i]);

	int u,v,w;
	for(int i = 1;i < n;i++) {
		read(u); read(v); read(w); ins(u,v,w);
	}

	__DFS__ :: dfs1(1);
	__DFS__ :: dfs2(1,1);

	rt = 0; sizmax[0] = INF; __sum = n;
	getRoot(1,0);
	transform(rt);

	for(int i = 1;i <= n;i++) {
		solve(boy1[i]); solve(boy2[i]);
	}

	LL lstans = 0;
	lstans = query(u,v,boy1[w]).x;
	while(m--) {
		read(w); read(u); read(v);
		u = (u + lstans) % p;
		v = (v + lstans) % p;
		if(u > v) std :: swap(u,v);
		
		lstans = query(u,v,boy1[w]).x;
		
		for(int i = w;ftr[i];i = ftr[i]) {
			Element tmp = query(u,v,boy1[ftr[i]]) - query(u,v,boy2[i]);
			lstans += tmp.x + 1LL * tmp.y * getDis(w,ftr[i]);
		}
		
		printf("%lld\n",lstans);
	}

	return 0;
}
