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
static const int maxn = 1e7 + 10;

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

LL size[maxm],sum[maxm],A[maxm],ddf[maxm];
LL lc[maxm],rc[maxm],fst[maxm],nxt[maxn],to[maxn];
LL rt,cnt,sz,ans,n,m;

void ins(LL f,LL t) {
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	ddf[t]++;
}

void build(LL &x,LL l,LL r) {
	x = ++sz; size[x] = sum[r] - sum[l - 1];
	if(l == r) return ;
	LL mid = (l + r) >> 1;
	build(lc[x],l,mid);
	build(rc[x],mid + 1,r);
}

void insert(LL x,LL l,LL r,LL L,LL R,LL v) {
	if(l >= L && r <= R) return ins(x,v),void();
	LL mid = (l + r) >> 1;
	if(L <= mid) insert(lc[x],l,mid,L,R,v);
	if(R > mid)  insert(rc[x],mid + 1,r,L,R,v);
}

void solve(LL x) {
	for(LL u = fst[x];u;u = nxt[u]) {
		LL v = to[u];
		if(!(--ddf[v])) ans++;
	}
}

void modify(LL x,LL l,LL r,LL pos) {
	size[x]--;
	if(!size[x]) solve(x);
	if(l == r) return ;
	LL mid = (l + r) >> 1;
	if(pos <= mid) modify(lc[x],l,mid,pos);
	else modify(rc[x],mid + 1,r,pos);
}

int main() {

	read(n); read(m);
	for(LL i = 1;i <= n;i++) {
		read(A[i]),sum[i] = sum[i - 1] + A[i];
	}

	build(rt,1,n);

	LL L,R,Q,x;
	for(LL i = 1;i <= m;i++) {
		read(L); read(R);
		insert(rt,1,n,L,R,i);
	}

	read(Q);

	while(Q--) {
		read(x);
		x = (x + ans - 1) % n + 1;
		modify(1,1,n,x);
		printf("%lld\n",ans);
	}

	return 0;
}
