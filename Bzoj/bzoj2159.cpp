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
static const int maxm = 50000 + 10;
static const int maxn = 150 + 10;
static const int maxx = 200000 + 10;
static const int mod = 10007;

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

int fst[maxm], nxt[maxx], to[maxx], fac[maxn];
int f[maxm][maxn], S[maxn][maxn], g[maxn], h[maxn], ans[maxm];
int n, K, cnt;

void ins(int f, int t) {
	nxt[++cnt] = fst[f], to[cnt] = t, fst[f] = cnt;
	nxt[++cnt] = fst[t], to[cnt] = f, fst[t] = cnt;
}

int add(int x, int y) {
	return x + y >= mod ? x + y - mod : x + y;
}

int dec(int x, int y) {
	return x - y < 0 ? x - y + mod : x - y;
}

void dfs1(int x, int fa) {
	f[x][0] = 1;
	for(int u = fst[x]; u; u = nxt[u]) {
		int v = to[u];
		if(v == fa) continue;
		dfs1(v, x);
		f[x][0] = add(f[x][0], f[v][0]);
		for(int j = 1; j <= K; j++) {
			f[x][j] = add(f[x][j], add(f[v][j], f[v][j - 1]));
		}
	}
}

void dfs2(int x, int fa) {
	for(int u = fst[x]; u; u = nxt[u]) {
		int v = to[u];
		if(v == fa) continue;
		g[0] = dec(f[x][0], f[v][0]); h[0] = n % mod;
		for(int j = 1; j <= K; j++) {
			g[j] = dec(f[x][j], add(f[v][j], f[v][j - 1]));
			h[j] = add(f[v][j], add(g[j], g[j - 1]));
		}
		for(int j = 0; j <= K; j++) {
			f[v][j] = h[j];
			ans[v] = add(ans[v], 1LL * S[K][j] * fac[j] % mod * h[j] % mod);
		}
		dfs2(v, x);
	}
}

void init() {
	S[0][0] = 1;
	for(int i = 1; i <= K; i++) {
		S[i][0] = 0;
		for(int j = 1; j <= i; j++) {
			S[i][j] = add(S[i - 1][j - 1], 1LL * S[i - 1][j] * j % mod);
		}
	}

	fac[0] = 1;
	for(int i = 1; i <= K; i++) fac[i] = 1LL * fac[i - 1] * i % mod;
}

int tL, tNow, tA, tB, tC;

int main() {
	
	read(n); read(K); read(tL);
	read(tNow); read(tA); read(tB); read(tC);

	for(int i = 1; i < n; i++) {
		tNow = (tNow * tA + tB) % tC;
		int u = i - tNow % (i < tL ? i : tL), v = i + 1;
		ins(u, v);
	}

	init();

	dfs1(1, 0);

	for(int i = 0; i <= K; i++) {
		ans[1] = add(ans[1], 1LL * S[K][i] * fac[i] % mod * f[1][i] % mod);
	}

	dfs2(1, 0);

	for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);

	return 0;
}
