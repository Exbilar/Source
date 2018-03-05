#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 2e6 + 10;
static const int INF = 1 << 29;

int pos[maxm],A[maxm],v[maxm];
LL f[maxm],tr[maxm];
int n,m,p;
LL ans;

void pushup(int x){
	int lc = x << 1,rc = x << 1 | 1;
	if(A[pos[lc]] < A[pos[rc]]) pos[x] = pos[lc];
	else pos[x] = pos[rc];
}

void build(int x,int l,int r){
	if(l == r) return pos[x] = l,void();
	int mid = (l + r) >> 1;
	build(x << 1,l,mid);
	build(x << 1 | 1,mid + 1,r);
	pushup(x);
}

void modify(int x,int l,int r,int pos){
	if(l == r) return A[l] = INF,void();
	int mid = (l + r) >> 1;
	if(pos <= mid) modify(x << 1,l,mid,pos);
	else modify(x << 1 | 1,mid + 1,r,pos);
	pushup(x);
}

int Qry(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return pos[x];
	int mid = (l + r) >> 1,ret1 = 0,ret2 = 0;
	if(L <= mid) ret1 = Qry(x << 1,l,mid,L,R);
	if(R > mid) ret2 = Qry(x << 1 | 1,mid + 1,r,L,R);
	if(ret1 * ret2 == 0) return ret1 ^ ret2;
	return A[ret1] < A[ret2] ? ret1 : ret2;
}

int lowbit(int x){
	return x & -x;
}

void Upt(int k,int val){
	for(int i = k;i <= n;i += lowbit(i))
		tr[i] += val;
}

int Query(int k){
	int ret = 0;
	for(int i = k;i;i -= lowbit(i))
		ret += tr[i];
	return ret;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),v[i] = A[i];
	std :: sort(v + 1,v + n + 1);
	int tot = std :: unique(v + 1,v + n + 1) - v - 1;
	for(int i = 1;i <= n;i++)
		A[i] = std :: lower_bound(v + 1,v + n + 1,A[i]) - v;

	for(int i = n;i;i--)
		f[i] = Query(A[i] - 1),Upt(A[i],1),ans += f[i];

	build(1,1,n);
	printf("%lld\n",ans);

	while(m--){
		scanf("%d",&p);
		while(A[p] != INF){
			int pos = Qry(1,1,n,p,n);
			ans -= f[pos],f[pos] = 0;
			modify(1,1,n,pos);
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}
