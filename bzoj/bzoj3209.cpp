#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 2e3 + 10;
static const int MOD = 10000007;

LL C[maxm][maxm],num[maxm];
LL ans = 1,n,len;

LL pow(LL x,LL k){
	LL ret = 1;
	x %= MOD;
	while(k){
		if(k & 1) ret = (ret * x) % MOD;
		x = (x * x) % MOD;
		k >>= 1; 
	}
	return ret;
}

void init(){
	for(int i = 0;i <= 60;i++)C[i][0] = 1;
	for(int i = 0;i <= 60;i++)
		for(int j = 1;j <= i;j++)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
}

LL get(LL x){
	LL ret = 0;
	for(LL i = len;i >= 1;i--){
		if(num[i]) ret += C[i - 1][x] , x--;
		if(x < 0) break;
	}
	return ret;
}

int main(){
	init();
	scanf("%lld",&n);n++;
	while(n){
		num[++len] = n & 1;
		n >>= 1;
	}
	
	for(int i = 1;i <= len;i++)
		ans = (ans * pow(i,get(i))) % MOD;
	
	printf("%lld\n",ans);
	
	return 0;
}
