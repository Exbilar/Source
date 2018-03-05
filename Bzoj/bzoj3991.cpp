#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

using std :: max;
using std :: min;
using std :: set;

typedef long long LL;

static const LL INF = 1 << 30;
static const LL oo = 1LL << 62;
static const LL maxm = 1e6 + 10;

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

LL fst[maxm],nxt[maxm],to[maxm],dpt[maxm],has[maxm];
LL dfn[maxm],top[maxm],size[maxm],son[maxm],ftr[maxm];
LL val[maxm],dis[maxm];
LL n,m,cnt,sz;

LL ans;

struct DFN {
	bool operator () (const LL x,const LL y) const {
		return dfn[x] < dfn[y];
	}
};

set<LL,DFN> S;

typedef set<LL,DFN> :: iterator itr;

void ins(LL f,LL t,LL v) {
	nxt[++cnt] = fst[f],to[cnt] = t,val[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,val[cnt] = v,fst[t] = cnt;
}

void dfs1(LL x) {
	dfn[x] = ++sz; size[x] = 1;
	for(LL u = fst[x];u;u = nxt[u]) {
		LL v = to[u];
		if(v == ftr[x]) continue;
		ftr[v] = x,dpt[v] = dpt[x] + 1;
		dis[v] = dis[x] + val[u];
		dfs1(v);
		size[x] += size[v];
		if(size[son[x]] < size[v]) son[x] = v;
	}
}

void dfs2(LL x,LL chain) {
	top[x] = chain;
	if(son[x]) dfs2(son[x],chain);
	for(LL u = fst[x];u;u = nxt[u]) {
		if(to[u] != son[x] && to[u] != ftr[x]) dfs2(to[u],to[u]);
	}
}

LL LCA(LL x,LL y) {
	while(top[x] != top[y]) {
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		x = ftr[top[x]];
	}
	return dpt[x] < dpt[y] ? x : y;
}

LL getPre(LL x) {
	itr it = S.find(x);
	return it == S.begin() ? 0 : *(--it);
}

LL getNxt(LL x) {
	itr it = S.find(x);
	return ++it == S.end() ? 0 : *it;
}

LL getDis(LL x,LL y) {
	if(x * y == 0) return 0;
	return dis[x] + dis[y] - 2 * dis[LCA(x,y)];
}

void addNode(LL x) {
	S.insert(x);
	LL l = getPre(x),r = getNxt(x);
	ans -= getDis(l,r);
	ans += getDis(l,x) + getDis(x,r);
}

void delNode(LL x) {
	LL l = getPre(x),r = getNxt(x);
	ans -= getDis(l,x) + getDis(x,r);
	ans += getDis(l,r);
	S.erase(x);
}

LL ___() {
	return getDis(*S.rbegin(),*S.begin());
}

int main() {

	read(n),read(m);

	LL u,v,w;
	for(LL i = 1;i < n;i++) {
		read(u),read(v),read(w);
		ins(u,v,w);
	}

	dfs1(1),dfs2(1,1);
	
	while(m--) {
		read(u);
		has[u] ^= 1;
		if(has[u]) addNode(u);
		else delNode(u);
		printf("%lld\n",ans + ___());
	}

	return 0;
}
