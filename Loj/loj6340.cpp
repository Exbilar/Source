#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 8e5 + 10;

template <class T> inline bool chkmax(T &x,T y){
	return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
	return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in){
	in = 0; char ch = getchar(); T f = 1;
	for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
	for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

struct Optimize {
	int opt, x1, y1, x2, y2, id;
}q[maxm];

struct Point {
	int opt, x, y, id;
}ddf[maxm], tmp[maxm];

bool cmp1(const Point &lhs, const Point &rhs) {
	return lhs.x > rhs.x;
}

bool cmp2(const Point &lhs, const Point &rhs) {
	return lhs.x < rhs.x;
}

int v[maxm], ans[maxm], asd[maxm];

char opt[10];

int n, tot;

struct Bit {
	int bit[maxm], asd[maxm];
	int maxn, clc;

	inline void init(const int n) {
		memset(bit, 0, sizeof bit);
		memset(asd, 0, sizeof asd);
		maxn = n; clc = 0;
	}

	inline void clear() {
		clc += 1;
	}

	inline int lowbit(const int x) {
		return x & -x;
	}

	inline void Upt(const int k, const int v) {
		for(register int i = k; i <= maxn; i += lowbit(i)) {
			if(asd[i] == clc) bit[i] += v;
			else asd[i] = clc, bit[i] = v;
		}
	}

	inline int Qry(const int k) {
		int res = 0;
		for(register int i = k; i; i -= lowbit(i)) {
			if(asd[i] == clc) res += bit[i];
		}
		return res;
	}

	inline int query(const int l, const int r) {
		if(l > r) return 0;
		return Qry(r) - Qry(l - 1);
	}
	
}Tx1, Tx2, Ty1, Ty2;

Bit T;

void solve1(const int l, const int r) {
	if(l == r) return ;
	int mid = (l + r) >> 1;

	int head = l, tail = mid + 1;
	for(register int i = l; i <= r; i++) {
		if(ddf[i].id <= mid) tmp[head++] = ddf[i];
		else tmp[tail++] = ddf[i];
	}
	for(register int i = l; i <= r; i++) ddf[i] = tmp[i];

	solve1(l, mid);

	T.clear();
	
	register int j = l;
	for(register int i = mid + 1; i <= r; i++) {
		for(; ddf[j].x > ddf[i].x && j <= mid; j++) {
			if(ddf[j].opt == 1) T.Upt(ddf[j].y, 1);
			else if(ddf[j].opt == 2) T.Upt(ddf[j].y, -1);
		}
		if(ddf[i].opt == 3) {
			ans[ddf[i].id] += T.query(ddf[i].y + 1, tot);
		}
	}

	solve1(mid + 1, r);
	
	head = l; tail = mid + 1;
	for(register int i = l; i <= r; i++) {
		if(head <= mid && (cmp1(ddf[head], ddf[tail]) || tail > r))
			tmp[i] = ddf[head++];
		else tmp[i] = ddf[tail++];
	}
	
	for(register int i = l; i <= r; i++) ddf[i] = tmp[i];
}

void solve2(const int l, const int r) {
	if(l == r) return ;
	int mid = (l + r) >> 1;

	int head = l, tail = mid + 1;
	for(register int i = l; i <= r; i++) {
		if(ddf[i].id <= mid) tmp[head++] = ddf[i];
		else tmp[tail++] = ddf[i];
	}
	for(register int i = l; i <= r; i++) ddf[i] = tmp[i];

	solve2(l, mid);

	T.clear();
	
	register int j = l;
	for(register int i = mid + 1; i <= r; i++) {
		for(; ddf[j].x > ddf[i].x && j <= mid; j++) {
			if(ddf[j].opt == 1) T.Upt(ddf[j].y, 1);
			else if(ddf[j].opt == 2) T.Upt(ddf[j].y, -1);
		}
		if(ddf[i].opt == 3) {
			ans[ddf[i].id] += T.query(1, ddf[i].y - 1);
		}
	}

	solve2(mid + 1, r);
	
	head = l; tail = mid + 1;
	for(register int i = l; i <= r; i++) {
		if(head <= mid && (cmp1(ddf[head], ddf[tail]) || tail > r))
			tmp[i] = ddf[head++];
		else tmp[i] = ddf[tail++];
	}
	
	for(register int i = l; i <= r; i++) ddf[i] = tmp[i];
}

void solve3(const int l, const int r) {
	if(l == r) return ;
	int mid = (l + r) >> 1;

	int head = l, tail = mid + 1;
	for(register int i = l; i <= r; i++) {
		if(ddf[i].id <= mid) tmp[head++] = ddf[i];
		else tmp[tail++] = ddf[i];
	}
	for(register int i = l; i <= r; i++) ddf[i] = tmp[i];

	solve3(l, mid);

	T.clear();
	
	register int j = l;
	for(register int i = mid + 1; i <= r; i++) {
		for(; ddf[j].x < ddf[i].x && j <= mid; j++) {
			if(ddf[j].opt == 1) T.Upt(ddf[j].y, 1);
			else if(ddf[j].opt == 2) T.Upt(ddf[j].y, -1);
		}
		if(ddf[i].opt == 3) {
			ans[ddf[i].id] += T.query(ddf[i].y + 1, tot);
		}
	}

	solve3(mid + 1, r);
	
	head = l; tail = mid + 1;
	for(register int i = l; i <= r; i++) {
		if(head <= mid && (cmp2(ddf[head], ddf[tail]) || tail > r))
			tmp[i] = ddf[head++];
		else tmp[i] = ddf[tail++];
	}
	
	for(register int i = l; i <= r; i++) ddf[i] = tmp[i];
}

void solve4(const int l, const int r) {
	if(l == r) return ;
	int mid = (l + r) >> 1;

	int head = l, tail = mid + 1;
	for(register int i = l; i <= r; i++) {
		if(ddf[i].id <= mid) tmp[head++] = ddf[i];
		else tmp[tail++] = ddf[i];
	}
	for(register int i = l; i <= r; i++) ddf[i] = tmp[i];

	solve4(l, mid);

	T.clear();
	
	register int j = l;
	for(register int i = mid + 1; i <= r; i++) {
		for(; ddf[j].x < ddf[i].x && j <= mid; j++) {
			if(ddf[j].opt == 1) T.Upt(ddf[j].y, 1);
			else if(ddf[j].opt == 2) T.Upt(ddf[j].y, -1);
		}
		if(ddf[i].opt == 3) {
			ans[ddf[i].id] += T.query(1, ddf[i].y - 1);
		}
	}

	solve4(mid + 1, r);

	head = l; tail = mid + 1;
	for(register int i = l; i <= r; i++) {
		if(head <= mid && (cmp2(ddf[head], ddf[tail]) || tail > r))
			tmp[i] = ddf[head++];
		else tmp[i] = ddf[tail++];
	}
	
	for(register int i = l; i <= r; i++) ddf[i] = tmp[i];
}

int main() {

	read(n);
	
	for(register int i = 1; i <= n; i++) {
		scanf("%s", opt); int u, v, x, y;
		if(opt[0] == 'I') {
			q[i].opt = 1;
			read(u); read(v); read(x); read(y);
			q[i].x1 = u; q[i].y1 = y;
			q[i].x2 = x; q[i].y2 = v;
			asd[++asd[0]] = i;
		}
		if(opt[0] == 'D') {
			q[i].opt = 2; read(u);
			q[i].x1 = q[asd[u]].x1; q[i].y1 = q[asd[u]].y1;
			q[i].x2 = q[asd[u]].x2; q[i].y2 = q[asd[u]].y2;
		}
		if(opt[0] == 'Q') {
			q[i].opt = 3;
			read(u); read(v); read(x); read(y);
			q[i].x1 = u; q[i].y1 = y;
			q[i].x2 = x; q[i].y2 = v;
		}
		q[i].id = i;
	}

	for(register int i = 1; i <= n; i++) {
		if(q[i].opt != 2) {
			v[++tot] = q[i].x1; v[++tot] = q[i].x2;
			v[++tot] = q[i].y1; v[++tot] = q[i].y2;
		}
	}

	std :: sort(v + 1, v + tot + 1);
	tot = std :: unique(v + 1, v + tot + 1) - v - 1;
	
	for(register int i = 1; i <= n; i++) {
		q[i].x1 = std :: lower_bound(v + 1, v + tot + 1, q[i].x1) - v;
		q[i].x2 = std :: lower_bound(v + 1, v + tot + 1, q[i].x2) - v;
		q[i].y1 = std :: lower_bound(v + 1, v + tot + 1, q[i].y1) - v;
		q[i].y2 = std :: lower_bound(v + 1, v + tot + 1, q[i].y2) - v;
	}

	Tx1.init(tot); Ty1.init(tot); Tx2.init(tot); Ty2.init(tot);

	int cur = 0;
	for(register int i = 1; i <= n; i++) {
		if(q[i].opt == 3) {
			ans[i] = cur;
			ans[i] -= Tx1.query(1, q[i].x1 - 1);
			ans[i] -= Tx2.query(q[i].x2 + 1, tot);
			ans[i] -= Ty1.query(q[i].y1 + 1, tot);
			ans[i] -= Ty2.query(1, q[i].y2 - 1);
		} else if(q[i].opt == 1){
			Tx1.Upt(q[i].x2, 1); Tx2.Upt(q[i].x1, 1);
			Ty1.Upt(q[i].y2, 1); Ty2.Upt(q[i].y1, 1);
			cur += 1;
		} else if(q[i].opt == 2) {
			Tx1.Upt(q[i].x2, -1); Tx2.Upt(q[i].x1, -1);
			Ty1.Upt(q[i].y2, -1); Ty2.Upt(q[i].y1, -1);
			cur -= 1;
		}
	}

	for(register int i = 1; i <= n; i++) {
		ddf[i].opt = q[i].opt; ddf[i].id = q[i].id;
		if(q[i].opt != 3) {
			ddf[i].x = q[i].x1; ddf[i].y = q[i].y2;
		} else {
			ddf[i].x = q[i].x2; ddf[i].y = q[i].y1;
		}
	}

	std :: sort(ddf + 1, ddf + n + 1, cmp1);

	T.init(tot);
	solve1(1, n);
	
	for(register int i = 1; i <= n; i++) {
		ddf[i].opt = q[i].opt; ddf[i].id = q[i].id;
		if(q[i].opt != 3) {
			ddf[i].x = q[i].x1; ddf[i].y = q[i].y1;
		} else {
			ddf[i].x = q[i].x2; ddf[i].y = q[i].y2;
		}
	}

	std :: sort(ddf + 1, ddf + n + 1, cmp1);

	T.init(tot);
	solve2(1, n);

	for(register int i = 1; i <= n; i++) {
		ddf[i].opt = q[i].opt; ddf[i].id = q[i].id;
		if(q[i].opt != 3) {
			ddf[i].x = q[i].x2; ddf[i].y = q[i].y2;
		} else {
			ddf[i].x = q[i].x1; ddf[i].y = q[i].y1;
		}
	}

	std :: sort(ddf + 1, ddf + n + 1, cmp2);

	T.init(tot);
	solve3(1, n);

	for(register int i = 1; i <= n; i++) {
		ddf[i].opt = q[i].opt; ddf[i].id = q[i].id;
		if(q[i].opt != 3) {
			ddf[i].x = q[i].x2; ddf[i].y = q[i].y1;
		} else {
			ddf[i].x = q[i].x1; ddf[i].y = q[i].y2;
		}
	}

	std :: sort(ddf + 1, ddf + n + 1, cmp2);

	T.init(tot);
	solve4(1, n);

	for(register int i = 1; i <= n; i++) {
		if(q[i].opt == 3) printf("%d\n", ans[i]);
	}

	return 0;
}
