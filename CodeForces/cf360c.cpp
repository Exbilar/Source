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
static const int maxm = 2000 + 10;
static const int mod = 1e9 + 7;

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

int f[maxm][maxm], sum[maxm][maxm];
char str[maxm];
int n, k;

inline int add(int x, int y) {
	return x + y >= mod ? x + y - mod : x + y;
}

int main() {

	read(n); read(k);
	scanf("%s", str + 1);

	f[0][0] = 1; sum[0][0] = 1;

	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= k; j++) {
			f[i][j] = add(f[i][j], 1LL * sum[j][i - 1] * (str[i] - 'a') % mod);
			for(int pre = 0; pre + 1 <= i && (pre + 1) * (n - i + 1) <= j; pre++) {
				f[i][j] = add(f[i][j], 1LL * f[i - pre - 1][j - (pre + 1) * (n - i + 1)] * ('z' - str[i]) % mod);
			}
			sum[j][i] = add(sum[j][i - 1], f[i][j]);
		}
	}

	int ans = 0;
	for(int i = n; i >= 0; i--) {
		ans = add(ans, f[i][k]);
	}

	printf("%d\n", ans);

	return 0;
}
