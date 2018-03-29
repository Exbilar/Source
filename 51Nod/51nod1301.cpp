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
static const int maxm = 2048 + 10;
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

int f[maxm][maxm][2];
int n, m;

inline int add(const int x, const int y) {
	return x + y >= mod ? x + y - mod : x + y;
}

inline int dec(const int x, const int y) {
	return x - y < 0 ? x - y + mod : x - y;
}

int main() {
	read(n); read(m);

	int ans = 0;
	
	for(int k = 0; k <= 10; k++) {
		f[0][0][0] = 1;
		for(int i = 1; i <= max(n, m); i++) {
			for(int j = 0; j < 2048; j++) {
				for(int d = 0; d < 2; d++) {
					f[i][j][d] = f[i - 1][j][d];
					if(i <= n) f[i][j][d] = add(f[i][j][d], f[i - 1][j ^ i][d]);
					if(i <= m) f[i][j][d] = add(f[i][j][d], f[i - 1][j ^ i][d ^ (i >> k & 1)]);
				}
			}
		}
		for(int i = 1 << k; i < (1 << k + 1); i++) {
			ans = add(ans, f[max(n, m)][i][1]);
		}
	}

	printf("%d\n", ans);
	
	return 0;
}
