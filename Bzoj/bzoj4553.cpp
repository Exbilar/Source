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
static const int maxm = 1e6 + 10;

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

struct Point {
	int x, y, z, id, typ;
	
	Point(int _x = 0, int _y = 0, int _z = 0, int _id = 0, int _typ = 0)
		: x(_x), y(_y), z(_z), id(_id), typ(_typ) {}
	
	bool operator < (const Point &rhs) const {
		return x < rhs.x;
	}
	
}pts[maxm], tmp[maxm];

int A[maxm], L[maxm], R[maxm], ddf[maxm], bit[maxm];
int n, q, tot, m, clc;

void clear() {
	clc++;
}

int lowbit(int x) {
	return x & -x;
}

void Upt(int k, int v) {
	for(int i = k; i <= m; i += lowbit(i)) {
		if(ddf[i] != clc) bit[i] = v, ddf[i] = clc;
		else chkmax(bit[i], v);
	}
}

int Qry(int k) {
	int res = 0;
	for(int i = k; i; i -= lowbit(i)) {
		if(ddf[i] == clc) chkmax(res, bit[i]);
	}
	return res;
}

int f[maxm];

void solve(int l, int r) {
	if(l == r) return ;
	
	int mid = (l + r) >> 1;
	int head = l, tail = mid + 1;
	
	for(int i = l; i <= r; i++) {
		if(pts[i].z <= mid) tmp[head++] = pts[i];
		else tmp[tail++] = pts[i];
	}
	
	for(int i = l; i <= r; i++) pts[i] = tmp[i];
	
	solve(l, mid); clear();

	int j = l;
	for(int i = mid + 1; i <= r; i++) {
		for(; j <= mid && pts[j].x <= pts[i].x; j++) {
			if(pts[j].typ == 1) Upt(pts[j].y, f[pts[j].id]);
		}
		if(pts[i].typ == 0)
			f[pts[i].id] = max(f[pts[i].id], Qry(pts[i].y) + 1);
	}
	
	solve(mid + 1, r);
	
	head = l, tail = mid + 1;
	for(int i = l; i <= r; i++) {
		if(head <= mid && (pts[head] < pts[tail] || tail > r)) tmp[i] = pts[head++];
		else tmp[i] = pts[tail++];
	}
	
	for(int i = l; i <= r; i++) pts[i] = tmp[i];
}

int main() {

	read(n); read(q);
	for(int i = 1; i <= n; i++) read(A[i]), f[i] = 1;

	for(int i = 1; i <= n; i++) L[i] = R[i] = A[i];
	for(int i = 1, x, y; i <= q; i++) {
		read(x); read(y);
		chkmin(L[x], y); chkmax(R[x], y);
	}

	for(int i = 1; i <= n; i++) chkmax(m, R[i]);

	for(int i = 1; i <= n; i++) {
		pts[++tot] = Point(A[i], L[i], tot, i, 0);
		pts[++tot] = Point(R[i], A[i], tot, i, 1);
	}

	std :: sort(pts + 1, pts + tot + 1);

	solve(1, tot);
	
	printf("%d\n", *std :: max_element(f + 1, f + n + 1));

	return 0;
}
