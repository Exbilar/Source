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

typedef unsigned long long LL;
typedef pair<LL, LL> pll;
typedef pair<int, int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 1e6 + 10;
static const int base = 131;

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

int ai[maxm];
LL pwr[maxm], E[maxm][2];

int n, cas;

inline LL add(const LL x, const LL y) {
	return x + y;
}

inline void pushup(int x, int l, int r) {
	int mid = (l + r) >> 1, lc = x << 1, rc = x << 1 | 1;
	E[x][0] = (E[lc][0] + E[rc][0] * pwr[mid - l + 1]);
	E[x][1] = (E[rc][1] + E[lc][1] * pwr[r - mid]);
}

void modify(int x, int l, int r, int pos) {
	if(l == r) return E[x][0] = E[x][1] = base, void();
	int mid = (l + r) >> 1;
	if(pos <= mid) modify(x << 1, l, mid, pos);
	else modify(x << 1 | 1, mid + 1, r, pos);
	pushup(x, l, r);
}

LL Query0(int x, int l, int r, int L, int R) {
	if(l == L && r == R) return E[x][0];
	int mid = (l + r) >> 1;
	if(R <= mid) return Query0(x << 1, l, mid, L, R);
	else if(L > mid) return Query0(x << 1 | 1, mid + 1, r, L, R);
	else return add(Query0(x << 1, l, mid, L, mid),
					Query0(x << 1 | 1, mid + 1, r, mid + 1, R) * pwr[mid - L + 1]);
}

LL Query1(int x, int l, int r, int L, int R) {
	if(l == L && r == R) return E[x][1];
	int mid = (l + r) >> 1;
	if(R <= mid) return Query1(x << 1, l, mid, L, R);
	else if(L > mid) return Query1(x << 1 | 1, mid + 1, r, L, R);
	else return add(Query1(x << 1, l, mid, L, mid) * pwr[R - mid],
					Query1(x << 1 | 1, mid + 1, r, mid + 1, R));
}

inline bool check(int x) {
	int len = min(x - 1, n - x);
	modify(1, 1, n, x);
	if(x == 1 || x == n) return false;
	LL res1 = Query0(1, 1, n, x - len, x - 1);
	LL res2 = Query1(1, 1, n, x + 1, x + len);
	return res1 != res2;
}

int main() {

	pwr[0] = 1;
	for(int i = 1; i <= 10000; i++) {
		pwr[i] = 1LL * pwr[i - 1] * base;
	}

	read(cas);

	while(cas--) {
		memset(E, 0, sizeof E);
		read(n); bool chk = false;
		for(int i = 1; i <= n; i++) read(ai[i]);
		for(int i = 1; i <= n; i++) {
			if(check(ai[i])) {
				chk = true; break;
			}
		}
		if(!chk) puts("N");
		else puts("Y");
	}

	return 0;
}
