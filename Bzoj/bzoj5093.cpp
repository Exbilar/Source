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
static const int mod = 998244353;

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

LL R[maxm];
LL N, K, n, m, L;

inline LL add(const LL x, const LL y) {
	return x + y >= mod ? x + y - mod : x + y;
}

inline LL dec(const LL x, const LL y) {
	return x - y < 0 ? x - y + mod : x - y;
}

inline LL fpm(LL x, LL k) {
	LL res = 1;
	while(k) {
		if(k & 1) res = 1LL * res * x % mod;
		x = 1LL * x * x % mod;
		k >>= 1;
	}
	return res;
}

inline LL mul(LL x, LL y) {
	return (x * y + mod) % mod;
}

inline LL getInv(const LL x) {
	return fpm(x, mod - 2);
}

void NTT(LL *A, LL n, LL f) {
	for(LL i = 0; i < n; i++) {
		if(i < R[i]) std :: swap(A[i], A[R[i]]);
	}
	
	for(LL i = 1; i < n; i <<= 1) {
		LL gn = fpm(3, (mod - 1) / (i << 1));
		if(f == -1) gn = getInv(gn);
		for(LL j = 0; j < n; j += i << 1) {
			LL g = 1;
			for(LL k = 0; k < i; k++, g = 1LL * g * gn % mod) {
				LL x = A[j + k], y = mul(A[i + j + k], g);
				A[j + k] = add(x, y);
				A[i + j + k] = dec(x, y);
			}
		}
	}
	
	if(f == -1) {
		LL inv = getInv(n);
		for(LL i = 0; i < n; i++) A[i] = mul(A[i], inv);
	}
}

LL f[maxm], g[maxm], facInv[maxm];

int main() {

#ifndef ONLINE_JUDGE
	freopen("bzoj5093.in", "r", stdin);
#endif
	
	read(N); read(K);

	for(n = 1; n <= K + K; n <<= 1) L++;
	for(LL i = 0; i < n; i++) {
		R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	}

	facInv[0] = 1;
	for(LL i = 1; i <= K; i++) {
		facInv[i] = mul(facInv[i - 1], i);
	}

	for(LL i = 0; i <= K; i++) {
		facInv[i] = getInv(facInv[i]);
	}

	for(LL i = 0; i <= K; i++) {
		f[i] = ((i & 1) ? mod - 1 : 1);
		f[i] = mul(f[i], facInv[i]);
	}

	for(LL i = 0; i <= K; i++) {
		g[i] = fpm(i, K);
		g[i] = mul(g[i], facInv[i]);
	}

	NTT(f, n, 1); NTT(g, n, 1);
	for(LL i = 0; i < n; i++) f[i] = mul(f[i], g[i]);
	NTT(f, n, -1);

	LL ans = 0, fac = 1;
	
	for(LL i = 0, Comb = 1; i <= min(N - 1, K); i++) {
		if(i != 0) Comb = mul(mul(Comb, N - i), getInv(i)), fac = mul(fac, i);
		ans = add(ans, mul(mul(f[i], fac), mul(Comb, fpm(2, N - 1 - i))));
	}

	printf("%lld\n", mul(mul(ans, N), fpm(2, 1LL * (N - 1) * (N - 2) / 2LL % mod)));

	return 0;
}
