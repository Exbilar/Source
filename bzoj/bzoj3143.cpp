#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: swap;
using std :: vector;
using std :: make_pair;

typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 500 * 500 + 10;
static const int maxn = 500 + 10;
static const double eps = 1e-8;

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

double mtx[maxn][maxn],Ex[maxn],ddf[maxm];
pii Edge[maxm];

vector<int> G[maxn];

int n,m;

void print(int n) {
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n + 1;j++) {
			printf("%lf ",mtx[i][j]);
		}
		putchar(10);
	}
	putchar(10);
}

void gauss(int n) {
	int pos; double cur;
	for(int i = 1;i <= n;i++) {
		pos = i;
		for(int j = i + 1;j <= n;j++) {
			if(fabs(mtx[j][i]) > fabs(mtx[pos][i])) pos = j;
		}
		for(int k = 1;k <= n + 1;k++) swap(mtx[i][k],mtx[pos][k]);
		
		if(fabs(cur = mtx[i][i]) < eps) assert(0);
		
		for(int k = 1;k <= n + 1;k++) mtx[i][k] /= cur;
		for(int k = 1;k <= n;k++) {
			if(k == i) continue;
			cur = mtx[k][i];
			for(int j = 1;j <= n + 1;j++) {
				mtx[k][j] -= mtx[i][j] * cur;
			}
		}
	}
	for(int i = 1;i <= n;i++) mtx[i][n + 1] /= mtx[i][i];
}

void solve() {
	for(int i = 1;i <= n;i++) mtx[i][i] = -1.0;
	mtx[1][n + 1] = -1.0;
	for(int i = 1;i < n;i++) {
		for(int k = 0;k < (int) G[i].size();k++) {
			int v = G[i][k];
			mtx[v][i] += 1.0 / ((int) G[i].size());
		}
	}
	gauss(n);
}

int main() {

	read(n); read(m);
	int u,v;
	for(int i = 1;i <= m;i++) {
		read(u); read(v);
		if(u > v) swap(u,v);
		Edge[i] = make_pair(u,v);
		G[u].push_back(v); G[v].push_back(u);
	}

	solve();

	for(int i = 1;i <= n;i++) Ex[i] = mtx[i][n + 1];
	for(int i = 1;i <= m;i++) {
		int x = Edge[i].px,y = Edge[i].py;
		ddf[i] += Ex[x] / ((double) G[x].size());
		if(y != n) ddf[i] += Ex[y] / ((double) G[y].size());
	}

	std :: sort(ddf + 1,ddf + m + 1);

	double ans = 0.0;
	for(int i = 1;i <= m;i++) ans += ddf[i] * (m - i + 1);

	printf("%.3lf\n",ans);

	return 0;
}
