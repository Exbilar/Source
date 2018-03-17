#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: string;
using std :: make_pair;

typedef long long LL;
typedef pair<LL, LL> pll;
typedef pair<int, int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 1e6 + 10;

template <class T> inline bool chkmax(T &x, T y) {
    return x < y ? x = y, true : false;
}

template <class T> inline bool chkmin(T &x, T y) {
    return x > y ? x = y, true : false;
}

template <class T> inline void read (T &in) {
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if (ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

string procStatus(){
    std :: ifstream t("/proc/self/status");
    return string(std :: istreambuf_iterator<char> (t),
				  std :: istreambuf_iterator<char> ());
}

int fst[maxm], nxt[maxm], to[maxm], posl[maxm], posr[maxm];
LL val[maxm], sum[maxm], sig[maxm], add[maxm], wi[maxm];
int ftr[maxm], ch[maxm][2], size[maxm];

int cnt, sz, dfn = 1, n, m, rt;

void ins(int f, int t) {
	nxt[++cnt] = fst[f], to[cnt] = t, fst[f] = cnt;
	nxt[++cnt] = fst[t], to[cnt] = f, fst[t] = cnt;
}

void dfs(int x, int fa) {
	sig[++dfn] = 1; posl[x] = dfn; val[dfn] = wi[x];
	for(int u = fst[x]; u; u = nxt[u]) {
		int v = to[u];
		if(v == fa) continue;
		dfs(v, x);
	}
	sig[++dfn] = -1; posr[x] = dfn; val[dfn] = wi[x];
}

#define lc ch[x][0]
#define rc ch[x][1]

int get(int x) {
	return ch[ftr[x]][1] == x;
}

void upt(int x) {
	size[x] = size[lc] + size[rc] + sig[x];
	sum[x] = sum[lc] + sum[rc] + val[x] * sig[x];
}

void pushadd(int x, LL v) {
	sum[x] += size[x] * v; val[x] += v; add[x] += v;
}

void pushdown(int x) {
	if(add[x]) {
		if(lc) pushadd(lc, add[x]);
		if(rc) pushadd(rc, add[x]);
		add[x] = 0;
	}
}

void downbtm(int x) {
	if(ftr[x]) downbtm(ftr[x]);
	pushdown(x);
}

void rotate(int x) {
	int fa = ftr[x], gnd = ftr[fa], f = get(x);
	if(gnd) ch[gnd][get(fa)] = x;
	ch[fa][f] = ch[x][f ^ 1], ftr[ch[x][f ^ 1]] = fa;
	ch[x][f ^ 1] = fa, ftr[fa] = x, ftr[x] = gnd;
	upt(fa); upt(x);
}

void splay(int x, int k) {
	downbtm(x);
	for(int fa = 0; (fa = ftr[x]) != k; rotate(x))
		if(ftr[fa] != k) rotate(get(fa) == get(x) ? fa : x);
	if(!k) rt = x;
}

void build(int &x, int l, int r, int fa) {
	if(l > r) return ;
	int mid = (l + r) >> 1;
	x = mid; ftr[x] = fa;
	build(lc, l, mid - 1, x);
	build(rc, mid + 1, r, x);
	upt(x);
}

int findPre(int x) {
	if(x != rt) splay(x, 0);
	x = ch[x][0];
	while(ch[x][1]) x = ch[x][1];
	return x;
}

int findNxt(int x) {
	if(x != rt) splay(x, 0);
	x = ch[x][1];
	while(ch[x][0]) x = ch[x][0];
	return x;
}

void modify(int x, LL v) {
	int xx = findPre(posl[x]), yy = findNxt(posr[x]);
	splay(xx, 0); splay(yy, xx);
	pushadd(ch[yy][0], v);
}

void relink(int x, int y) {
	int xx = findPre(posl[x]), yy = findNxt(posr[x]);
	splay(xx, 0); splay(yy, rt);
	int k = ch[yy][0];
	ftr[k] = 0, ch[yy][0] = 0;
	upt(yy); upt(rt);

	splay(posl[y], 0); splay(yy = findNxt(posl[y]), rt);
	ch[yy][0] = k; ftr[k] = yy;
	upt(yy); upt(rt);
}

LL Query(int x) {
	splay(findNxt(posl[x]), 0);
	return sum[ch[rt][0]];
}

char str[10];

int main() {

#ifndef ONLINE_JUDGE
	freopen("bzoj3786.in", "r", stdin);
#endif
	
	read(n);
	for(int i = 2, u; i <= n; i++) read(u), ins(u, i);
	for(int i = 1; i <= n; i++) read(wi[i]);

	dfs(1, 0);
	build(rt, 1, dfn + 1, 0);

	read(m);

	LL x, y;
	
	while(m--) {
		scanf("%s", str);
		if(str[0] == 'Q') read(x), printf("%lld\n", Query(x));
		if(str[0] == 'C') read(x), read(y), relink(x, y);
		if(str[0] == 'F') read(x), read(y), modify(x, y);
	}

	return 0;
}
