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

int f[maxm];
int n, x, ans;

inline int add(int x, int y) {
	return x + y >= mod ? x + y - mod : x + y;
}

int main() {
	read(n);

	for(int i = 1; i <= n; i++) {
		read(x);
		int rec = (f[x] + 1) % mod;
		for(int sub = x; sub; sub = (sub - 1) & x) {
			f[sub] = add(f[sub], rec);
		}
		ans = add(ans, rec);
	}

	printf("%d\n", ans - n);

	return 0;
}
