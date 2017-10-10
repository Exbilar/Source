#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 5e6 + 10;

LL A[maxm],maxd[maxm];
LL n,sa,sb,sc,sd,mod,ans;

LL F(LL x){
	return x * x % mod * x % mod * sa % mod + x * x % mod * sb + x % mod * sc + sd % mod; 
}

int main(){
	scanf("%lld%lld%lld%lld%lld%lld%lld",&n,&sa,&sb,&sc,&sd,&A[1],&mod);
	for(int i = 2;i <= n;i++) A[i] = (F(A[i - 1]) % mod + F(A[i - 2]) % mod) % mod;
	for(int i = 1;i <= n;i++) maxd[i] = std :: max(maxd[i - 1],A[i]);
	for(int i = 1;i <= n;i++)
		if(maxd[i - 1] > A[i]) ans = std :: max(ans,(maxd[i - 1] - A[i] + 1) >> 1);
	
	printf("%lld\n",ans);
	
	return 0;
}
