#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: make_pair;

typedef long long LL;
typedef pair<LL, LL> pll;
typedef pair<int, int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 2e5 + 10;

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

int fst[maxm], nxt[maxm], to[maxm], size[maxm], col[maxm];
int son[maxm];
int cnt, n;

void ins(int f, int t) {
	nxt[++cnt] = fst[f], to[cnt] = t, fst[f] = cnt;
	nxt[++cnt] = fst[t], to[cnt] = f, fst[t] = cnt;
}

void dfs(int x, int fa) {
	size[x] = 1;
	for(int u = fst[x]; u; u = nxt[u]) {
		int v = to[u];
		if(v == fa) continue;
		dfs(v, x);
		size[x] += size[v];
		if(size[son[x]] < size[v]) son[x] = v;
	}
}

LL num[maxm], ans[maxm];
LL smax, sum, SON;

void calc(int x, int fa, int val) {
	num[col[x]] += val;
	if(num[col[x]] > smax) sum = col[x], smax = num[col[x]];
	else if(num[col[x]] == smax) sum += col[x];
	for(LL u = fst[x]; u; u = nxt[u])
		if(to[u] != fa && to[u] != SON) calc(to[u], x, val);
}

void dfs2(int x, int fa, int chain) {
	for(int u = fst[x]; u; u = nxt[u])
		if(to[u] != fa && to[u] != son[x]) dfs2(to[u], x, 0);
	if(son[x]) dfs2(son[x], x, 1), SON = son[x];
	calc(x, fa, 1); SON = 0;
	ans[x] = sum;
	if(chain != 1) calc(x, fa, -1), smax = sum = 0;
}

int main() {

	read(n);
	for(int i = 1; i <= n; i++) read(col[i]);

	int u, v;
	for(int i = 1; i < n; i++) {
		read(u); read(v); ins(u, v);
	}

	dfs(1, 0);
	dfs2(1, 0, 0);

	for(int i = 1; i <= n; i++) {
		printf("%I64d ", ans[i]);
	}

	putchar(10);

	return 0;
}
