#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;
static const int MOD = 1e9 + 7;

LL x[maxm],y[maxm],z[maxm];
LL A,B,C,n;

LL fpm(LL x,LL k){
	LL res = 1;
	while(k){
		if(k & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		k >>= 1;
	}
	return res;
}

int main(){
	
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++){
		scanf("%lld%lld%lld",&A,&B,&C);
		x[i] = A - B;
		y[i] = B - C;
		z[i] = C - A;
	}

	std :: sort(x + 1,x + n + 1);
	std :: sort(y + 1,y + n + 1);
	std :: sort(z + 1,z + n + 1);

	LL ans = 0;
	
	for(int i = 1;i <= n;i++){
		ans = (ans + (1LL * 2 * i - n - 1) * (x[i] + y[i] + z[i])) % MOD;
	}

	printf("%lld\n",ans * fpm(2,MOD - 2) % MOD);

	return 0;
}
