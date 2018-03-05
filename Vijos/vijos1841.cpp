#include <cstdio>
#include <algorithm>

typedef long long LL;

int n,m,x,k;

LL fpm(LL x,LL k){
	LL res = 1;
	while(k){
		if(k & 1) res = (res * x) % n;
		x = (x * x) % n;
		k >>= 1;
	}
	return res;
}

int main(){
	scanf("%d%d%d%d",&n,&m,&k,&x);
	
	LL ans = (x + (1LL * fpm(10,(LL)k) * m) % n) % n;

	printf("%lld\n",ans);

	return 0;
}
