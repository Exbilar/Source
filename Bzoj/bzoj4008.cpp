#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: string;
using std :: make_pair;

typedef long long LL;
typedef pair<LL, LL> pll;
typedef pair<int, int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 300 + 10;

template <class T> inline bool chkmax(T &x, T y) {
    return x < y ? x = y, true : false;
}

template <class T> inline bool chkmin(T &x, T y) {
    return x > y ? x = y, true : false;
}

template <class T> inline void read(T &in) {
    in = 0; char ch = getchar(); T f = 1;
    for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

template <class T> inline void write(T out) {
	if(out >= 10) write(out / 10);
	putchar(out % 10 + '0');
}

string procStatus() {
	std :: ifstream t("/proc/self/status");
	return string(std :: istreambuf_iterator<char> (t),
				  std :: istreambuf_iterator<char> ());
}

double f[maxm][maxm], g[maxm], pi[maxm], pwr[maxm][maxm];

int di[maxm];

int n, cas, r;

double ans;

void init() {
	ans = 0.0;
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
}

void solve() {
	read(n); read(r);
	for(int i = 1; i <= n; i++) {
		scanf("%lf%d", &pi[i], &di[i]);
		pwr[i][0] = 1.0;
	}

	if(!r) return printf("%.10lf\n", 0.0), void();
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= r; j++) {
			pwr[i][j] = pwr[i][j - 1] * (1.0 - pi[i]);
		}
	}

	f[1][0] = pwr[1][r]; f[1][1] = 1.0 - pwr[1][r];

	for(int i = 2; i <= n; i++) {
		for(int j = 0; j <= i && j <= r; j++) {
			if(j != 0) f[i][j] += f[i - 1][j - 1] * (1.0 - pwr[i][r - j + 1]);
			if(i != j) f[i][j] += f[i - 1][j] * pwr[i][r - j];
		}
	}

	g[1] = f[1][1];
	for(int i = 2; i <= n; i++) {
		for(int j = 0; j <= i - 1 && j <= r; j++) {
			g[i] += f[i - 1][j] * (1.0 - pwr[i][r - j]);
		}
	}

	for(int i = 1; i <= n; i++) {
		ans += g[i] * di[i];
	}

	printf("%.10lf\n", ans);
	
}

int main() {

	read(cas);
	while(cas--) {
		init(), solve();
	}

	return 0;
}
