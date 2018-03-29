#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: map;
using std :: pair;
using std :: string;
using std :: make_pair;

typedef long long LL;
typedef pair<LL, LL> pll;
typedef pair<int, int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 1010101;
static const int mod = 1e9 + 7;

template <class T> inline bool chkmax(T &x, T y) {
    return x < y ? x = y, true : false;
}

template <class T> inline bool chkmin(T &x, T y) {
    return x > y ? x = y, true : false;
}

inline char get(void) {
    static char buf[100000], *S = buf, *T = buf;
    if (S == T) {
        T = (S = buf) + fread(buf, 1, 100000, stdin);
        if (S == T) return EOF;
    }
    return *S++;
}

template <typename T> inline int read(T &x) {
    static char c; x = 0; int sgn = 0;
    for (c = get(); c < '0' || c > '9'; c = get()) {
        if (c == '-') sgn = 1;
        if (c == EOF) return 0;
    }
    for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
    if (sgn) x = -x; return 1;
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

map<int, int> mmp[maxm];

int li[maxm], ri[maxm], fac[maxm], facInv[maxm];

int n, cas;

int fpm(int x, int k) {
	int res = 1;
	while(k) {
		if(k & 1) res = 1LL * res * x % mod;
		x = 1LL * x * x % mod;
		k >>= 1;
	}
	return res;
}

void init(int n) {
	facInv[1] = 1;
	for(int i = 2; i <= n; i++) facInv[i] = 1LL * (mod - mod / i) * facInv[mod % i] % mod;
	fac[0] = 1, facInv[0] = 1;
	for(int i = 1; i <= n; i++) {
		fac[i] = 1LL * fac[i - 1] * i % mod;
		facInv[i] = 1LL * facInv[i - 1] * facInv[i] % mod;
	}
}

int C(int n ,int m) {
	return 1LL * fac[n] * facInv[m] % mod * facInv[n - m] % mod;
}

int solve(int L, int R) {
	if(L > R) return 1;
	int pos = mmp[L][R];
	if(L == R && pos == L) return 1;
	if(pos < L || pos > R) return 0;
	return 1LL * C(R - L, pos - L) * solve(L, pos - 1) % mod * solve(pos + 1, R) % mod;
}

int main() {

	init(1000000);

	while(read(n)) {
		for(int i = 1; i <= n; i++) mmp[i].clear();
		for(int i = 1; i <= n; i++) read(li[i]);
		for(int i = 1; i <= n; i++) read(ri[i]);
		int check = 1;
		for(int i = 1; i <= n; i++) {
			if(mmp[li[i]].count(ri[i])) check = 0;
			else mmp[li[i]][ri[i]] = i;
		}
		if(check) printf("Case #%d: %d\n", ++cas, solve(1, n));
		else printf("Case #%d: %d\n", ++cas, 0);
	}

	return 0;
}
