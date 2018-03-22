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
static const int maxm = 3e6 + 10;

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

string procStatus(){
    std :: ifstream t("/proc/self/status");
    return string(std :: istreambuf_iterator<char> (t),
				  std :: istreambuf_iterator<char> ());
}

LL wi[maxm], A[maxm], B[maxm];
LL n, m, cntA, cntB;

void dfs(int x, int n, LL cur, LL *get, LL &cnt) {
	if(cur > m) return ;
	if(x > n) return get[++cnt] = cur, void();
	dfs(x + 1, n, cur, get, cnt);
	dfs(x + 1, n, cur + wi[x], get, cnt);
}

int main() {
	read(n); read(m);
	for(int i = 1; i <= n; i++) read(wi[i]);

	dfs(1, n >> 1, 0, A, cntA);
	dfs((n >> 1) + 1, n, 0, B, cntB);

	A[++cntA] = oo;
	std :: sort(A + 1, A + cntA + 1);

	LL ans = 0;
	
	for(int i = 1; i <= cntB; i++) {
		ans += std :: upper_bound(A + 1, A + cntA + 1, m - B[i]) - A - 1;
	}

	printf("%lld\n", ans);

	return 0;
}
