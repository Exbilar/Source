#include <cstdio>
#include <cstring>
#include <algorithm>

#define REP(i,s,t) for(int i = s;i <= t;i++)

typedef long long LL;

static const int maxm = 4e5 + 10;
static const int MOD = 1e9 + 7;

struct Matrix{
	LL mtx[5][5];
	
	Matrix(){memset(mtx,0,sizeof mtx);}
	
	void init(){
		REP(i,1,2) REP(j,1,2)
			mtx[i][j] = (i == j);
	}

	Matrix operator + (const Matrix &B) const {
		Matrix ret;
		REP(i,1,2) REP(j,1,2)
			ret.mtx[i][j] = (mtx[i][j] + B.mtx[i][j]) % MOD;
		return ret;
	}

	Matrix operator * (const Matrix &B) const {
		Matrix ret;
		REP(i,1,2) REP(j,1,2) REP(k,1,2)
			ret.mtx[i][j] = (ret.mtx[i][j] + mtx[i][k] * B.mtx[k][j]) % MOD;
		return ret;
	}
	
}tag[maxm],tr[maxm],get,st;

LL A[maxm];
int n,m,opt;

Matrix pow(Matrix A,LL n){
	if(!n) return A;
	Matrix ret = A;n--;
	while(n){
		if(n & 1) ret = ret * A;
		A = A * A;
		n >>= 1;
	}
	return ret;
}

void pushup(int x){
	tr[x] = tr[x << 1] + tr[x << 1 | 1];
}

void pushdown(int x){
	int lc = x << 1,rc = x << 1 | 1;
	tr[lc] = tr[lc] * tag[x];
	tr[rc] = tr[rc] * tag[x];
	tag[lc] = tag[lc] * tag[x];
	tag[rc] = tag[rc] * tag[x];
	tag[x].init();
}

void build(int x,int l,int r){
	tag[x].init();
	if(l == r)
		return tr[x] = (A[l] == 1 ? st : st * pow(get,A[l] - 1)),void();
	int mid = (l + r) >> 1;
	build(x << 1,l,mid);
	build(x << 1 | 1,mid + 1,r);
	pushup(x);
}

void modify(int x,int l,int r,int L,int R,Matrix val){
	if(l >= L && r <= R){
		tr[x] = tr[x] * val;
		tag[x] = tag[x] * val;
		return;
	}
	pushdown(x);
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1,l,mid,L,R,val);
	if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,val);
	pushup(x);
}

LL Qry(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return tr[x].mtx[1][1];
	pushdown(x);
	int mid = (l + r) >> 1;LL ret = 0;
	if(L <= mid) ret = (ret + Qry(x << 1,l,mid,L,R)) % MOD;
	if(R > mid) ret = (ret + Qry(x << 1 | 1,mid + 1,r,L,R)) % MOD;
	return ret;
}

int main(){
	get.mtx[1][1] = 0,get.mtx[1][2] = 1;
	get.mtx[2][1] = 1,get.mtx[2][2] = 1;
	st.mtx[1][1] = 1,st.mtx[1][2] = 1;
	
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%lld",&A[i]);
	build(1,1,n);

	LL v;int l,r;
	while(m--){
		scanf("%d",&opt);
		if(opt == 1)
			scanf("%d%d%lld",&l,&r,&v),modify(1,1,n,l,r,pow(get,v));
		if(opt == 2)
			scanf("%d%d",&l,&r),printf("%lld\n",Qry(1,1,n,l,r));
	}

	return 0;
}
