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
static const int maxn = 3e6 + 10;
static const int mod = 1e9 + 7;

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

int C[maxm],D[maxm],lft[maxm];
int mind[maxn];
int n;

void build_d(int x,int l,int r) {
	if(l == r) return mind[x] = D[l],void();
	int mid = (l + r) >> 1;
	build_d(x << 1,l,mid);
	build_d(x << 1 | 1,mid + 1,r);
	mind[x] = min(mind[x << 1],mind[x << 1 | 1]);
}

int Query_d(int x,int l,int r,int L,int R) {
	if(l >= L && r <= R) return mind[x];
	int mid = (l + r) >> 1,res = INF;
	if(L <= mid) chkmin(res,Query_d(x << 1,l,mid,L,R));
	if(R > mid)  chkmin(res,Query_d(x << 1 | 1,mid + 1,r,L,R));
	return res;
}

int maxc[maxn],posc[maxn];

void build_c(int x,int l,int r) {
	if(l == r) return maxc[x] = C[l],posc[x] = l,void();
	int mid = (l + r) >> 1;
	build_c(x << 1,l,mid);
	build_c(x << 1 | 1,mid + 1,r);
	if(maxc[x << 1] >= maxc[x << 1 | 1]) {
		maxc[x] = maxc[x << 1]; posc[x] = posc[x << 1];
	} else {
		maxc[x] = maxc[x << 1 | 1]; posc[x] = posc[x << 1 | 1];
	}
}

pii Query_c(int x,int l,int r,int L,int R) {
	if(l == L && r == R) return make_pair(maxc[x],posc[x]);
	int mid = (l + r) >> 1;
	if(R <= mid) return Query_c(x << 1,l,mid,L,R);
	else if(L > mid) return Query_c(x << 1 | 1,mid + 1,r,L,R);
	else {
		pii lhs = Query_c(x << 1,l,mid,L,mid);
		pii rhs = Query_c(x << 1 | 1,mid + 1,r,mid + 1,R);
		if(lhs.px >= rhs.px) return lhs;
		return rhs;
	}
}

struct Node {
	int maxf,val;
	Node() {maxf = -INF,val = 0;}
	Node(int _,int __) {maxf = _,val = __;}

	Node upt() {
		return Node(maxf + 1,val);
	}
	
	Node operator + (const Node &rhs) const {
		if(maxf != rhs.maxf) return maxf > rhs.maxf ? *this : rhs;
		return Node(maxf,(val + rhs.val) % mod);
	}

	bool operator != (const Node &rhs) const {
		return (maxf != rhs.maxf) || (val != rhs.val);
	}
	
}E[maxn],f[maxm],tag[maxn];

void build_f(int x,int l,int r) {
	if(l == r) return E[x] = f[l],void();
	int mid = (l + r) >> 1;
	build_f(x << 1,l,mid);
	build_f(x << 1 | 1,mid + 1,r);
	E[x] = E[x << 1] + E[x << 1 | 1];
}

inline void pushtag(int x,Node v) {
	E[x] = E[x] + v;
	tag[x] = tag[x] + v;
}

inline void pushdown(int x) {
	int lc = x << 1,rc = x << 1 | 1;
	if(tag[x] != Node(-INF,0)) {
		pushtag(lc,tag[x]);
		pushtag(rc,tag[x]);
		tag[x] = Node(-INF,0);
	}
}

void modify(int x,int l,int r,int L,int R,Node v) {
	if(l >= L && r <= R) return pushtag(x,v),void();
	int mid = (l + r) >> 1;
	pushdown(x);
	if(L <= mid) modify(x << 1,l,mid,L,R,v);
	if(R > mid)  modify(x << 1 | 1,mid + 1,r,L,R,v);
	E[x] = E[x << 1] + E[x << 1 | 1];
}

Node Query(int x,int l,int r,int L,int R) {
	if(L > R) return Node(-INF,0);
	if(l == L && r == R) return E[x];
	int mid = (l + r) >> 1;
	pushdown(x);
	if(R <= mid) return Query(x << 1,l,mid,L,R);
	else if(L > mid) return Query(x << 1 | 1,mid + 1,r,L,R);
	else return Query(x << 1,l,mid,L,mid) + Query(x << 1 | 1,mid + 1,r,mid + 1,R);
}

inline int find(int L,int R,int k) {
	int l = L,r = R,res = R + 1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(lft[mid] >= k) res = mid,r = mid - 1;
		else l = mid + 1;
	}
	return res;
}

inline void transform(int L,int R,int mid) {
	RG int cur = max(mid,L + C[mid]);
	RG int curl = max(L,lft[cur]),curr = min(mid - 1,cur - C[mid]);
	if(cur > R || curl >= mid) return ;

	Node tmp = Query(1,0,n,curl,curr);
	while(cur <= mid + C[mid] - 1 && cur <= R) {
		if(lft[cur] > curl) {
			if(lft[cur] >= mid) return ;
			curl = lft[cur];
			tmp = Query(1,0,n,curl,curr);
		}
		f[cur] = f[cur] + tmp.upt();
		if(curl <= ++curr) tmp = tmp + f[curr];
		cur++;
	}
	
	while(cur <= R) {
		if(lft[cur] > curl) {
			if(lft[cur] >= mid) return ;
			curl = lft[cur];
		}
		tmp = Query(1,0,n,curl,mid - 1); tmp = tmp.upt();
		int pos = find(L,R,lft[cur] + 1);
		if(pos > R) return modify(1,0,n,cur,R,tmp),void();
		modify(1,0,n,cur,pos - 1,tmp);
		cur = pos;
	}
}

void solve(int L,int R) {
	if(L > R) return ;
	if(L == R) {
		if(L) modify(1,0,n,L,L,f[L]);
		f[L] = Query(1,0,n,L,L);
		return ;
	}
	int mid = Query_c(1,0,n,L + 1,R).py;
	solve(L,mid - 1);
	transform(L,R,mid);
	solve(mid,R);
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("bzoj3711.in","r",stdin);
#endif
	
	read(n);
	for(RG int i = 1;i <= n;i++) {
		read(C[i]); read(D[i]);
	}
	
	f[0] = Node(0,1);
	build_d(1,0,n); build_c(1,0,n); build_f(1,0,n);

	for(RG int i = 1;i <= n;i++) {
		lft[i] = lft[i - 1];
		while(i - lft[i] > Query_d(1,0,n,lft[i] + 1,i)) lft[i]++;
	}

	solve(0,n);

	if(f[n].maxf >= 0) printf("%d %d\n",f[n].maxf,f[n].val);
	else puts("NIE");
	
	return 0;
}
