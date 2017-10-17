#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int mod = 1e9 + 7;

LL fac[maxm],A[maxm],tr[maxm],f[maxm];
int n;

int lowbit(int x){
	return x & -x;
}

void Upt(int k,LL v){
	for(int i = k;i <= n;i += lowbit(i)) tr[i] += v;
}

LL Qry(int k){
	LL res = 0;
	for(int i = k;i;i -= lowbit(i)) res += tr[i];
	return res;
}

void init(){
	fac[0] = 1;
	for(int i = 1;i <= n;i++) fac[i] = (fac[i - 1] * i) % mod;
	for(int i = 1;i <= n;i++) Upt(i,1);
	
	f[2] = 1; LL x = 1;
	for(int i = 3;i <= n;i++){
		x = (x * i) % mod;
		f[i] = x * ((1LL * i * (i - 1) / 2) % mod) % mod;
	}
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%lld",&A[i]);
	init();
	
	LL sum = 0,ans = 0;
	for(int i = 1;i <= n;i++){
		LL tmp = Qry(A[i] - 1);
		ans = (ans + fac[n - i] * ((tmp * (tmp - 1) / 2 % mod) % mod) % mod) % mod;
		ans = (ans + f[n - i] * tmp % mod) % mod;
		ans = (ans + fac[n - i] * (sum * tmp % mod) % mod) % mod;
		sum = (sum + tmp) % mod;
		Upt(A[i],-1);
	}
	
	ans = (ans + sum) % mod;
	
	printf("%lld\n",ans);
	
	return 0;
}
