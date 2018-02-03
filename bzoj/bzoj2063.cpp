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
typedef pair<LL,LL> pll;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;

template <class T> inline bool chkmax(T &x, T y) {
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x, T y) {
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in) {
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if (ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

LL L,R,K,len;

pll f[20][200][1000 + 10];

int dl[20],dr[20];

pll operator + (const pll &lhs, const pll &rhs) {
	return make_pair(lhs.px + rhs.px,rhs.py);
}

pll dfs (int dpt, LL sum, LL rmn, bool dn, bool up) {
	if (!dpt) {
		if(sum + rmn >= K) return make_pair(1LL,0LL);
		else return make_pair(0LL,sum + rmn);
	}
	
	if (!up && !dn && f[dpt][sum][rmn].px) {
		return f[dpt][sum][rmn];
	}
	
	pll res = make_pair(0, rmn);

	for (int i = (dn ? dl[dpt] : 0); i <= (up ? dr[dpt] : 9); i++) {
		res = res + dfs(dpt - 1, sum + i, res.py, dn && i == dl[dpt], up && i == dr[dpt]);
	}
	
	if (!up && !dn) f[dpt][sum][rmn] = res;
	
	return res;
}

int main() {

	read(L),read(R),read(K);

	len = 0; while(L) dl[++len] = L % 10,L /= 10;
	len = 0; while(R) dr[++len] = R % 10,R /= 10;

	printf("%lld\n",dfs(len,0,0,1,1).px);

	return 0;
}
