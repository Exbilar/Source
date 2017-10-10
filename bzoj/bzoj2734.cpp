#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e5 + 10;
static const int maxn = 20 + 10;
static const int MOD = 1000000001;

int f[maxn][maxm],lmt[maxm],mtx[maxn][maxn],vis[maxm],bin[maxm];
int n;
LL ans = 1;

int dp(int x){
	
	for(int i = 1;i <= 18;i++)lmt[i] = 0;
	
	mtx[1][1] = x;
	
	for(int i = 2 ;i <= 18;i++)
		if(mtx[i - 1][1] * 2 <= n)mtx[i][1] = mtx[i - 1][1] * 2;
		else mtx[i][1] = n + 1;
	
	for(int i = 1 ;i <= 18 ;i++)
		for(int j = 2;j <= 11 ;j++)
			if(mtx[i][j - 1] * 3 <= n)mtx[i][j] = mtx[i][j - 1] * 3;
			else mtx[i][j] = n + 1;
	
	for(int i = 1;i <= 18;i++)
		for(int j = 1;j <= 11;j++)
			if(mtx[i][j] <= n) lmt[i] += bin[j-1] , vis[mtx[i][j]] = 1;
	
	for(int i = 0;i <= 18;i++)
		for(int j = 0;j <= lmt[i];j++)
			f[i][j] = 0;
	f[0][0] = 1;
	
	for(int i = 0;i <= 18;i++)
		for(int j = 0;j <= lmt[i];j++)
			if(f[i][j])
				for(int k = 0;k <= lmt[i + 1];k++)
					if(!(j & k) && (!(k & (k << 1))))
						f[i + 1][k] = (f[i + 1][k] + f[i][j]) % MOD;
	return f[18][0];
}

int main(){
	scanf("%d",&n);
	
	bin[0] = 1;
	for(int i = 1;i <= n;i++)bin[i] = bin[i-1] << 1;
	
	for(int i = 1;i <= n;i++)
		if(!vis[i]) ans = (ans * dp(i)) % MOD;
	
	printf("%lld\n",ans);
	
	return 0;
}
