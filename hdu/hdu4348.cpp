#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 3e6 + 10;

int lc[maxm],rc[maxm],rt[maxm],tag[maxm],A[maxm];
char opt[10];
LL sum[maxm];
int sz,n,m;

void pushup(int x){
	sum[x] = sum[lc[x]] + sum[rc[x]];
}

void build(int &x,int l,int r){
	x = ++sz;
	if(l == r) return sum[x] = A[l],void();
	int mid = (l + r) >> 1;
	build(lc[x],l,mid);
	build(rc[x],mid + 1,r);
	pushup(x);
}

void Upt(int &x,int lst,int l,int r,int L,int R,int val){
	x = ++sz,lc[x] = lc[lst],rc[x] = rc[lst],tag[x] = tag[lst];
	sum[x] = sum[lst] + (std :: min(r,R) - std :: max(l,L) + 1) * val;
	int mid = (l + r) >> 1;
	if(l >= L && r <= R) return tag[x] += val,void();
	if(L <= mid) Upt(lc[x],lc[lst],l,mid,L,R,val);
	if(R > mid) Upt(rc[x],rc[lst],mid + 1,r,L,R,val);
}

LL Qry(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return sum[x];
	int mid = (l + r) >> 1;
	LL ret = (std :: min(r,R) - std :: max(l,L) + 1) * tag[x];
	if(L <= mid) ret += Qry(lc[x],l,mid,L,R);
	if(R > mid) ret += Qry(rc[x],mid + 1,r,L,R);
	return ret;
}

int main(){
	
	int l,r,v,t,ver;
	while(scanf("%d%d",&n,&m) != EOF){
		sz = 0,ver = 0;
		for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
		build(rt[0],1,n);
		while(m--){
			scanf("%s",opt);
			if(opt[0] == 'Q')
				scanf("%d%d",&l,&r),printf("%lld\n",Qry(rt[ver],1,n,l,r));
			if(opt[0] == 'C')
				scanf("%d%d%d",&l,&r,&v),Upt(rt[ver + 1],rt[ver],1,n,l,r,v),ver++;
			if(opt[0] == 'H')
				scanf("%d%d%d",&l,&r,&t),printf("%lld\n",Qry(rt[t],1,n,l,r));
			if(opt[0] == 'B')
				scanf("%d",&ver);
		}
	}



	return 0;
}
