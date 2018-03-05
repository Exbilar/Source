#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e3 + 10;
static const int INF = 1 << 30;

int f[maxm][maxm],A[maxm];
int n,m;

void DP(){
	f[0][0] = 1;
	for(int i = 1;i <= 10;i++){
		for(int j = 0;j <= 9;j++){
			for(int k = 0;k <= 9;k++){
				if(j != 4 && !(j == 6 && k == 2)){
					f[i][j] += f[i - 1][k];
				}
			}
		}
	}
}

int solve(int x){
	int	len = 0,res = 0;
	while(x){
		A[++len] = x % 10;
		x /= 10;
	}
	A[len + 1] = 0;

	for(int i = len;i >= 1;i--){
		for(int j = 0;j < A[i];j++){
			if(A[i + 1] != 6 || j != 2) res += f[i][j];
		}
		if(A[i] == 4 || (A[i + 1] == 6 && A[i] == 2)) break;
	}
	
	return res;
}

int main(){

	DP();
	
	while(scanf("%d%d",&n,&m) == 2 && (n || m)){
		printf("%d\n",solve(m + 1) - solve(n));
	}
	
	return 0;
}
