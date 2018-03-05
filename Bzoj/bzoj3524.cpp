#include <cstdio>
#include <algorithm>

static const int maxm = (5e5 + 10) * 24; 

int lc[maxm],rc[maxm],size[maxm],rt[maxm],A[maxm];
int n,m,sz;

void insert(int &x,int lst,int l,int r,int val){
	x = ++sz,lc[x] = lc[lst],rc[x] = rc[lst],size[x] = size[lst] + 1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(val <= mid) insert(lc[x],lc[lst],l,mid,val);
	else insert(rc[x],rc[lst],mid + 1,r,val);
}

int Qry(int x,int y,int l,int r,int k){
	if(l == r) return l;
	int tmp1 = size[lc[y]] - size[lc[x]];
	int tmp2 = size[rc[y]] - size[rc[x]];
	int mid = (l + r) >> 1;
	if(tmp1 > k) return Qry(lc[x],lc[y],l,mid,k);
	if(tmp2 > k) return Qry(rc[x],rc[y],mid + 1,r,k);
	return 0;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	for(int i = 1;i <= n;i++) insert(rt[i],rt[i - 1],1,n,A[i]);
	
	int l,r;
	while(m--){
		scanf("%d%d",&l,&r);
		printf("%d\n",Qry(rt[l - 1],rt[r],1,n,(r - l + 1) >> 1));	
	}
	
	return 0;
}
