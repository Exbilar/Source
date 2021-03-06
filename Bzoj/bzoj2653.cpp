#include <cstdio>
#include <algorithm>

using std :: sort;
using std :: max;
using std :: min;

typedef long long LL;

static const int maxm = 200010;

int lc[maxm * 20],rc[maxm * 20],rt[maxm],A[maxm],q[10];
int lsum[maxm * 20],rsum[maxm * 20],sum[maxm * 20],id[maxm];
int sz,n,m,lstans;

bool cmp(int x,int y){
	return A[x] < A[y];
}

void pushup(int x){
	sum[x] = sum[lc[x]] + sum[rc[x]];
	lsum[x] = max(lsum[lc[x]],sum[lc[x]] + lsum[rc[x]]);
	rsum[x] = max(rsum[rc[x]],sum[rc[x]] + rsum[lc[x]]);
}

void build(int &x,int l,int r){
	x = ++sz;
	int mid = (l + r) >> 1;
	if(l == r) return sum[x] = lsum[x] = rsum[x] = 1,void();
	build(lc[x],l,mid);
	build(rc[x],mid + 1,r);
	pushup(x);
}

void insert(int &x,int lst,int l,int r,int pos,int val){
	x = ++sz,lc[x] = lc[lst],rc[x] = rc[lst];
	if(l == r) return sum[x] = lsum[x] = rsum[x] = val,void();
	int mid = (l + r) >> 1;
	if(pos <= mid) insert(lc[x],lc[lst],l,mid,pos,val);
	else insert(rc[x],rc[lst],mid + 1,r,pos,val);
	pushup(x);
}

int Qry_sum(int x,int l,int r,int L,int R){
	if(L > R) return 0;
	if(l == L && r == R) return sum[x];
	int mid = (l + r) >> 1;
	if(R <= mid) return Qry_sum(lc[x],l,mid,L,R);
	else if(L > mid) return Qry_sum(rc[x],mid + 1,r,L,R);
	else return Qry_sum(lc[x],l,mid,L,mid) + Qry_sum(rc[x],mid + 1,r,mid + 1,R);
}

int Qry_lsum(int x,int l,int r,int L,int R){
	if(L > R) return 0;
	if(l == L && r == R) return lsum[x];
	int mid = (l + r) >> 1;
	if(R <= mid) return Qry_lsum(lc[x],l,mid,L,R);
	else if(L > mid) return Qry_lsum(rc[x],mid + 1,r,L,R);
	else return max(Qry_lsum(lc[x],l,mid,L,mid),Qry_sum(lc[x],l,mid,L,mid) + Qry_lsum(rc[x],mid + 1,r,mid + 1,R));
}

int Qry_rsum(int x,int l,int r,int L,int R){
	if(L > R) return 0;
	if(l == L && r == R) return rsum[x];
	int mid = (l + r) >> 1;
	if(R <= mid) return Qry_rsum(lc[x],l,mid,L,R);
	else if(L > mid) return Qry_rsum(rc[x],mid + 1,r,L,R);
	else return max(Qry_rsum(rc[x],mid + 1,r,mid + 1,R),Qry_sum(rc[x],mid + 1,r,mid + 1,R) + Qry_rsum(lc[x],l,mid,L,mid));
}

bool chk(int x){
	int a = q[1],b = q[2],c = q[3],d = q[4];
	return Qry_sum(rt[x],1,n,b,c) + max(Qry_lsum(rt[x],1,n,c + 1,d),0) + max(Qry_rsum(rt[x],1,n,a,b - 1),0) >= 0;
}

int main(){
	
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),id[i] = i;
	sort(id + 1,id + n + 1,cmp);
	build(rt[1],1,n);
	for(int i = 2;i <= n;i++)
		insert(rt[i],rt[i - 1],1,n,id[i - 1],-1);

	scanf("%d",&m);

	while(m--){
		for(int i = 1;i <= 4;i++) scanf("%d",&q[i]);
		for(int i = 1;i <= 4;i++) q[i] = (q[i] + lstans) % n + 1;
		sort(q + 1,q + 4 + 1);
		int l = 1,r = n,ans = 0;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(chk(mid)) ans = mid,l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n",lstans = A[id[ans]]);
	}

	
	return 0;
}
