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

int fst[maxm], nxt[maxm], to[maxm], ind[maxm];
LL f[maxm], size[maxm];

int cnt, n, m, cas, rt;

void ins(int f, int t) {
	nxt[++cnt] = fst[f], to[cnt] = t, fst[f] = cnt;
	nxt[++cnt] = fst[t], to[cnt] = f, fst[t] = cnt;
}

void init() {
	memset(fst, 0, sizeof fst);
	memset(ind, 0, sizeof ind);
	memset(f, 0, sizeof f);
	cnt = 0;
}

LL find(int x, int fa, int P) {
	LL res = x > P;
	for(int u = fst[x]; u; u = nxt[u]) {
		int v = to[u];
		if(v == fa) continue;
		res += find(v, x, P);
	}
	return res;
}

void dfs(int x, int fa) {
	size[x] = 1; f[x] = 1;
	for(int u = fst[x]; u; u = nxt[u]) {
		int v = to[u];
		if(v == fa) continue;
		dfs(v, x);
		size[x] += size[v];
	}
	
	int half = size[x] & 1 ? 0 : size[x] >> 1;
	for(int u = fst[x]; u; u = nxt[u]) {
		int v = to[u];
		if(v == fa) continue;
		if(size[v] == half) f[x] = f[x] * f[v] % mod * find(v, x, x) % mod;
		else f[x] = f[x] * f[v] % mod * size[v] % mod;
	}
}

int main() {

	freopen("bzoj4835.in", "r", stdin);
	
	read(cas);
	while(cas--) {
		read(n); read(m); init();
		for(int i = 1, u, v; i <= m; i++) {
			read(u), read(v), ins(u, v), ind[v]++;
		}
		for(int i = 1; i <= n; i++) {
			if(ind[i] == 0) {
				dfs(i, 0);
				printf("%lld\n", f[i]);
				break;
			}
		}
	}

	return 0;
}
