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
static const int maxm = 5000 + 10;
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

int S[maxm][maxm], fac[maxm];
int n, k;

inline int add(const int x, const int y) {
	return x + y >= mod ? x + y - mod : x + y;
}

inline int dec(const int x, const int y) {
	return x - y < 0 ? x - y + mod : x - y;
}

inline int fpm(int x, int k) {
	int res = 1;
	while(k) {
		if(k & 1) res = 1LL * res * x % mod;
		x = 1LL * x * x % mod;
		k >>= 1;
	}
	return res;
}

void init() {
	for(int i = 1; i <= k; i++) S[i][0] = 0, S[i][i] = 1;
	for(int i = 1; i <= k; i++) {
		for(int j = 1; j < i; j++) {
			S[i][j] = add(S[i - 1][j - 1], 1LL * S[i - 1][j] * j % mod);
		}
	}
	
	fac[0] = 1;
	for(int i = 1; i <= k; i++) fac[i] = 1LL * fac[i - 1] * i % mod;
}

int inv(int x) {
	return fpm(x, mod - 2);
}

int main() {

	read(n); read(k); init();

	int ans = 0;

	int C = 1;
	for(int i = 1; i <= min(n, k); i++) {
		C = 1LL * C * (n - i + 1) % mod * inv(i) % mod;
		ans = add(ans, 1LL * S[k][i] * fac[i] % mod * C % mod * fpm(2, n - i) % mod);
	}

	printf("%d\n", ans);

	return 0;
}
