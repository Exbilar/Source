#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using std :: min;
using std :: max;

static const int maxm = 9;
static const int INF = 1 << 29;

int f[maxm+7][maxm][maxm][maxm][maxm],d[maxm+7][maxm][maxm][maxm][maxm];
int sum[maxm][maxm],v[maxm][maxm];
int n;

template <class T>
T sqr(T x){
    return x*x;
}

int s(int x1,int y1,int x2,int y2){
    return sqr(sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1]);
}

int dfs(int k,int x1,int y1,int x2,int y2){
    if(f[k][x1][y1][x2][y2] != -1)return f[k][x1][y1][x2][y2];
    if(k == 1)return s(x1,y1,x2,y2);
    int ret = INF;
    for(int i = x1;i < x2;i++){
	ret = min(ret,dfs(k - 1,x1,y1,i,y2) + s(i + 1,y1,x2,y2));
	ret = min(ret,dfs(k - 1,i + 1,y1,x2,y2) + s(x1,y1,i,y2));
    }
    for(int i = y1;i< y2;i++){
	ret = min(ret,dfs(k - 1,x1,y1,x2,i) + s(x1,i + 1,x2,y2));
	ret = min(ret,dfs(k - 1,x1,i + 1,x2,y2) + s(x1,y1,x2,i));
    }
    return f[k][x1][y1][x2][y2] = ret;
}

int main(){
    
    while(scanf("%d",&n) != EOF){
	memset(v,0,sizeof v);
	memset(sum,0,sizeof sum);
	memset(f,-1,sizeof f);
	memset(d,-1,sizeof d);

	for(int i = 1;i <= 8;i++)
	    for(int j = 1;j <= 8;j++)
		scanf("%d",&v[i][j]);
	for(int i = 1;i <= 8;i++)
	    for(int j = 1; j<= 8;j++)
		sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + v[i][j];
	
	double avr = (double) sum[8][8] / n;
	double ans = (double) sqrt((double) dfs(n,1,1,8,8) / n - sqr(avr));
	printf("%.3lf\n",ans);
    }

    return 0;
}
