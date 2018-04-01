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
static const int maxm = 5e5 + 10;

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

int A[maxm], val[maxm], smin[maxm];
int n, tot, m;

void build(int x, int l, int r) {
	smin[x] = INF;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
}

void modify(int x, int l, int r, int pos, int v) {
	if(l == r) return chkmin(smin[x], v), void();
	int mid = (l + r) >> 1;
	if(pos <= mid) modify(x << 1, l, mid, pos, v);
	else modify(x << 1 | 1, mid + 1, r, pos, v);
	smin[x] = min(smin[x << 1], smin[x << 1 | 1]);
}

int Query(int x, int l, int r, int L, int R) {
	if(l >= L && r <= R) return smin[x];
	int mid = (l + r) >> 1, res = INF;
	if(L <= mid) chkmin(res, Query(x << 1, l, mid, L, R));
	if(R > mid)  chkmin(res, Query(x << 1 | 1, mid + 1, r, L, R));
	return res;
}

int less[maxm], greater[maxm];
int F[maxm][40], G[maxm][40];

int getF(int x, int v) {
	F[x][++F[x][0]] = v;
	for(int i = 1; i <= G[v][0]; i++)
		if(A[G[v][i]] < A[x]) return getF(x, G[v][i]);
}

int getG(int x, int v) {
	G[x][++G[x][0]] = v;
	for(int i = 1; i <= F[v][0]; i++)
		if(A[F[v][i]] > A[x]) return getG(x, F[v][i]);
}

struct Query {
	int l, r, id;
	bool operator < (const Query &rhs) const {
		return r < rhs.r;
	}
}q[maxm];

int ans[maxm], asd[maxm];

int main() {

	read(n); read(m);
	for(int i = 1; i <= n; i++) read(A[i]), val[i] = A[i], asd[i] = A[i];
	
	std :: sort(val + 1, val + n + 1);
	tot = std :: unique(val + 1, val + n + 1) - val - 1;

	for(int i = 1; i <= n; i++) {
		A[i] = std :: lower_bound(val + 1, val + tot + 1, A[i]) - val;
	}

	static int stk[maxm], top = 0;

	for(int i = 1; i <= n; i++) {
		while(top && A[stk[top]] >= A[i]) top--;
		if(top) less[i] = stk[top];
		stk[++top] = i;
	}

	top = 0;

	for(int i = 1; i <= n; i++) {
		while(top && A[stk[top]] <= A[i]) top--;
		if(top) greater[i] = stk[top];
		stk[++top] = i;
	}

	for(int i = 1; i <= n; i++) {
		if(less[i]) getF(i, less[i]);
		if(greater[i]) getG(i, greater[i]);
	}

	for(int i = 1; i <= m; i++) {
		read(q[i].l); read(q[i].r);
		q[i].id = i;
	}

	std :: sort(q + 1, q + m + 1);

	build(1, 1, n);
	
	for(int i = 1, cur = 1; i <= n; i++) {
		for(int j = 1; j <= F[i][0]; j++) {
			modify(1, 1, n, F[i][j], asd[i] - asd[F[i][j]]);
		}
		for(int j = 1; j <= G[i][0]; j++) {
			modify(1, 1, n, G[i][j], asd[G[i][j]] - asd[i]);
		}
		while(q[cur].r == i && cur <= m) {
			ans[q[cur].id] = Query(1, 1, n, q[cur].l, i);
			cur++;
		}
	}

	for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);

	return 0;
}
