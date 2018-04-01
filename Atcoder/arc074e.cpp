#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: vector;
using std :: make_pair;

typedef long long LL;
typedef pair<LL, LL> pll;
typedef pair<int, int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 300 + 10;
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

int n, m;

vector<pii> G[maxm];

int f[maxm][maxm][maxm], ban[maxm][maxm][maxm];

bool check(int r, int g, int b) {
	int k = max(max(r, g), b);
	ban[r][g][b] = 0;
	for(int i = 0; i < G[k].size(); i++) {
		pii v = G[k][i];
		if((r >= v.px) + (g >= v.px) + (b >= v.px) != v.py) return true;
	}
	return false;
}

int add(int x, int y) {
	return x + y >= mod ? x + y - mod : x + y;
}

void update(int r, int g, int b, int w) {
	if(ban[r][g][b]) return ;
	f[r][g][b] = add(f[r][g][b], w);
}

int main() {

	read(n); read(m);

	int l, r, x;
	for(int i = 1; i <= m; i++) {
		read(l); read(r); read(x);
		G[r].push_back(make_pair(l, x));
	}

	for(int r = 0; r <= n; r++) {
		for(int g = 0; g <= n; g++) {
			for(int b = 0; b <= n; b++) {
				if(check(r, g, b)) ban[r][g][b] = 1;
			}
		}
	}

	f[0][0][0] = 1;

	int ans = 0;
	
	for(int r = 0; r <= n; r++) {
		for(int g = 0; g <= n; g++) {
			for(int b = 0; b <= n; b++) {
				if(int w = f[r][g][b]) {
					int k = max(max(r, g), b);
					update(k + 1, g, b, w);
					update(r, k + 1, b, w);
					update(r, g, k + 1, w);
					if(k == n) ans = add(ans, w);
				}
			}
		}
	}

	printf("%d\n", ans);

	return 0;
}
