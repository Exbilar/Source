#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 30;
static const int mod = 1e9 + 7;

LL f[maxm];
LL ans,s;
int n;

LL fpm(LL x,LL k){
	LL res = 1;
	while(k){
		if(k & 1) res = (res * x) % mod;
		x = (x * x) % mod;
		k >>= 1;
	}
	return res;
}

LL C(LL n,LL m){
	if(n < m) return 0;
	if(m > n - m) m = n - m;
	
	LL up = 1,down = 1;
	for(LL i = 0;i < m;i++){
		up = up * (n - i) % mod;
		down = down * (i + 1) % mod;
	}
	return up * fpm(down,mod - 2) % mod;
}

LL lucas(LL n,LL m){
	if(!m) return 1;
	return lucas(n / mod,m / mod) * C(n % mod,m % mod) % mod;
}

void solve(){
	for(int i = 0;i < (1 << n);i++){
		LL sum = s; int sig = 1;
		for(int j = 0;j < n;j++){
			if(i & (1 << j)){
				sum -= (f[j + 1] + 1);
				sig *= -1;
			}
		}
		if(sum < 0) continue;
		ans = (ans + sig * lucas(sum + n - 1,n - 1)) % mod;
	}
	
	ans = (ans + mod) % mod;
}

int main(){
	scanf("%d%lld",&n,&s);
	for(int i = 1;i <= n;i++) scanf("%lld",&f[i]);
	
	solve();
	printf("%lld\n",ans);
	
	return 0;
}
