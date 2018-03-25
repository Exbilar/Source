#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: map;
using std :: pair;
using std :: string;
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

string procStatus(){
    std :: ifstream t("/proc/self/status");
    return string(std :: istreambuf_iterator<char> (t),
				  std :: istreambuf_iterator<char> ());
}

map<int, int> nxt;
int lst[maxm], stk1[maxm], stk2[maxm], ai[maxm];

int top1, top2;
int ans1 = 1, ans2 = 1, n, K, d;

namespace Task0 {
	void solve() {
		for(int i = 1, j; i <= n; i = j + 1) {
			j = i; while(j < n && ai[i] == ai[j + 1]) j++;
			if(j - i > ans2 - ans1 || (j - i == ans2 - ans1 && i < ans1))
				ans1 = i, ans2 = j;
		}
		printf("%d %d\n", ans1, ans2);
	}
}

int E[maxm], add[maxm];

void pushup(int x) {
	E[x] = min(E[x << 1], E[x << 1 | 1]);
}

void build(int x, int l, int r) {
	add[x] = 0;
	if(l == r) return E[x] = -l, void();
	int mid = (l + r) >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
}

void pushadd(int x, int v) {
	E[x] += v; add[x] += v;
}

void pushdown(int x) {
	if(add[x]) {
		pushadd(x << 1, add[x]);
		pushadd(x << 1 | 1, add[x]);
		add[x] = 0;
	}
}

void modify(int x, int l, int r, int L, int R, int v) {
	if(l >= L && r <= R) return pushadd(x, v), void();
	pushdown(x);
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1, l, mid, L, R, v);
	if(R > mid)  modify(x << 1 | 1, mid + 1, r, L, R, v);
	pushup(x);
}

int query(int x, int l, int r, int lim) {
	if(l == r) return l;
	pushdown(x);
	int mid = (l + r) >> 1;
	if(E[x << 1 | 1] <= lim) return query(x << 1 | 1, mid + 1, r, lim);
	else return query(x << 1, l, mid, lim);
}

int Query(int x, int l, int r, int L, int R, int lim) {
	if(l >= L && r <= R) {
		if(E[x] <= lim) return query(x, l, r, lim);
		return 0;
	}
	pushdown(x);
	int mid = (l + r) >> 1, res = 0;
	if(L <= mid) chkmax(res, Query(x << 1, l, mid, L, R, lim));
	if(R > mid)  chkmax(res, Query(x << 1 | 1, mid + 1, r, L, R, lim));
	return res;
}

void solve(int l, int r) {
	if(l == r) return;
	for(int i = l; i <= r; i++) ai[i] = (ai[i] + 1e9) / d + 1;
	int R = r + 1; nxt.clear();
	stk1[0] = stk2[0] = r + 1; top1 = 0, top2 = 0;
	for(int i = r; i >= l; i--) {
		if(nxt.count(ai[i])) R = min(R, nxt[ai[i]]);
		
		while(top1 && ai[i] > ai[stk1[top1]]) {
			modify(1, 1, n, stk1[top1], stk1[top1 - 1] - 1, -ai[stk1[top1]]);
			top1--;
		}
		stk1[++top1] = i;
		modify(1, 1, n, stk1[top1], stk1[top1 - 1] - 1, ai[stk1[top1]]);

		while(top2 && ai[i] < ai[stk2[top2]]) {
			modify(1, 1, n, stk2[top2], stk2[top2 - 1] - 1, ai[stk2[top2]]);
			top2--;
		}
		stk2[++top2] = i;
		modify(1, 1, n, stk2[top2], stk2[top2 - 1] - 1, -ai[stk2[top2]]);

		int pos = Query(1, 1, n, i, R - 1, K - i);
		if((pos - i > ans2 - ans1) || (pos - i == ans2 - ans1 && i < ans1)) {
			ans1 = i; ans2 = pos;
		}
		
		nxt[ai[i]] = i;
	}
}

int main() {

	read(n); read(K); read(d);
	for(int i = 1; i <= n; i++) read(ai[i]);

	if(d == 0) return Task0 :: solve(), 0;

	build(1, 1, n);

	for(int i = 1, j; i <= n; i = j + 1) {
		j = i; while(j < n && (ai[i] % d + d) % d == (ai[j + 1] % d + d) % d) j++;
		solve(i, j);
	}

	printf("%d %d\n", ans1, ans2);
	
	return 0;
}
