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
static const int maxm = 2e5 + 10;
static const int mod = 1e9 + 7;

template <class T> inline bool chkmax(T &x, T y) {
    return x < y ? x = y, true : false;
}

template <class T> inline bool chkmin(T &x, T y) {
    return x > y ? x = y, true : false;
}

template <class T> inline void read(T &in) {
    in = 0; char ch = getchar(); T f = 1;
    for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

template <class T> inline void write(T out) {
    if(out >= 10) write(out / 10);
    putchar(out % 10 + '0');
}

string procStatus(){
    std :: ifstream t("/proc/self/status");
    return string(std :: istreambuf_iterator<char> (t),
                  std :: istreambuf_iterator<char> ());
}

int fst[maxm], nxt[maxm << 1], to[maxm << 1];
char str[maxm];
int n, cnt;

void ins(int f, int t) {
	nxt[++cnt] = fst[f], to[cnt] = t, fst[f] = cnt;
	nxt[++cnt] = fst[t], to[cnt] = f, fst[t] = cnt;
}

struct SAM {
	int len[maxm], fail[maxm], ch[maxm][26];
	int sz, rt, lst;

	SAM() {
		sz = 0; rt = lst = ++sz;
		len[rt] = fail[rt] = 0;
	}

	void insert(int v) {
		int x = ++sz, cur = lst;
		len[x] = len[lst] + 1;
		lst = x;
		
		while(cur && !ch[cur][v]) ch[cur][v] = x, cur = fail[cur];
		if(!cur) return fail[x] = rt, void();

		int pos = ch[cur][v];
		if(len[pos] == len[cur] + 1) return fail[x] = pos, void();

		int clone = ++sz;
		fail[clone] = fail[pos];
		len[clone] = len[cur] + 1;
		memcpy(ch[clone], ch[pos], sizeof ch[pos]);
		
		fail[x] = fail[pos] = clone;
		while(cur && ch[cur][v] == pos) {
			ch[cur][v] = clone, cur = fail[cur];
		}
	}

	void init() {
		for(int i = 1; i <= sz; i++) {
			if(fail[i]) ins(i, fail[i]);
		}
	}
	
}SAM;

int ftr[maxm], son[maxm], size[maxm];
int dpt[maxm], top[maxm], pos[maxm], ddf[maxm];
int sz, tot;

void dfs1(int x) {
	size[x] = 1;
	for(int u = fst[x]; u; u = nxt[u]) {
		int v = to[u];
		if(v == ftr[x]) continue;
		ftr[v] = x; dpt[v] = dpt[x] + 1;
		dfs1(v);
		size[x] += size[v];
		if(size[son[x]] < size[v]) son[x] = v;
	}
}

void dfs2(int x, int chain) {
	pos[x] = ++sz; ddf[sz] = x; top[x] = chain;
	if(son[x]) dfs2(son[x], chain);
	for(int u = fst[x]; u; u = nxt[u]) {
		if(to[u] != ftr[x] && to[u] != son[x]) dfs2(to[u], to[u]);
	}
}

int sum[maxm << 2], add[maxm << 2], xi[maxm << 2];

void pushup(int x) {
	xi[x] = (xi[x << 1] + xi[x << 1 | 1]) % mod;
	sum[x] = (sum[x << 1] + sum[x << 1 | 1]) % mod;
}

void pushadd(int x, int v) {
	add[x] = (add[x] + v) % mod;
	sum[x] = (sum[x] + 1LL * v * xi[x] % mod) % mod;
}

void pushdown(int x) {
	if(add[x]) {
		pushadd(x << 1, add[x]);
		pushadd(x << 1 | 1, add[x]);
		add[x] = 0;
	}
}

void build(int x, int l, int r) {
	if(l == r) {
		int p = ddf[l];
		xi[x] = SAM.len[p] - SAM.len[SAM.fail[p]];
		return ;
	}
	int mid = (l + r) >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
	pushup(x);
}

void modify(int x, int l, int r, int L, int R, int v) {
	if(l >= L && r <= R) return pushadd(x, v), void();
	pushdown(x);
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1, l, mid, L, R, v);
	if(R > mid)  modify(x << 1 | 1, mid + 1, r, L, R ,v);
	pushup(x);
}

int Query(int x, int l, int r, int L, int R) {
	if(l >= L && r <= R) return sum[x];
	pushdown(x);
	int mid = (l + r) >> 1, res = 0;
	if(L <= mid) res = (res + Query(x << 1, l, mid, L, R)) % mod;
	if(R > mid)  res = (res + Query(x << 1 | 1, mid + 1, r, L, R)) % mod;
	return res;
}

void solve() {
	int ans = 0, cur = SAM.rt, sum = 0;
	for(int i = 1; i <= n; i++) {
		cur = SAM.ch[cur][str[i] - 'a'];
		for(int p = cur; p; p = ftr[top[p]]) {
			sum = (sum + Query(1, 1, tot, pos[top[p]], pos[p])) % mod;
		}
		ans = (ans + sum) % mod;
		printf("%d\n", ans);
		for(int p = cur; p; p = ftr[top[p]]) {
			modify(1, 1, tot, pos[top[p]], pos[p], 1);
		}
	}
}

int main() {

	read(n); scanf("%s", str + 1);
	for(int i = 1; i <= n; i++) SAM.insert(str[i] - 'a');
	SAM.init(); tot = SAM.sz;

	dfs1(1); dfs2(1, 1);
	build(1, 1, tot);

	solve();

	return 0;
}
