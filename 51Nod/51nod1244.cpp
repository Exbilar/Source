#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

using std :: max;
using std :: min;
using std :: vector;

typedef long long LL;

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

LL l,r;
int M;

vector<LL> pre,suf;
vector<int> prm;

LL dfs(LL rem,int lst,LL mul,LL n) {
	LL tmp = (rem > M ? suf[n / rem] : pre[rem]) - pre[prm[lst] - 1];
	LL res = -tmp * mul;
	for(int i = lst;i < (int) prm.size();i++) {
		int p = prm[i];
		if(1LL * p * p > rem) break;
		res += dfs(rem / p,i + 1,-mul,n);
	}
	return res;
}

LL solve(LL n){
	pre.clear(),suf.clear(),prm.clear();
	
	M = sqrt(n);
	pre.resize(M + 1),suf.resize(M + 1);

	for(int i = 1;i <= M;i++) {
		pre[i] = i - 1;
		suf[i] = n / i - 1;
	}
	
	for(int p = 2;p <= M;p++) {
		if(pre[p] == pre[p - 1]) continue;
		prm.push_back(p);
		LL pcnt = pre[p - 1],q = 1LL * p * p,m = n / p;
		LL end = min((LL) M,n / q);
		for(int i = 1,w = M / p;i <= w;i++) suf[i] -= suf[i * p] - pcnt;
		for(int i = M / p + 1;i <= end;i++) suf[i] -= pre[m / i] - pcnt;
		for(int i = M;i >= q;i--) pre[i] -= pre[i / p] - pcnt;
	}
	prm.push_back(M + 1);
	return n > 1 ? 1 + dfs(n,0,1,n) : 1;
}

int main() {
	read(l),read(r);

	printf("%lld\n",solve(r) - solve(l - 1));
	
	return 0;
}
