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
static const int maxm = 1e3 + 10;
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

int A[maxm],f[maxm][maxm];
int n,m;

int main() {
	read(n); read(m);
	for(int i = 1;i <= n;i++) read(A[i]);

	f[0][0] = 1;
	for(int i = 1;i <= n;i++) {
		int l = i,r = i;
		while(A[l - 1] < A[i] && l > 1) l--;
		while(A[r + 1] < A[i] && r < n) r++;
		f[i][m] = (f[i][m] + f[i - 1][m]) % mod;
		for(int j = m;j >= 1;j--) {
			int sum = f[l - 1][j - 1];
			for(int k = l;k <= r;k++) {
				f[k][j] = (f[k][j] + sum) % mod;
				sum = (sum + f[k][j - 1]) % mod;
			}
			f[i][j - 1] = (f[i][j - 1] + f[i - 1][j - 1]) % mod;
			f[i][j] = (f[i][j] - f[i - 1][j - 1] + mod) % mod;
		}
	}

	int ans = 0;
	for(int i = 0;i <= m;i++) {
		ans = (ans + f[n][i]) % mod;
	}
	
	printf("%d\n",ans);

	return 0;
}
