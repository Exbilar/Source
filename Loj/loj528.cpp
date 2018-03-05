

#include <cmath>
#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 4e6 + 10;
static const int MOD = 998244353;
static const int INF = 1 << 30;

LL mu[maxm],prm[maxm],npr[maxm];
LL sum[maxm];
int cnt;

void getPrime(LL n){
	mu[1] = 1;
	for(int i = 2;i <= n;i++){
		if(!npr[i]) prm[++cnt] = i,mu[i] = -1;
		for(int j = 1;j <= cnt && i * prm[j] <= n;j++){
			npr[i * prm[j]] = 1;
			if(i % prm[j] == 0){
				mu[i * prm[j]] = 0;
				break;
			}
			else mu[i * prm[j]] = -mu[i];
		}
	}
	for(int i = 1;i <= n;i++) mu[i] += mu[i - 1];
}

LL calc(LL n,LL m){
	LL res = 0;
	for(LL i = 1,nxt = 0;i <= n;i = nxt + 1){
		nxt = std :: min(n / (n / i),m / (m / i));
		LL tmp1 = (((n / i) % MOD) * ((m / i) % MOD)) % MOD;
		LL tmp2 = mu[(LL) sqrt(nxt)] - mu[(LL) sqrt(i - 1)];
		res = ((res + tmp1 * tmp2 % MOD) % MOD) % MOD;
	}
	return res + MOD;
}

int main(){
	LL n,m;
	scanf("%lld%lld",&n,&m);

	if(n > m) std :: swap(n,m);
	
	getPrime(sqrt(n) + 1);
	
	printf("%lld\n",calc(n,m) % MOD);
	
	return 0;
}
