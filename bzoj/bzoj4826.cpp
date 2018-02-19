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
static const int maxm = 2e5 + 10;

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

int rt[maxm],lc[maxm << 6],rc[maxm << 6];
LL add[maxm << 6],sum[maxm << 6];

int A[maxm],stk[maxm],li[maxm],ri[maxm];

int sz,n,m,top;
LL P1,P2;

struct Node {
	int x,l,r;
	LL v;
	
	Node() {}
	Node(int _,int __,int ___,LL ____) {x = _,l = __,r = ___,v = ____;}

	bool operator < (const Node &rhs) const {
		return x < rhs.x;
	}
}E[maxm << 2];

void insert(int &x,int lst,int l,int r,int L,int R,LL v) {
	x = ++sz; add[x] = add[lst]; lc[x] = lc[lst]; rc[x] = rc[lst];
	sum[x] = sum[lst] + (R - L + 1) * v;
	if(l == L && r == R) return add[x] += v,void();
	int mid = (l + r) >> 1;
	if(R <= mid) insert(lc[x],lc[lst],l,mid,L,R,v);
	else if(L > mid) insert(rc[x],rc[lst],mid + 1,r,L,R,v);
	else {
		insert(lc[x],lc[lst],l,mid,L,mid,v);
		insert(rc[x],rc[lst],mid + 1,r,mid + 1,R,v);
	}
}

LL Query(int x,int lst,int l,int r,int L,int R) {
	if(l == L && r == R) {
		return sum[x] - sum[lst];
	}
	int mid = (l + r) >> 1;
	LL res = (add[x] - add[lst]) * (R - L + 1);
	if(R <= mid) return res + Query(lc[x],lc[lst],l,mid,L,R);
	else if(L > mid) return res + Query(rc[x],rc[lst],mid + 1,r,L,R);
	else {
		res += Query(lc[x],lc[lst],l,mid,L,mid);
		res += Query(rc[x],rc[lst],mid + 1,r,mid + 1,R);
		return res;
	}
}

int main() {

	freopen("sf.in","r",stdin);
	
	read(n); read(m); read(P1); read(P2);
	for(int i = 1;i <= n;i++) read(A[i]);
	A[0] = INF,A[n + 1] = INF;

	stk[++top] = 0;
	for(int i = 1;i <= n;i++) {
		while(A[i] > A[stk[top]]) ri[stk[top--]] = i;
		stk[++top] = i;
	}
	while(top) ri[stk[top--]] = n + 1;

	stk[++top] = n + 1;
	for(int i = n;i >= 1;i--) {
		while(A[i] > A[stk[top]]) li[stk[top--]] = i;
		stk[++top] = i;
	}
	while(top) li[stk[top--]] = 0;

	int cnt = 0;
	for(int i = 1;i <= n;i++) {
		if(li[i] != 0 && ri[i] != n + 1) {
			E[++cnt] = Node(li[i],ri[i],ri[i],P1);
		}
		if(i != n) E[++cnt] = Node(i,i + 1,i + 1,P1);
		if(li[i] != 0 && i + 1 <= ri[i] - 1) {
			E[++cnt] = Node(li[i],i + 1,ri[i] - 1,P2);
		}
		if(ri[i] != n + 1 && li[i] + 1 <= i - 1) {
			E[++cnt] = Node(ri[i],li[i] + 1,i - 1,P2);
		}
	}

	std :: sort(E + 1,E + cnt + 1);

	int cur = 1;
	for(int i = 1;i <= n;i++) {
		rt[i] = rt[i - 1];
		if(E[cur].x == i) {
			insert(rt[i],rt[i - 1],1,n,E[cur].l,E[cur].r,E[cur].v); cur++;
			while(E[cur].x == i && cur <= cnt) {
				insert(rt[i],rt[i],1,n,E[cur].l,E[cur].r,E[cur].v);
				cur++;
			}
		}
	}

	int L,R;

	while(m--) {
		LL ans;
		read(L); read(R);
		printf("%lld\n",ans = Query(rt[R],rt[L - 1],1,n,L,R));
	}

	return 0;
}
