#include <cstdio>
#include <algorithm>

static const int maxm = 2e2 + 10;
static const int INF = 1 << 30;

double f[maxm][maxm][maxm];
int x,y,z;

int main(){
	scanf("%d%d%d",&x,&y,&z); f[x][y][z] = 1.0;

	for(int i = x;i >= 1;i--){
		for(int j = y;j >= 1;j--){
			for(int k = z;k >= 1;k--){
				double sum = i * j + j * k + i * k;
				f[i - 1][j][k] += f[i][j][k] * i * k / sum;
				f[i][j - 1][k] += f[i][j][k] * i * j / sum;
				f[i][j][k - 1] += f[i][j][k] * j * k / sum;
			}
		}
	}
	
	double ans1 = 0,ans2 = 0,ans3 = 0;
	
	for(int i = 1;i <= 100;i++){
		for(int j = 0;j <= 100;j++){
			ans1 += f[i][j][0];
			ans2 += f[0][i][j];
			ans3 += f[j][0][i];
		}
	}
	
	printf("%.10lf %.10lf %.10lf\n",ans1,ans2,ans3);
	
	return 0;
}
