#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm = 4e6 + 10;
static const int INF = ~(1 << 31);

struct segment{
	int l,r,len;
	bool operator < (const segment &seg) const {
		return len < seg.len;
	}
}A[maxm];

int tag[maxm],maxl[maxm],rnk[maxm];
int n,m,top,tot,ans = INF;

void pushup(int x){
	int lc = x << 1,rc = x << 1 | 1;
	maxl[x] = max(maxl[lc],maxl[rc]);
}

void pushdown(int x){
	int lc = x << 1,rc = x << 1 | 1;
	maxl[lc] += tag[x],maxl[rc] += tag[x];
	tag[lc] += tag[x],tag[rc] += tag[x],tag[x] = 0;
}

void modify(int x,int l,int r,int L,int R,int v){
	if(l >= L && r <= R) return tag[x] += v,maxl[x] += v,void();
	pushdown(x);
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1,l,mid,L,R,v);
	if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,v);
	pushup(x);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%d%d",&A[i].l,&A[i].r);
		A[i].len = A[i].r - A[i].l;
		rnk[++tot] = A[i].l,rnk[++tot] = A[i].r;
	}

	sort(rnk + 1,rnk + tot + 1);
	tot = unique(rnk + 1,rnk + tot + 1) - rnk - 1;

	for(int i = 1;i <= n;i++)
		A[i].l = lower_bound(rnk + 1,rnk + tot + 1,A[i].l) - rnk,
			A[i].r = lower_bound(rnk + 1,rnk + tot + 1,A[i].r) - rnk;
	
	sort(A + 1,A + n + 1);
	
	for(int i = 1;i <= n;i++){
		while(maxl[1] < m && top < n)
			top++,modify(1,1,tot,A[top].l,A[top].r,1);		
		if(maxl[1] == m) ans = min(ans,A[top].len - A[i].len);
		modify(1,1,tot,A[i].l,A[i].r,-1);
	}

	printf("%d\n",ans == INF ? -1 : ans);

	return 0;
}
