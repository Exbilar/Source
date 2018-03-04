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
static const int maxm = 1e5 + 10;
static const int mod = 998244353;

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

int val[maxm * 400],lc[maxm * 400],rc[maxm * 400],rt[maxm << 2];
int sz,n,m;

int fpm(int x, int k) {
	int res = 1;
	while(k) {
		if(k & 1) res = 1LL * res * x % mod;
		x = 1LL * x * x % mod;
		k >>= 1;
	}
	return res;
}

int inv(int x) {
	return fpm(x, mod - 2);
}

int merge(int x, int y) {
	int xx = (1 - x < 0 ? 1 - x + mod : 1 - x);
	int yy = (1 - y < 0 ? 1 - y + mod : 1 - y);
	return (1LL * x * y % mod + 1LL * xx * yy % mod) % mod;
}

void modify(int &x, int l, int r, int L, int R, int v) {
	if(!x) x = ++sz,val[x] = 1;
	if(l == L && r == R) return val[x] = merge(val[x], v),void();
	int mid = (l + r) >> 1;
	if(R <= mid) modify(lc[x], l, mid, L, R, v);
	else if(L > mid) modify(rc[x], mid + 1, r, L, R, v);
	else {
		modify(lc[x], l, mid, L, mid, v);
		modify(rc[x], mid + 1, r,mid + 1, R, v);
	}
}

int query(int x, int l, int r, int pos) {
	if(!x) return 1;
	if(l == r) return val[x];
	int mid = (l + r) >> 1,res = val[x];
	if(pos <= mid) return merge(res,query(lc[x], l, mid, pos));
	else return merge(res,query(rc[x], mid + 1, r, pos));
}

void insert(int x, int l, int r, int L1, int R1, int L2, int R2, int v) {
	if(l >= L1 && r <= R1) return modify(rt[x], 1, n, L2, R2, v),void();
	int mid = (l + r) >> 1;
	if(L1 <= mid) insert(x << 1, l, mid, L1, R1, L2, R2, v);
	if(R1 > mid)  insert(x << 1 | 1, mid + 1, r, L1 ,R1, L2, R2, v);
}

int Query(int o, int l, int r, int x, int y) {
	if(l == r) return query(rt[o], 1, n, y);
	int res = query(rt[o], 1, n, y);
	int mid = (l + r) >> 1;
	if(x <= mid) return merge(res,Query(o << 1, l, mid, x, y));
	else return merge(res,Query(o << 1 | 1, mid + 1, r, x, y));
}

int main() {

	freopen("bit.in","r",stdin);
	
	read(n); read(m);

	int opt,l,r;
	while(m--) {
		read(opt); read(l); read(r);
		if(opt == 1) {
			int Inv = inv(r - l + 1);
			int p1 = (1 - Inv + mod) % mod;

			if(l > 1) insert(1, 0, n, 1, l - 1, l, r, p1);
			if(r < n) insert(1, 0, n, l, r, r + 1, n, p1);

			int p2 = (1 - (Inv << 1) % mod + mod) % mod;

			insert(1, 0, n, l, r, l, r,p2);

			if(l > 1) insert(1, 0, n, 0, 0, 1, l - 1, 0);
			if(r < n) insert(1, 0, n, 0, 0, r + 1, n, 0);

			insert(1, 0, n, 0, 0, l, r, Inv);

		} else if(opt == 2) printf("%d\n",Query(1, 0, n, l - 1, r));
	}

	return 0;
}
