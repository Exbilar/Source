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

static const int INF = 1e9 + 7;
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
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

string procStatus(){
    std :: ifstream t("/proc/self/status");
    return string(std :: istreambuf_iterator<char> (t),
				  std :: istreambuf_iterator<char> ());
}

int fst[maxm], nxt[maxm], to[maxm], pos[maxm];
int OP[maxm], ED[maxm], ftr[maxm], top[maxm], size[maxm], son[maxm];

LL f[maxm], g[maxm], w[maxm];

int cnt, n, m, sz;

void ins(int f, int t) {
	nxt[++cnt] = fst[f], to[cnt] = t, fst[f] = cnt;
	nxt[++cnt] = fst[t], to[cnt] = f, fst[t] = cnt;
}

void dfs1(int x) {
	size[x] = 1; f[x] = w[x];
	LL sum = 0;
	for(int u = fst[x]; u; u = nxt[u]) {
		int v = to[u];
		if(v == ftr[x]) continue;
		ftr[v] = x;
		dfs1(v);
		size[x] += size[v]; sum += f[v];
		if(size[son[x]] < size[v]) son[x] = v;
	}
	g[x] = sum ? sum : INF;
	chkmin(f[x], g[x]);
}

void dfs2(int x, int chain) {
	top[x] = chain; OP[x] = ++sz; pos[sz] = x;
	if(son[x]) dfs2(son[x], chain);
	for(int u = fst[x]; u; u = nxt[u]) {
		if(to[u] != son[x] && to[u] != ftr[x]) dfs2(to[u], to[u]);
	}
	ED[x] = sz;
}

LL add[maxm], E[maxm];

void pushup(int x) {
	E[x] = min(E[x << 1], E[x << 1 | 1]);
}

void pushadd(int x, LL v) {
	E[x] -= v; add[x] += v;
}

void pushdown(int x) {
	if(add[x]) {
		pushadd(x << 1, add[x]);
		pushadd(x << 1 | 1, add[x]);
		add[x] = 0;
	}
}

void build(int x, int l, int r) {
	if(l == r) return E[x] = w[pos[l]] - g[pos[l]], void();
	int mid = (l + r) >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
	pushup(x);
}

LL Query(int x, int l, int r, int pos) {
	if(l == r) return E[x];
	pushdown(x);
	int mid = (l + r) >> 1;
	if(pos <= mid) return Query(x << 1, l, mid, pos);
	else return Query(x << 1 | 1, mid + 1, r, pos);
}

int modify(int x, int l, int r, int L, int R, LL v) {
	if(l == r) {
		pushadd(x, v);
		return E[x] <= 0 ? pos[l] : 0;
	}
	if(l == L && r == R && E[x] > v) {
		pushadd(x, v);
		return 0;
	}
	pushdown(x);
	int mid = (l + r) >> 1, res = 0;
	if(R <= mid) res = modify(x << 1, l, mid, L, R, v);
	else if(L > mid) res = modify(x << 1 | 1, mid + 1, r, L, R, v);
	else {
		res = modify(x << 1 | 1, mid + 1, r, mid + 1, R, v);
		if(!res) res = modify(x << 1, l, mid, L, mid, v);
	}
	pushup(x);
	return res;
}

LL getAns(int x) {
	return min(w[x], w[x] - Query(1, 1, n, OP[x]));
}

void solve(int x, LL v) {
	if(v <= 0) return ;
	while(x) {
		int k = modify(1, 1, n, OP[top[x]], OP[x], v);
		if(k != 0) {
			solve(ftr[k], Query(1, 1, n, OP[k]) + v);
			return;
		} else x = ftr[top[x]];
	}
}

char opt[10];

int main() {

	read(n);
	for(int i = 1; i <= n; i++) read(w[i]);
	for(int i = 1, u, v; i < n; i++) {
		read(u), read(v); ins(u, v);
	}

	dfs1(1); dfs2(1, 1);

	build(1, 1, n);
	
	read(m);

	int x; LL v;
	
	while(m--) {
		scanf("%s", opt);
		if(opt[0] == 'Q') {
			read(x);
			printf("%lld\n", getAns(x));
		}
		if(opt[0] == 'C') {
			read(x); read(v);
			if(v == 0) continue;
			w[x] += v; modify(1, 1, n, OP[x], OP[x], -v);
			solve(ftr[x], min(w[x], w[x] - Query(1, 1, n, OP[x])) - w[x] + v);
		}
	}

	return 0;
}
