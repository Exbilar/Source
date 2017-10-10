#include <cstdio>

typedef long long LL;

LL P;
int T;

LL getphi(LL x){
	LL ret = x;
	for(int i = 2;i * i <= x;i++){
		if(x % i) continue;
		ret = ret / i * (i - 1);
		while(x % i == 0) x /= i;
	}
	if(x != 1) ret = ret / x * (x - 1);
	return ret;
}

LL pow(LL x,LL n,LL MOD){
	LL ret = 1;
	while(n){
		if(n & 1) ret = (ret * x) % MOD;
		x = (x * x) % MOD;
		n >>= 1;
	}
	return ret % MOD;
}

LL f(int P){
	if(P == 1) return 0;
	LL phi = getphi(P);
	return pow(2,f(phi) + phi,P);
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&P);
		printf("%lld\n",f(P));
	}

	return 0;
}
