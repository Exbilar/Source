#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 4e3 + 10;
static const int MOD = 1e9 + 7;

LL f[maxm][maxm],C[maxm][maxm],eq[maxm];
int n;
LL ans;

int main(){
	scanf("%d",&n);

	f[0][0] = 1;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= i;j++)
			f[i][j] = (f[i - 1][j - 1] + j * f[i - 1][j]) % MOD,
	
	C[0][0] = 1;
	for(int i = 1;i <= n;i++){
		C[i][0] = 1;
		for(int j = 1;j <= i;j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
	}
	
	for(int i = 0;i <= n;i++)
		for(int j = 0;j <= i;j++)
			eq[i] = (eq[i] + f[i][j]) % MOD;

	for(int i = 0;i < n;i++) ans = (ans + C[n][i] * eq[i]) % MOD;
	
	printf("%I64d\n",ans);

	return 0;
}
