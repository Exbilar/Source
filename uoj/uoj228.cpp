#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long LL;

static const int maxm = 2e6 + 10;

LL sum[maxm],smax[maxm],smin[maxm],tag[maxm],A[maxm];
int n,m,opt;

void pushup(int x){
	int lc = x << 1,rc = x << 1 | 1;
	sum[x] = sum[lc] + sum[rc];
	smax[x] = max(smax[lc],smax[rc]);
	smin[x] = min(smin[lc],smin[rc]);
}

void pushdown(int x,int l,int r){
	int mid = (l + r) >> 1,lc = x << 1,rc = x << 1 | 1;
	tag[lc] += tag[x],tag[rc] += tag[x];
	smax[lc] += tag[x],smax[rc] += tag[x];
	smin[lc] += tag[x],smin[rc] += tag[x];
	sum[lc] += tag[x] * (mid - l + 1);
	sum[rc] += tag[x] * (r - mid);
	tag[x] = 0;
}

void build(int x,int l,int r){
	if(l == r) return sum[x] = smax[x] = smin[x] = A[l],void();
	int mid = (l + r) >> 1;
	build(x << 1,l,mid);
	build(x << 1 | 1,mid + 1,r);
	pushup(x);
}

void Add(int x,int l,int r,int L,int R,LL val){
	if(l >= L && r <= R){
		tag[x] += val,sum[x] += (r - l + 1) * val;
		smin[x] += val,smax[x] += val;
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(x,l,r);
	if(L <= mid) Add(x << 1,l,mid,L,R,val);
	if(R > mid) Add(x << 1 | 1,mid + 1,r,L,R,val);
	pushup(x);
}

void solve(int x,int l,int r,LL val){
	tag[x] += val,sum[x] += (r - l + 1) * val;
	smax[x] += val,smin[x] += val;
}

void sqr(int x,int l,int r,int L,int R){
	if(l >= L && r <= R){
		LL maxd = smax[x],mind = smin[x];
		if(maxd - mind <= 1 && (LL)sqrt(maxd) - (LL)sqrt(mind) == (maxd - mind))
			return solve(x,l,r,(LL)sqrt(maxd) - maxd),void();
	}
	int mid = (l + r) >> 1;
	pushdown(x,l,r);
	if(L <= mid) sqr(x << 1,l,mid,L,R);
	if(R > mid) sqr(x << 1 | 1,mid + 1,r,L,R);
	pushup(x);
}

LL Qry(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return sum[x];
	int mid = (l + r) >> 1;
	pushdown(x,l,r);
	LL ret = 0;
	if(L <= mid) ret += Qry(x << 1,l,mid,L,R);
	if(R > mid) ret += Qry(x << 1 | 1,mid + 1,r,L,R);
	pushup(x);
	return ret;
}

int main(){
	int x,y;LL z;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%lld",&A[i]);
	build(1,1,n);

	while(m--){
		scanf("%d%d%d",&opt,&x,&y);
		if(opt == 1) scanf("%lld",&z),Add(1,1,n,x,y,z);
		if(opt == 2) sqr(1,1,n,x,y);
		if(opt == 3) printf("%lld\n",Qry(1,1,n,x,y));
	}
	
	return 0;
}
