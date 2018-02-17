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
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 1e6 + 10;

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

LL A[maxm],H[maxm];
LL n,S,L;

bool chk(LL x) {
	LL res = 0;
	for(int i = 1;i <= n;i++) {
		if(H[i] + A[i] * x >= L) res += H[i] + A[i] * x;
		if(res >= S) return true;
	}
	return false;
}

LL abs(LL x) {
	return x >= 0 ? x : -x;
}

int main() {

	freopen("asd.in","r",stdin);

	LL smin = oo,posmin = 0,smax = 0,posmax = 0;
	
	read(n); read(S); read(L);
	for(int i = 1;i <= n;i++) {
		read(H[i]);
		if(chkmin(smin,H[i])) posmin = i;
		if(chkmax(smax,H[i])) posmax = i;
	}
	
	for(int i = 1;i <= n;i++) read(A[i]);
	
	LL l = 0,r = 0;

	for(int i = 1;i <= n;i++) {
		if(r <= abs(L - H[i]) / A[i] + 1) r = abs(L - H[i]) / A[i] + 1;
		if(r <= abs(S - H[i]) / A[i] + 1) r = abs(S - H[i]) / A[i] + 1;
	}

	LL ans = r;
	
	while(l <= r) {
		LL mid = (l + r) >> 1;
		if(chk(mid)) ans = mid,r = mid - 1;
		else l = mid + 1;
	}

	printf("%lld\n",ans);

	return 0;
}
