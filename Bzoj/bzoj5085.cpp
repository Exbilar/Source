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
static const int maxm = 2000 + 10;

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

int ai[maxm][maxm], asd[maxm][maxm];
int n, m;

bool check(int v) {
	static int ddf[maxm]; ddf[0] = 0;
	
	for(int i = 1; i <= m; i++) {
		for(int j = i + 1; j <= m; j++) asd[i][j] = 0;
	}
	
	for(int i = 1; i <= n; i++, ddf[0] = 0) {
		for(int j = 1; j <= m; j++)
			if(ai[i][j] >= v) ddf[++ddf[0]] = j;

		for(int j = 1; j <= ddf[0]; j++) {
			for(int k = j + 1; k <= ddf[0]; k++) {
				if(asd[ddf[j]][ddf[k]]) return true;
				asd[ddf[j]][ddf[k]] = 1;
			}
		}
	}
	
	return false;
}

int main() {
	read(n); read(m);
	
	int l = INF, r = -INF, ans = 0;
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			read(ai[i][j]);
			chkmin(l, ai[i][j]);
			chkmax(r, ai[i][j]);
		}
	}

	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}

	printf("%d\n", ans);
	
	return 0;
}
