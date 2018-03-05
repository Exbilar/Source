#include <cstdio>
#include <algorithm>

using std :: min;

typedef long long LL;

static const LL maxm = 2e6 + 10;

LL sum[maxm],aux[maxm],phi[maxm],A[maxm];
LL n,m,P,c,cnt;

LL getphi(LL x){
	LL ret = x;
	for(LL i = 2;i * i <= x;i++){
		if(x % i) continue;
		ret = ret / i * (i - 1);
		while(x % i == 0) x /= i;
	}
	if(x != 1) ret = ret / x * (x - 1);
	return ret;
}

void init(){
	phi[0] = P;
	while(P != 1){
		phi[++cnt] = getphi(P);
		P = phi[cnt];
	}
	phi[++cnt] = 1;
}

LL pow(LL x,LL k,LL mod){
	LL ret = 1;
	while(k){
		if(k & 1) ret = (ret * x) % mod;
		x = (x * x) % mod;
		k >>= 1;
	}
	return ret % mod;
}

LL calc(LL dpt,LL k){
	LL ret = k;
	if(ret >= phi[dpt]) ret = ret % phi[dpt] + phi[dpt];
	for(LL i = dpt;i > 0;i--){
		ret = pow(c,ret,phi[i - 1]);
		if(!ret) ret += phi[i - 1];
	}
	return ret % phi[0];
}

void pushup(LL x){
	LL lc = x << 1,rc = x << 1 | 1;
	sum[x] = (sum[lc] + sum[rc]) % phi[0];
	aux[x] = min(aux[lc],aux[rc]);
}

void build(LL x,LL l,LL r){
	if(l == r) return sum[x] = A[l] % phi[0],void();
	LL mid = (l + r) >> 1;
	build(x << 1,l,mid);
	build(x << 1 | 1,mid + 1,r);
	pushup(x);
}

LL Qry(LL x,LL l,LL r,LL L,LL R){
	if(l >= L && r <= R) return sum[x] % phi[0];
	LL mid = (l + r) >> 1,ret = 0;
	if(L <= mid) ret += Qry(x << 1,l,mid,L,R);
	if(R > mid) ret += Qry(x << 1 | 1,mid + 1,r,L,R);
	return ret % phi[0];
}

void modify(LL x,LL l,LL r,LL L,LL R){
	if(aux[x] >= cnt) return;
	if(l == r){
		aux[x]++;
		sum[x] = calc(aux[x],A[l]);
		return;
	}
	LL mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1,l,mid,L,R);
	if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R);
	pushup(x);
}

int main(){
	scanf("%lld%lld%lld%lld",&n,&m,&P,&c);
	for(LL i = 1;i <= n;i++) scanf("%lld",&A[i]);

	init();
	build(1,1,n);

	LL l,r,opt;

	while(m--){
		scanf("%lld%lld%lld",&opt,&l,&r);
		if(opt == 0) modify(1,1,n,l,r);
		if(opt == 1) printf("%lld\n",Qry(1,1,n,l,r));
	}
	
	return 0;
}
