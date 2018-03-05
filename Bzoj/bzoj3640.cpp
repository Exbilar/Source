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
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 150 + 10;
static const int maxn = 5000 + 10;
static const int maxhp = 10000 + 10;
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

int n,m,hp;

vector<int> G[maxm];

int A[maxm];
double mtx[maxm][maxm],val[maxm][maxm],f[maxm][maxhp];
double cons[maxm];

void gauss() {
	double cur;
	for(int i = 1;i <= n;i++) {
		int pos = i;
		for(int j = i + 1;j <= n;j++) {
			if(fabs(mtx[j][i]) > fabs(mtx[pos][i])) pos = i;
		}
		
		for(int j = 1;j <= n;j++) std :: swap(mtx[i][j],mtx[pos][j]);
		for(int j = 1;j <= n;j++) std :: swap(val[i][j],val[pos][j]);
		
		if(fabs(cur = mtx[i][i]) < eps) assert(0);

		for(int j = 1;j <= n;j++) mtx[i][j] /= cur;
		for(int j = 1;j <= n;j++) val[i][j] /= cur;
		
		for(int k = 1;k <= n;k++) {
			if(k == i) continue;
			cur = mtx[k][i];
			for(int j = 1;j <= n;j++) mtx[k][j] -= mtx[i][j] * cur;
			for(int j = 1;j <= n;j++) val[k][j] -= val[i][j] * cur;
		}
	}
	
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n;j++) {
			val[i][j] /= mtx[i][i];
		}
	}
}

void solve() {
	for(int i = 1;i <= n;i++) {
		mtx[i][i] = 1.0; val[i][i] = 1.0;
		if(A[i] == 0) {
			for(int k = 0;k < (int) G[i].size();k++) {
				int v = G[i][k];
				if(v != n) mtx[i][v] -= 1.0 / (int) G[v].size();
			}
		}
	}
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("bzoj3640.in","r",stdin);
#endif
	
	read(n); read(m); read(hp);

	for(int i = 1;i <= n;i++) read(A[i]);
	
	int u,v;
	for(int i = 1;i <= m;i++) {
		read(u); read(v);
		G[u].push_back(v);
		if(u != v) G[v].push_back(u);
	}

	solve(); gauss();

	double ans = 0.0;
	
	for(int h = hp;h >= 1;h--) {
		memset(cons,0,sizeof cons);
		if(h == hp) cons[1] = 1.0;
		
		for(int i = 1;i <= n;i++) {
			if(A[i] && h + A[i] <= hp) {
				for(int k = 0;k < (int) G[i].size();k++) {
					int v = G[i][k];
					if(v != n) cons[i] += f[v][h + A[i]] / (int) G[v].size();
				}
			}
		}
		
		for(int i = 1;i <= n;i++) {
			for(int j = 1;j <= n;j++) {
				f[i][h] += val[i][j] * cons[j];
			}
		}
		
		ans += f[n][h];
	}

	printf("%.8lf\n",ans);

	return 0;
}
