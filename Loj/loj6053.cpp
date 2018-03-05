#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

using std :: max;
using std :: min;
using std :: vector;

typedef long long LL;
typedef unsigned long long ull;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const ull mod = 1000000007;

template <class T> inline bool chkmax (T &x, T y) {
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin (T &x, T y) {
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in) {
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if (ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

vector<int> prm;
vector<ull> pre[2],suf[2];

ull n,M;

inline LL add(LL x,LL y) {
	return x + y >= mod ? x + y - mod : x + y;
}

inline LL minus(LL x,LL y) {
	return x - y < 0 ? x - y + mod : x - y;
}

ull dfs(ull rem,int lst,ull mul,ull n) {
	ull tmp = minus((rem > M ? suf[1][n / rem] : pre[1][rem]),pre[1][prm[lst] - 1]);
	ull res = 1ull * mul * tmp % mod;
	for(int i = lst;i < (int) prm.size();i++) {
		int p = prm[i];
		if(1ull * p * p > rem) break;
		ull nrem = rem,nmul = 0;
		for(ull q = p,e = 1;q * p <= rem;q *= p) {
			nmul = 1ull * mul * (p ^ e) % mod;
			res = add(res,dfs(nrem /= p,i + 1,nmul,n));
			res = add(res,1ull * mul * (p ^ (++e)) % mod);
		}
	}
	return res;
}

inline void init(ull n) {
	M = sqrt(n);
	prm.reserve(M + 1);
	pre[0].resize(M + 1);
	pre[1].resize(M + 1);
	suf[0].resize(M + 1);
	suf[1].resize(M + 1);
}

ull solve(ull n) {
	init(n);
	for(RG ull i = 1;i <= M;i++) {
		pre[0][i] = i - 1;
		pre[1][i] = (1ull * i * (i + 1ull) / 2 - 1) % mod;
		const ull pos = (n / i) % mod;
		suf[0][i] = (pos - 1 + mod) % mod;
		suf[1][i] = (1ull * pos * (pos + 1ull) / 2 - 1) % mod;
	}

	for(RG ull p = 2;p <= M;p++) {
		if(pre[0][p] == pre[0][p - 1]) continue;
		prm.push_back(p);
		
		const ull q = 1ull * p * p,m = n / p;
		const ull pcnt0 = pre[0][p - 1],pcnt1 = pre[1][p - 1];
		ull end = min(1ull * M,n / q);
		
		for(RG ull i = 1,w = M / p;i <= w;i++) {
			suf[0][i] = minus(suf[0][i],minus(suf[0][i * p],pcnt0));
			suf[1][i] = minus(suf[1][i],minus(suf[1][i * p],pcnt1) * p % mod);
		}
		for(RG ull i = M / p + 1;i <= end;i++) {
			suf[0][i] = minus(suf[0][i],minus(pre[0][m / i],pcnt0));
			suf[1][i] = minus(suf[1][i],minus(pre[1][m / i],pcnt1) * p % mod);
		}
		for(RG ull i = M;i >= q;i--) {
			pre[0][i] = minus(pre[0][i],minus(pre[0][i / p],pcnt0));
			pre[1][i] = minus(pre[1][i],minus(pre[1][i / p],pcnt1) * p % mod);
		}
	}
	
	prm.push_back(M + 1);
	
	for(ull i = 1;i <= M;i++) {
		pre[1][i] = minus(pre[1][i],pre[0][i]);
		suf[1][i] = minus(suf[1][i],suf[0][i]);
		if(i >= 2) pre[1][i] = add(2,pre[1][i]);
		if(n >= i * 2) suf[1][i] = add(2,suf[1][i]);
	}
	return n > 1 ? (1 + dfs(n,0,1,n)) % mod : 1;
}

int main() {
	read(n);

	printf("%llu\n",solve(n));

	return 0;
}
