#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 3e3 + 10;
static const int INF = 1 << 30;
static const int MOD = 1e9 + 7;

LL f[maxm][maxm][2];
LL ans,n,m;

int main(){
	
	scanf("%lld%lld",&n,&m);
	
	f[0][0][1] = 1;
	for(int i = 1;i <= n;i++) f[0][i][0] = 1;

	if(n == 1){
		LL ans = 2;
		for(int i = 1;i <= m;i++) ans = ans * 2 % MOD;
		return printf("%lld\n",ans),0;
	}
	
	for(int i = 1;i <= m;i++){
		f[i][0][1] = (f[i - 1][0][1] + f[i - 1][1][0] + f[i - 1][1][1]) % MOD;
		f[i][1][0] = (f[i - 1][1][0] + f[i - 1][2][0]) % MOD;
		f[i][1][1] = (f[i - 1][0][1] + f[i - 1][1][0] +
					  2LL * f[i - 1][1][1] + f[i - 1][2][1]) % MOD;
		f[i][n][0] = (f[i - 1][n - 1][0] + f[i - 1][n][0]) % MOD;
		f[i][n][1] = (f[i - 1][n - 1][1] + f[i - 1][n][1]) % MOD;
		for(int j = 2;j < n;j++){
			f[i][j][0] = (f[i - 1][j - 1][0] + 2LL * f[i - 1][j][0] +
						  f[i - 1][j + 1][0]) % MOD;
			f[i][j][1] = (f[i - 1][j - 1][1] + 2LL * f[i - 1][j][1] +
						  f[i - 1][j + 1][1]) % MOD;
		}
	}
	
	for(int i = 0;i <= n;i++) ans = (ans + f[m][i][1]) % MOD;
	
	printf("%lld\n",ans);
	
	return 0;
}
