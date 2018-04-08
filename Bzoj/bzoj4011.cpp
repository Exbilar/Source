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

static const LL INF = 1 << 30;
static const LL oo = 1LL << 60;
static const LL maxm = 1e6 + 10;
static const LL mod = 1e9 + 7;

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

string procStatus() {
	std :: ifstream t("/proc/self/status");
	return string(std :: istreambuf_iterator<char> (t),
				  std :: istreambuf_iterator<char> ());
}

LL fst[maxm], nxt[maxm], to[maxm], deg[maxm], ind[maxm];
LL cnt, n, m, x, y;

void ins(LL f, LL t) {
	nxt[++cnt] = fst[f], to[cnt] = t, fst[f] = cnt;
	deg[t]++; ind[t]++;
}

LL stk[maxm], f[maxm];
LL top;

LL fpm(LL x, LL k) {
	LL res = 1;
	while(k) {
		if(k & 1) res = 1LL * res * x % mod;
		x = 1LL * x * x % mod;
		k >>= 1;
	}
	return res;
}

void topsort() {
	for(LL i = 1; i <= n; i++) {
		if(!deg[i]) stk[++top] = i;
	}
	while(top) {
		LL x = stk[top--];
		f[x] = 1LL * f[x] * fpm(ind[x], mod - 2) % mod;
		for(LL u = fst[x]; u; u = nxt[u]) {
			LL v = to[u];
			if(!(--deg[v])) stk[++top] = v;
			f[v] = (f[v] + f[x]) % mod;
		}
	}
}

int main() {

	read(n); read(m); read(x); read(y); ind[y]++;

	LL u, v;
	for(LL i = 1; i <= m; i++) {
		read(u); read(v); ins(u, v);
	}

	LL ans = 1;
	for(LL i = 2; i <= n; i++)
		ans = 1LL * ans * ind[i] % mod;

	if(y == 1) return printf("%lld\n", ans), 0;

	f[y] = ans; topsort();

	printf("%lld\n", (ans - f[x] + mod) % mod);

	return 0;
}
