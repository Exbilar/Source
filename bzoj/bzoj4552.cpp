#include <cstdio>
#include <algorithm>

using std :: max;
using std :: min;

static const int maxm = 1e5 + 10;

int tr[maxm << 2],A[maxm],tag[maxm << 2],d[maxm],Ql[maxm],Qr[maxm],Qf[maxm];
int n,m,pos;

void build(int x,int l,int r){
	tag[x] = -1;
	if(l == r) return tr[x] = A[l],void();
	int mid = (l + r) >> 1;
	build(x << 1,l,mid);
	build(x << 1 | 1,mid + 1,r);
	tr[x] = tr[x << 1] + tr[x << 1 | 1];
}

void pushdown(int x,int l,int r){
	int lc = x << 1,rc = x << 1 | 1;
	int mid = (l + r) >> 1;
	tr[lc] = tag[x] * (mid - l + 1),tr[rc] = tag[x] * (r - mid);
	tag[lc] = tag[x],tag[rc] = tag[x],tag[x] =  -1;
}

void modify(int x,int l,int r,int L,int R,int val){
	if(L > R) return;
	if(l >= L && r <= R) return tr[x] = (r - l + 1) * val,tag[x] = val,void();
	int mid = (l + r) >> 1;
	if(tag[x] != -1) pushdown(x,l,r);
	if(L <= mid) modify(x << 1,l,mid,L,R,val);
	if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,val);
	tr[x] = tr[x << 1] + tr[x << 1 | 1];
}

int Qry(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return tr[x];
	int mid = (l + r) >> 1,ret = 0;
	if(tag[x] != -1) pushdown(x,l,r);
	if(L <= mid) ret += Qry(x << 1,l,mid,L,R);
	if(R > mid) ret += Qry(x << 1 | 1,mid + 1,r,L,R);
	return ret;
}

bool chk(int x){
	for(int i = 1;i <= n;i++) A[i] = d[i] > x;
	build(1,1,n);
	for(int i = 1;i <= m;i++){
		int num = Qry(1,1,n,Ql[i],Qr[i]);
		if(Qf[i]){
			modify(1,1,n,Ql[i],Ql[i] + num - 1,1);
			modify(1,1,n,Ql[i] + num,Qr[i],0);
		}else{
			modify(1,1,n,Qr[i] - num + 1,Qr[i],1);
			modify(1,1,n,Ql[i],Qr[i] - num,0);
		}
	}
	return !Qry(1,1,n,pos,pos);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&d[i]);
	for(int i = 1;i <= m;i++) scanf("%d%d%d",&Qf[i],&Ql[i],&Qr[i]);
	scanf("%d",&pos);

	int l = 1,r = n,ans = 0;

	while(l <= r){
		int mid = (l + r) >> 1;
		if(chk(mid)) ans = mid,r = mid - 1;
		else l = mid + 1;
	}

	printf("%d\n",ans);
	
	return 0;
}
