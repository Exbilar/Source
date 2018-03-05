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
static const int maxm = 6e4 + 10;
static const int maxn = 30 + 5;

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

struct Optimize{
	int opt,v,w,e;
}qry[maxm];

int use[maxm],ans[maxm],f[maxn][maxm];
int Q,xord,maxv,typ;

vector<pii> ddf[maxm];

void modify(int x,int l,int r,int L,int R,pii v) {
	if(l >= L && r <= R) {
		ddf[x].push_back(v);
		return ;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1,l,mid,L,R,v);
	if(R > mid)  modify(x << 1 | 1,mid + 1,r,L,R,v);
}

void solve(int x,int l,int r,int dpt) {
	if(use[l]) {
		if(qry[l].opt == 1) {
			qry[l].v -= xord;
			qry[l].w -= xord;
			qry[l].e -= xord;
			modify(1,1,Q,l,qry[l].e,make_pair(qry[l].v,qry[l].w));
		}
		use[l] = 0;
	}

	memcpy(f[dpt],f[dpt - 1],sizeof f[dpt - 1]);
	
	for(int i = 0;i < ddf[x].size();i++) {
		int v = ddf[x][i].px,w = ddf[x][i].py;
		for(int j = maxv;j >= v;j--) {
			if(f[dpt][j - v] != -INF) {
				chkmax(f[dpt][j],f[dpt][j - v] + w);
			}
		}
	}

	if(l == r) {
		if(qry[l].opt == 2) {
			int v = qry[l].v - xord;
			if(f[dpt][v] == -INF) {
				ans[l] = -1;
				xord = 0;
			}
			else {
				ans[l] = f[dpt][v];
				xord = typ * (ans[l] ^ 1);
			}
		}
		return ;
	}

	int mid = (l + r) >> 1;
	solve(x << 1,l,mid,dpt + 1);
	solve(x << 1 | 1,mid + 1,r,dpt + 1);
}

int main() {

	read(Q); read(maxv); read(typ);
	for(int i = 1;i <= Q;i++) use[i] = 1;
	std :: fill(f[0] + 1,f[0] + maxv + 1,-INF);

	for(int i = 1;i <= Q;i++) {
		read(qry[i].opt);
		if(qry[i].opt == 1) read(qry[i].v),read(qry[i].w),read(qry[i].e);
		if(qry[i].opt == 2) read(qry[i].v);
	}

	solve(1,1,Q,1);

	for(int i = 1;i <= Q;i++) {
		if(qry[i].opt == 2) {
			if(ans[i] >= 0) printf("%d %d\n",1,ans[i]);
			else puts("0 0");
		}
	}
	
	return 0;
}
