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
static const int maxm = 1e5 + 10;

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

LL suf[maxm], pre[maxm], prm[maxm];
LL n, M, sz, ans;

inline void init(LL n) {
	sz = 0;
	M = sqrt(n);
}

LL dfs(const LL rem, const int lst, const LL mul, const LL n) {
	LL res = 0;
	if(rem != n) {
		LL tmp = (rem > M ? suf[n / rem] : pre[rem]) - pre[prm[lst] - 1];
		res += tmp * mul;
	}
	for(RG int i = lst; i <= sz; i++) {
		RG const LL p = prm[i];
		if(p * p > rem) break;
		LL nmul = mul, nrem = rem;
		if(rem == n) {
			for(LL q = p; q * p <= rem; q *= p) {
				res += dfs(nrem /= p, i + 1, nmul, n);
				nmul = nmul * p; res += nmul;
			}
		} else {
			for(LL q = p; q * p <= rem; q *= p) {
				nmul = nmul * p;
				res += dfs(nrem /= p, i + 1, nmul, n);
				res += nmul * p;
			}
		}
	}
	return res;
}

inline LL solve(LL n) {
	if(!n) return 0;
	
	init(n);
	
	for(RG uint i = 1; i <= M; i++) {
		pre[i] = 1LL * i * (i + 1) / 2 - 1;
		LL pos = n / i;
		suf[i] = 1LL * pos * (pos + 1) / 2 - 1;
	}
	
	for(RG uint p = 2; p <= M; p++) {
		if(pre[p] == pre[p - 1]) continue;
		prm[++sz] = p;
		const LL q = 1LL * p * p, end = min(M, n / q), m = n / p;
		const LL presum = pre[p - 1];
		for(RG uint i = 1, w = M / p; i <= w; i++) {
			suf[i] = suf[i] - 1LL * (suf[i * p] - presum) * p;
		}
		for(RG uint i = M / p + 1; i <= end; i++) {
			suf[i] = suf[i] - 1LL * (pre[m / i] - presum) * p;
		}
		for(RG uint i = M; i >= q; i--) {
			pre[i] = pre[i] - 1LL * (pre[i / p] - presum) * p;
		}
	}
	
	prm[++sz] = M + 1;
	
	return n > 1 ? dfs(n, 1, 1, n) : 0;
}

int main() {

	read(n);
	LL ansl = solve(n - 1);
	read(n);
	LL ansr = solve(n);

	printf("%lld\n", ansr - ansl);

	return 0;
}
