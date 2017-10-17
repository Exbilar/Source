#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;
static const int MOD = 1e9 + 7;

LL f[maxm],p[maxm];
int n;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%I64d",&p[i]);
	for(int i = 2;i <= n + 1;i++){
		f[i] = ((2 * f[i - 1]) % MOD - f[p[i - 1]] + 2) % MOD;
		f[i] = (f[i] + MOD) % MOD;
	}
	
	printf("%I64d\n",f[n + 1]);
	
	return 0;
}
