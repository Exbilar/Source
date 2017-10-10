#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int sum[maxm],gcd[maxm],A[maxm];
int n,m;

void pushup(int x){
	int lc = x << 1,rc = x << 1 | 1;
	gcd[x] = std :: __gcd(gcd[lc],gcd[rc]);
	sum[x] = 0;
	if(gcd[lc] == gcd[x]) sum[x] += sum[lc];
	if(gcd[rc] == gcd[x]) sum[x] += sum[rc];
}

void build(int x,int l,int r){
	if(l == r) return sum[x] = 1,gcd[x] = A[l],void();
	int mid = (l + r) >> 1;
	build(x << 1,l,mid);
	build(x << 1 | 1,mid + 1,r);
	pushup(x);
}

int Qry_gcd(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return gcd[x];
	int mid = (l + r) >> 1,res = 0;
	if(L <= mid) res = std :: __gcd(res,Qry_gcd(x << 1,l,mid,L,R));
	if(R > mid) res = std :: __gcd(res,Qry_gcd(x << 1 | 1,mid + 1,r,L,R));
	return res;
}

int Qry(int x,int l,int r,int L,int R,int G){
	if(l >= L && r <= R) return sum[x] * (gcd[x] == G);
	int mid = (l + r) >> 1,res = 0;
	if(L <= mid) res += Qry(x << 1,l,mid,L,R,G);
	if(R > mid) res += Qry(x << 1 | 1,mid + 1,r,L,R,G);
	return res;
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	build(1,1,n);
	
	scanf("%d",&m);
	
	while(m--){
		int l,r;
		scanf("%d%d",&l,&r);
		int G = Qry_gcd(1,1,n,l,r);
		printf("%d\n",r - l + 1 - Qry(1,1,n,l,r,G));
	}

	return 0;
}
