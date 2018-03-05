#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e3 + 10;
static const int MOD = 19650827;

int f[maxm][maxm][2],A[maxm];
int n;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	
	for(int i = 1;i <= n;i++) f[i][i][0] = 1;
	
	for(int i = n;i >= 1;i--){
		for(int j = i + 1;j <= n;j++){
			if(A[i] < A[j]) f[i][j][0] += f[i + 1][j][1];
			if(A[i] < A[i + 1]) f[i][j][0] += f[i + 1][j][0];
			if(A[j] > A[j - 1]) f[i][j][1] += f[i][j - 1][1];
			if(A[j] > A[i]) f[i][j][1] += f[i][j-1][0]; 
			f[i][j][1] %= MOD , f[i][j][0] %= MOD;
		}
	}
	
	printf("%d\n",(f[1][n][0] + f[1][n][1]) % MOD);
	
	return 0;
}
