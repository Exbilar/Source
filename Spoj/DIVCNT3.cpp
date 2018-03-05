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
vector<ull> pre,suf;

int M,cas;

ull n,k;

ull dfs(ull rem,int lst,ull mul,ull n) {
	ull tmp = (rem > M ? suf[n / rem] : pre[rem]) - pre[prm[lst] - 1];
	ull res = (k + 1) * tmp * mul;
	for(RG int i = lst;i < (int) prm.size();i++) {
		int p = prm[i];
		if(1ull * p * p > rem) break;
		ull nrem = rem,nmul = mul * (k + 1);
		for(RG ull q = p;q * p <= rem;q *= p) {
			res += dfs(nrem /= p,i + 1,nmul,n);
			nmul += mul * k;
			res += nmul;
		}
	}
	return res;
}

inline ull solve(ull n) {
	M = sqrt(n);
	pre.clear(),suf.clear(),prm.clear();
	pre.resize(M + 1),suf.resize(M + 1);

	for(RG int i = 1;i <= M;i++) {
		pre[i] = i - 1,suf[i] = n / i - 1;
	}

	for(RG int p = 2;p <= M;p++) {
		if(pre[p] == pre[p - 1]) continue;
		prm.push_back(p);
		ull pcnt = pre[p - 1],q = 1ull * p * p,m = n / p;
		ull end = min(1ull * M,n / q);
		for(RG int i = 1,w = M / p;i <= w;i++) suf[i] -= suf[i * p] - pcnt;
		for(RG int i = M / p + 1;i <= end;i++) suf[i] -= pre[m / i] - pcnt;
		for(RG int i = M;i >= q;i--) pre[i] -= pre[i / p] - pcnt;
	}
	
	prm.push_back(M + 1);
	return n > 1 ? 1 + dfs(n,0,1,n) : 1;
}

int main() {
	read(cas);
	k = 3;
	while(cas--) {
		read(n);
		printf("%llu\n",solve(n));
	}

	return 0;
}
