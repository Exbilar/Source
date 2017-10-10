#include <cstdio>
#include <cmath>
#include <algorithm>

typedef long long LL;

LL n,ans;

LL phi(LL x){
	LL ret = x;
	for(int i = 2;i * i <= x;i++){
		if(x % i) continue;
		ret = ret / i * (i - 1);
		while(x % i == 0) x /= i;
	}
	if(x != 1) ret = ret / x * (x - 1);
	return ret;
}

int main(){
	scanf("%lld",&n);
	int m = sqrt(n);
	for(int i = 1;i <= m;i++){
		if(n % i) continue;
		ans += 1LL * phi(n / i) * i;
		if(i * i < n) ans += 1LL * phi(i) * (n / i);
	}

	printf("%lld\n",ans);
	
	return 0;
}
