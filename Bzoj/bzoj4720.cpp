#include <cstdio>
#include <cstring>
#include <algorithm>

using std :: max;
using std :: min;

static const int maxm = 3e2 + 10;
static const int maxn = 2e3 + 10;
static const int INF  = 1<<29;

int dis[maxm][maxm],c[maxn],d[maxn];
double k[maxn],f[maxn][maxn][2];
int n,m,v,e,x,y,z;
double ans = (double) 1e30;

void floyd(){
    for(int i = 1;i <= v;i++)dis[i][i] = 0;
    for(int k = 1;k <= v;k++)
	for(int i = 1;i <= v;i++)
	    for(int j = 1;j <= v;j++)
		if(i != k && i != j)
		    dis[i][j] = min(dis[i][j],dis[i][k] + dis[k][j]);
}

int main(){
    scanf("%d%d%d%d",&n,&m,&v,&e);
    for(int i = 1;i <= n;i++)scanf("%d",&c[i]);
    for(int i = 1;i <= n;i++)scanf("%d",&d[i]);
    for(int i = 1;i <= n;i++)scanf("%lf",&k[i]);

    for(int i = 1;i <= v;i++)
	for(int j = 1;j <= v;j++)
	    dis[i][j]=INF;
    
    for(int i = 1;i <= e;i++){
	scanf("%d%d%d",&x,&y,&z);
	dis[x][y] = min(dis[x][y],z);
	dis[y][x] = min(dis[y][x],z);
    }
    
    floyd();

    for(int i = 1;i <= n;i++)
	for(int j = 0;j <= m;j++)
	    f[i][j][1]=f[i][j][0] = 1e30;
    
    f[1][0][0] = 0; f[1][1][1] = 0;
    
    for(int i = 2;i <= n;i++){
	int lim = min(i,m);
	double minl;
	for(int j = 0;j <= lim;j++){
	    f[i][j][0] = min(f[i][j][0],f[i - 1][j][0] + dis[c[i - 1]][c[i]]);
	    f[i][j][0] = min(f[i][j][0],f[i - 1][j][1] + dis[c[i - 1]][c[i]] * (1.0 - k[i - 1]) + dis[d[i - 1]][c[i]] * k[i - 1]);
	    if(j>=1)f[i][j][1] = min(f[i][j][1],f[i - 1][j - 1][0] + dis[c[i - 1]][d[i]] * k[i] + dis[c[i - 1]][c[i]] * (1.0 - k[i]));
	      if(j>=1)f[i][j][1] = min(f[i][j][1],f[i - 1][j - 1][1] + dis[c[i - 1]][c[i]] * (1.0 - k[i -1]) * (1.0 - k[i]) + dis[c[i -1]][d[i]] * (1.0 - k[i-1]) * k[i] + dis[d[i - 1]][c[i]] * k[i - 1] * (1.0 - k[i]) + dis[d[i - 1]][d[i]] * k[i-1] * k[i]);
	}
    }

    for(int i = 0;i <= m;i++)
	ans=min(ans,f[n][i][0]),ans=min(ans,f[n][i][1]);

    printf("%.2lf\n",ans);
    
    return 0;
}
