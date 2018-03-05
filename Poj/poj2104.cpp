#include <cstdio>
#include <algorithm>

static const int maxm = 4e6 + 10;

int lc[maxm],rc[maxm],size[maxm],rt[maxm],id[maxm],rnk[maxm],A[maxm];
int sz,n,m;

bool cmp(const int &x,const int &y){
	return A[x] < A[y];
}

void insert(int &x,int lst,int l,int r,int val){
	x = ++sz,lc[x] = lc[lst],rc[x] = rc[lst],size[x] = size[lst] + 1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(val <= mid) insert(lc[x],lc[lst],l,mid,val);
	else insert(rc[x],rc[lst],mid + 1,r,val);
}

int Qry(int x,int y,int l,int r,int rank){
	if(l == r) return l;
	int tmp = size[lc[y]] - size[lc[x]];
	int mid = (l + r) >> 1;
	if(rank <= tmp) return Qry(lc[x],lc[y],l,mid,rank);
	else return Qry(rc[x],rc[y],mid + 1,r,rank - tmp);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),id[i] = i;
	std :: sort(id + 1,id + n + 1,cmp);
	for(int i = 1;i <= n;i++) rnk[id[i]] = i;
	
	for(int i = 1;i <= n;i++) 
		insert(rt[i],rt[i - 1],1,n,rnk[i]);
	
	int l,r,k;
	while(m--){
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",A[id[Qry(rt[l - 1],rt[r],1,n,k)]]);
	}
	
	return 0;
}
