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

int pre[maxm], A[maxm], blk[maxm];
int n;

inline int add(int x, int y) {
	return x + y >= mod ? x + y - mod : x + y;
}

inline int dec(int x, int y) {
	return x - y < 0 ? x - y + mod : x - y;
}

int main() {

	read(n);
	for(int i = 1; i <= n; i++) read(A[i]);
	
	pre[1] = A[1];
	for(int i = 2; i <= n; i++) {
		pre[i] = std :: __gcd(pre[i - 1], A[i]);
	}

	for(int i = 2; i <= n; i++) {
		if(pre[i] == pre[i - 1]) blk[i] = blk[i - 1];
		else blk[i] = i - 1;
	}
	blk[0] = -1;
	
	int suf = 0, ans = 0;
	for(int i = n; i >= 2; i--) {
		suf = std :: __gcd(suf, A[i]);
		for(int j = i - 2; j >= 0; j = blk[j]) {
			ans = add(ans, 1LL * (j - blk[j]) * std :: __gcd(suf, pre[j]) % mod);
		}
		if(i == n) ans = dec(ans, suf);
	}

	for(int i = 2; i <= n - 1; i++) ans = add(ans, pre[i]);
	printf("%d\n", ans);

	return 0;
}
