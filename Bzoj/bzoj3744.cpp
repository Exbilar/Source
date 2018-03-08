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
static const int maxm = 50000 + 10;
static const int maxn = 300;

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

int ai[maxm],vi[maxm],bit[maxm];
int rt[maxm * 4],lc[maxm * 25],rc[maxm * 25],size[maxm * 25];
int sum[maxn][maxm],posl[maxm],posr[maxm];
int n,m,sz;

int lowbit(int x) {
	return x & -x;
}

void Upt(int k, int v) {
	for(int i = k;i <= n + 10;i += lowbit(i)) bit[i] += v;
}

int Qry(int k) {
	int res = 0;
	for(int i = k;i;i -= lowbit(i)) res += bit[i];
	return res;
}

void insert(int &x, int lst, int l, int r, int pos, int v) {
	x = ++sz; lc[x] = lc[lst]; rc[x] = rc[lst]; size[x] = size[lst] + v;
	if(l == r) return void();
	int mid = (l + r) >> 1;
	if(pos <= mid) insert(lc[x], lc[lst], l, mid, pos, v);
	else insert(rc[x], rc[lst], mid + 1, r, pos, v);
}

int Query(int x, int lst, int l, int r, int pos) {
	if(!x) return 0;
	if(l == r) return size[x] - size[lst];
	int mid = (l + r) >> 1, siz = size[lc[x]] - size[lc[lst]];
	if(pos <= mid) return Query(lc[x], lc[lst], l, mid, pos);
	else return Query(rc[x], rc[lst], mid + 1, r, pos) + siz;
}

int main() {

	read(n); int Bsize = sqrt(n);
	for(int i = 0;i < n;i++) read(ai[i]), vi[i] = ai[i];

	std :: sort(vi, vi + n);
	int tot = std :: unique(vi, vi + n) - vi - 1;

	for(int i = 0;i < n;i++) {
		ai[i] = std :: lower_bound(vi, vi + tot, ai[i]) - vi + 1;
		insert(rt[i + 1], rt[i], 0, n, ai[i], 1);
	}

	for(int i = 0;i <= n / Bsize;i++) {
		memset(bit, 0, sizeof bit); Upt(n + 5 - ai[i * Bsize], 1);
		for(int j = i * Bsize + 1;j < n;j++) {
			sum[i][j] = sum[i][j - 1] + Qry(n + 5 - ai[j] - 1);
			Upt(n + 5 - ai[j], 1);
		}
	}

	read(m);

	int lstans = 0, l, r;
	while(m--) {
		read(l); read(r);
		l = (l ^ lstans) - 1; r = (r ^ lstans) - 1;
		lstans = 0;
		if(l / Bsize == r / Bsize) {
			for(int i = r;i >= l;i--) {
				lstans += Query(rt[r + 1], rt[i + 1], 0, n, ai[i] - 1);
			}
		} else {
			lstans += sum[l / Bsize + 1][r];
			for(int i = (l / Bsize + 1) * Bsize - 1;i >= l;i--) {
				lstans += Query(rt[r + 1], rt[i + 1], 0, n, ai[i] - 1);
			}
		}
		printf("%d\n", lstans);
	}
	
	return 0;
}
