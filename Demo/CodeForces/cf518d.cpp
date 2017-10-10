#include <cstdio>
#include <algorithm>

static const int maxm = 2e3 + 10;
static const int INF = 1 << 30;

double f[maxm][maxm];
int n,t;
double p;

int main(){
	scanf("%d%lf%d",&n,&p,&t);
	
	f[0][0] = 1;
	for(int i = 1;i <= t;i++){
		for(int j = 0;j <= n;j++){
			if(j == n) f[i][j] = f[i - 1][j];
			else f[i][j] = (1 - p) * f[i - 1][j];
			if(j) f[i][j] += p * f[i - 1][j - 1];
		}
	}

	double ans = 0;
	for(int i = 1;i <= n;i++) ans += f[t][i] * i;

	printf("%.7lf\n",ans);
	
	return 0;
}
