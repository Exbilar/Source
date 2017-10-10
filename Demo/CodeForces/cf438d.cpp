#include <cstdio>
#include <algorithm>

using std :: max;
using std :: min;

typedef long long LL;

static const int maxm = 2e6 + 10;

LL sum[maxm],smax[maxm];
int n,m,opt;

void pushup(int x){
	int lc = x << 1;
	int rc = x << 1 | 1;
	sum[x] = sum[lc] + sum[rc];
	smax[x] = max(smax[lc],smax[rc]);
}

void build(int x,int l,int r){
	if(l == r) return scanf("%lld",&sum[x]),smax[x] = sum[x],void();
	int mid = (l + r) >> 1;
	build(x << 1,l,mid);
	build(x << 1 | 1,mid + 1,r);
	pushup(x);
}

void modify(int x,int l,int r,int pos,int val){
	if(l == r) return smax[x] = sum[x] = val,void();
	int mid = (l + r) >> 1;
	if(pos <= mid) modify(x << 1,l,mid,pos,val);
	else modify(x << 1 | 1,mid + 1,r,pos,val);
	pushup(x);
}

void smod(int x,int l,int r,int L,int R,int MOD){
	if(l >= L && r <= R){
		if(l == r) return sum[x] %= MOD,smax[x] = sum[x],void();
		if(smax[x] < MOD) return;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) smod(x << 1,l,mid,L,R,MOD);
	if(R > mid) smod(x << 1 | 1,mid + 1,r,L,R,MOD);
	pushup(x);
}

LL Qry(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return sum[x];
	int mid = (l + r) >> 1;LL ret = 0;
	if(L <= mid) ret += Qry(x << 1,l,mid,L,R);
	if(R > mid) ret += Qry(x << 1 | 1,mid + 1,r,L,R);
	pushup(x);
	return ret;
}

int main(){
	int x,y,z;
	scanf("%d%d",&n,&m);
	build(1,1,n);

	while(m--){
		scanf("%d",&opt);
		if(opt == 1) scanf("%d%d",&x,&y),printf("%lld\n",Qry(1,1,n,x,y));
		if(opt == 2) scanf("%d%d%d",&x,&y,&z),smod(1,1,n,x,y,z);
		if(opt == 3) scanf("%d%d",&x,&z),modify(1,1,n,x,z);
	}
	
	return 0;
}
