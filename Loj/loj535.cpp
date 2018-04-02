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
static const int maxm = 2e6 + 10;

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

string procStatus(){
    std :: ifstream t("/proc/self/status");
    return string(std :: istreambuf_iterator<char> (t),
				  std :: istreambuf_iterator<char> ());
}

struct Point {
	int x, l, r, v;
	Point() { }
	Point(int _x, int _l, int _r, int _v) { x = _x, l = _l, r = _r, v = _v; }
	bool operator < (const Point &rhs) const {
		return x < rhs.x;
	}
}P[maxm];

int E[maxm], add[maxm];
int n, tot;

void pushadd(int x, int v) {
	add[x] += v; E[x] += v;
}

void pushdown(int x) {
	if(add[x]) {
		pushadd(x << 1, add[x]);
		pushadd(x << 1 | 1, add[x]);
		add[x] = 0;
	}
}

void pushup(int x) {
	E[x] = max(E[x << 1], E[x << 1 | 1]);
}

void modify(int x, int l, int r, int L, int R, int v) {
	if(l >= L && r <= R) return pushadd(x, v), void();
	pushdown(x);
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1, l, mid, L, R, v);
	if(R > mid)  modify(x << 1 | 1, mid + 1, r, L, R, v);
	pushup(x);
}

int Query(int x, int l, int r, int L, int R) {
	if(l >= L && r <= R) return E[x];
	pushdown(x);
	int mid = (l + r) >> 1, res = 0;
	if(L <= mid) chkmax(res, Query(x << 1, l, mid, L, R));
	if(R > mid)  chkmax(res, Query(x << 1 | 1, mid + 1, r, L, R));
	return res;
}

int bit[maxm];

int lowbit(int x) {
	return x & -x;
}

void Upt(int k, int v) {
	for(int i = k; i <= n; i += lowbit(i)) bit[i] += v;
}

int Qry(int k) {
	int res = 0;
	for(int i = k; i; i -= lowbit(i)) res += bit[i];
	return res;
}

int pre[maxm], suf[maxm], h[maxm];

int findL(int L, int R, int ht) {
	int l = L, r = R, res = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(pre[mid] >= ht) res = mid, r = mid - 1;
		else l = mid + 1;
	}
	return res;
}

int findR(int L, int R, int ht) {
	int l = L, r = R, res = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(suf[mid] <= ht) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	return res;
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("columns.in", "r", stdin);
	freopen("columns.out", "w", stdout);
#endif
	
	read(n);
	for(int i = 1; i <= n; i++) read(h[i]);

	pre[0] = 0;
	for(int i = 1; i <= n; i++) pre[i] = max(pre[i - 1], h[i]);
	
	suf[n + 1] = n + 1;
	for(int i = n; i >= 1; i--) suf[i] = min(suf[i + 1], h[i]);

	for(int i = 1; i <= n; i++) {
		if(pre[i] == h[i] || suf[i] == h[i]) continue;
		int l = findL(1, i - 1, h[i]);
		int r = findR(i + 1, n, h[i]);
		P[++tot] = Point(l, i + 1, r, 1);
		P[++tot] = Point(i, i + 1, r, -1);
	}

	std :: sort(P + 1, P + tot + 1);

	LL ans = 0;
	
	for(int i = 1; i <= tot; i++) {
		modify(1, 1, n, P[i].l, P[i].r, P[i].v);
		chkmax(ans, 1LL * Query(1, 1, n, 1, n));
	}

	ans *= -2LL;
	
	for(int i = n; i >= 1; i--) {
		ans += Qry(h[i]);
		Upt(h[i], 1);
	}

	printf("%lld\n", ans);

	return 0;
}
