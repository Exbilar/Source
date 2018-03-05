#include <cstdio>
#include <algorithm>

using std :: max;
using std :: min;

typedef long long LL;

static const LL maxm = 4e6 + 10;
static const LL INF = ~(1 << 31);

LL se[maxm],mx[maxm],sum[maxm],cnt[maxm],A[maxm];
LL n,m,T,opt;

void pushup(LL x){
	cnt[x] = 0;
	LL lc = x << 1,rc = x << 1 | 1;
	
	sum[x] = sum[lc] + sum[rc];
	
	mx[x] = max(mx[lc],mx[rc]);
	
	se[x] = max(se[lc],se[rc]);
	if(mx[lc] != mx[rc]) se[x] = max(se[x],min(mx[lc],mx[rc]));
	
	if(mx[x] == mx[lc]) cnt[x] += cnt[lc];
	if(mx[x] == mx[rc]) cnt[x] += cnt[rc];
}

void pushtag(LL x,LL val){
	if(val >= mx[x]) return;
	sum[x] += 1LL * (val - mx[x]) * cnt[x],mx[x] = val;
}

void pushdown(LL x){
	LL lc = x << 1,rc = x << 1 | 1;
	pushtag(lc,mx[x]);
	pushtag(rc,mx[x]);
}

void build(LL x,LL l,LL r){
	if(l == r) return sum[x] = mx[x] = A[l],cnt[x] = 1,se[x] = -1,void();
	LL mid = (l + r) >> 1;
	build(x << 1,l,mid);
	build(x << 1 | 1,mid + 1,r);
	pushup(x);
}

void modify(LL x,LL l,LL r,LL L,LL R,LL val){
	if(val >= mx[x]) return;
	if(l >= L && r <= R && val > se[x]) return pushtag(x,val),void();
	pushdown(x);
	LL mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1,l,mid,L,R,val);
	if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,val);
	pushup(x);
}

LL Qry_sum(LL x,LL l,LL r,LL L,LL R){
	if(l >= L && r <= R) return sum[x];
	pushdown(x);
	LL mid = (l + r) >> 1;LL ret = 0;
	if(L <= mid) ret += Qry_sum(x << 1,l,mid,L,R);
	if(R > mid) ret += Qry_sum(x << 1 | 1,mid + 1,r,L,R);
	return ret;
}

LL Qry_max(LL x,LL l,LL r,LL L,LL R){
	if(l >= L && r <= R) return mx[x];
	pushdown(x);
	LL mid = (l + r) >> 1;LL ret = -INF;
	if(L <= mid) ret = max(ret,Qry_max(x << 1,l,mid,L,R));
	if(R > mid) ret = max(ret,Qry_max(x << 1 | 1,mid + 1,r,L,R));
	return ret;
}

void solve(){
	LL l,r,val;
	scanf("%lld%lld",&n,&m);
	for(LL i = 1;i <= n;i++) scanf("%lld",&A[i]);
	build(1,1,n);
	
	while(m--){
		scanf("%lld",&opt);
		if(opt == 0) scanf("%lld%lld%lld",&l,&r,&val),modify(1,1,n,l,r,val);
		if(opt == 1) scanf("%lld%lld",&l,&r),printf("%lld\n",Qry_max(1,1,n,l,r));
		if(opt == 2) scanf("%lld%lld",&l,&r),printf("%lld\n",Qry_sum(1,1,n,l,r));
	}
	
}

int main(){
	scanf("%lld",&T);
	while(T--) solve();
	
	return 0;
}
