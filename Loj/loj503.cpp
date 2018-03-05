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
static const int maxm = 1e6 + 10;
static const int inf = 5e7 + 10;

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

struct Node {
	int opt,x,y,ans,id;
}q[maxm];

int lc[maxm * 20],rc[maxm * 20],E[maxm * 20];
int xi[maxm],yi[maxm],__ans[maxm],sum[maxm];
int rt,sz,n,m;

void newnode(int &x) {
	x = ++sz; lc[x] = 0; rc[x] = 0; E[x] = 0;
}

void modify(int &x, int l, int r, int L, int R, int v) {
	if(!x) newnode(x);
	if(l == L && r == R) return E[x] += v,void();
	int mid = (l + r) >> 1;
	if(R <= mid) modify(lc[x], l, mid, L, R, v);
	else if(L > mid) modify(rc[x], mid + 1, r, L, R, v);
	else {
		modify(lc[x], l, mid, L, mid, v);
		modify(rc[x], mid + 1, r, mid + 1, R, v);
	}
}

int Query(int x, int l, int r, int pos) {
	if(!x) return 0;
	if(l == r) return E[x];
	int mid = (l + r) >> 1;
	if(pos <= mid) return Query(lc[x], l, mid, pos) + E[x];
	else return Query(rc[x], mid + 1, r, pos) + E[x];
}

void init() {
	memset(sum,0,sizeof sum);
	memset(E,0,sizeof E);
	memset(lc,0,sizeof lc);
	memset(rc,0,sizeof rc);
}

void solve() {
	int tag = 0,cur = 1,ans = 0;
	sum[0] = 1; rt = 0; sz = 0;
	
	for(int i = 1;i <= n;i++) sum[i] = sum[i - 1] + xi[i];
	
	for(int i = 1;i < n;i++) {
		modify(rt, -inf, inf, min(sum[i], sum[i + 1]), max(sum[i], sum[i + 1]), 1);
	}
	
	for(int i = 0;i < n;i++) ans += (sum[i] > 0) ^ (sum[i + 1] > 0);

	for(int i = 1;i <= m;i++) {
		if(q[i].opt == 1) {
			if(cur == 1) continue;
			sum[--cur] -= tag;
			modify(rt, -inf, inf, min(sum[cur], sum[cur + 1]), max(sum[cur], sum[cur + 1]), 1);
		}
		if(q[i].opt == 2) {
			if(cur == n) continue;
			modify(rt, -inf, inf, min(sum[cur], sum[cur + 1]), max(sum[cur], sum[cur + 1]), -1);
			sum[cur++] += tag;
		}
		if(q[i].opt == 3) {
			ans -= Query(rt, -inf, inf, -tag);
			ans -= (sum[cur - 1] > 0) ^ (sum[cur] + tag > 0);
			int delta = q[i].x - xi[cur]; tag += delta; xi[cur] = q[i].x;
			ans += Query(rt, -inf, inf, -tag);
			ans += (sum[cur - 1] > 0) ^ (sum[cur] + tag > 0);
		}
		if(q[i].opt == 4) __ans[q[i].id] += ans;
	}
}

char str[10];

int main() {
	
	read(n);
	for(int i = 1;i <= n;i++) read(xi[i]),read(yi[i]);

	int tot = 0;
	
	read(m);
	for(int i = 1;i <= m;i++) {
		scanf("%s",str + 1);
		if(str[1] == 'B') q[i].opt = 1;
		if(str[1] == 'F') q[i].opt = 2;
		if(str[1] == 'C') read(q[i].x),read(q[i].y),q[i].opt = 3;
		if(str[1] == 'Q') q[i].opt = 4,q[i].id = ++tot;
	}

	solve();
	
	for(int i = 1;i <= n;i++) std :: swap(xi[i], yi[i]);
	for(int i = 1;i <= m;i++) {
		if(q[i].opt == 3) std :: swap(q[i].x, q[i].y);
	}

	solve();

	for(int i = 1;i <= tot;i++) printf("%d\n",__ans[i]);

	return 0;
}
