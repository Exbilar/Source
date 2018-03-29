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
static const int MOD = 1e9;
static const int MOD2 = 512;
static const int MOD5 = 1953125;
static const int phi2 = 256;
static const int phi5 = 1562500;
static const int maxm = 2e6 + 10;

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

template <class T> inline void write(T out) {
	if(out >= 10) write(out / 10);
	putchar(out % 10 + '0');
}

string procStatus(){
    std :: ifstream t("/proc/self/status");
    return string(std :: istreambuf_iterator<char> (t),
				  std :: istreambuf_iterator<char> ());
}

LL fac2[maxm], fac5[maxm], pwr2[maxm], pwr5[maxm];
LL N, M, K;

inline LL add(const LL x, const LL y, const LL mod) {
	return x + y >= mod ? x + y - mod : x + y;
}

inline LL dec(const LL x, const LL y, const LL mod) {
	return x - y < 0 ? x - y + mod : x - y;
}

inline LL fpm(LL x, LL k, const LL mod) {
	LL res = 1;
	while(k) {
		if(k & 1) res = res * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return res;
}

void exgcd(LL a, LL b, LL &x, LL &y) {
	if(!b) return x = 1, y = 0, void();
	exgcd(b, a % b, y, x); y -= a / b * x;
}

inline LL getInv(LL a, LL P) {
	LL x, y;
	exgcd(a, P, x, y);
	return (x + P) % P == 0 ? P : (x + P) % P;
}

LL getFac(LL n, LL P, LL Pk) {
	if(!n) return 1;
	LL res = 1;
	if(P == 2) {
		if(n / Pk) res = pwr2[n / Pk % phi2];
		res = res * fac2[n % Pk] % Pk;
	} else if(P == 5) {
		if(n / Pk) res = pwr5[n / Pk % phi5];
		res = res * fac5[n % Pk] % Pk;
	}
	return res * getFac(n / P, P, Pk) % Pk;
}

inline LL Comb(LL n, LL m, LL P, LL Pk, int k) {
	if(n < m) return 0;
	LL x = getFac(n, P, Pk), y = getFac(m, P, Pk), z = getFac(n - m, P, Pk);
	
	int e = 0;
	for(RG LL i = n; i; i /= P) e += i / P;
	for(RG LL i = m; i; i /= P) e -= i / P;
	for(RG LL i = n - m; i; i /= P) e -= i / P;

	if(P == 2 && k) e -= 1;
	
	LL res = x * getInv(y, Pk) % Pk * getInv(z, Pk) % Pk;
	res = res * fpm(P, e, Pk) % Pk;

	if(P == 5 && k) res = res * getInv(2, Pk) % Pk;
	
	return res * (MOD / Pk) % MOD * getInv(MOD / Pk, Pk) % MOD;
}

inline LL solve(const LL n, const LL m, const LL k) {
	return add(Comb(n, m, 2, MOD2, k), Comb(n, m, 5, MOD5, k), MOD);
}

inline void init() {
	fac2[0] = 1, fac5[0] = 1;
	for(RG LL i = 1; i <= 512; i++) {
		if(i % 2) fac2[i] = fac2[i - 1] * i % MOD2;
		else fac2[i] = fac2[i - 1];
	}
	for(RG LL i = 1; i <= 1953125; i++) {
		if(i % 5) fac5[i] = fac5[i - 1] * i % MOD5;
		else fac5[i] = fac5[i - 1];
	}
	
	pwr2[0] = 1, pwr5[0] = 1;
	for(RG LL i = 1; i <= phi2; i++) pwr2[i] = pwr2[i - 1] * fac2[512] % MOD2;
	for(RG LL i = 1; i <= phi5; i++) pwr5[i] = pwr5[i - 1] * fac5[1953125] % MOD5;
}

void output(LL x, int len) {
	if(len == 1) return putchar(x % 10 + '0'), void();
	output(x / 10, len - 1);
	putchar(x % 10 + '0');
}

int main() {

	init();
	
	while(scanf("%lld%lld%lld", &N, &M, &K) != EOF) {
		if(N == M) {
			output(dec(fpm(2, N + M - 1, MOD), solve(N + M, N, 1), MOD), K);
			putchar(10);
		} else {
			LL res = fpm(2, N + M - 1, MOD);
			if((N + M) % 2 == 0) {
				res = add(res, solve(N + M, (N + M) >> 1, 1), MOD);
				for(RG LL i = M + 1, w = (N + M) / 2; i < w; i++) {
					res = add(res, solve(N + M, i, 0), MOD);
				}
			} else {
				for(RG LL i = M + 1, w = (N + M) / 2; i <= w; i++) {
					res = add(res, solve(N + M, i, 0), MOD);
				}
			}
			output(res, K);
			putchar(10);
		}
	}

	return 0;
}
