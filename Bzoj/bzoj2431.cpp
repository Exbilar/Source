#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e3+10;
static const int MOD=1e4;

int n,k;
int f[maxm][maxm],g[maxm][maxm];

int main(){
    scanf("%d%d",&n,&k);
    f[0][0]=1;
    for(int i=0;i<=k;i++)
	g[0][i]=1;
    for(int i=1;i<=n;i++){
	for(int j=0;j<=k;j++){
	    if(j>=i)f[i][j]=(g[i-1][j]-g[i-1][j-i]+MOD)%MOD;
	    else f[i][j]=g[i-1][j];
	    g[i][j]=(j?g[i][j-1]:0)+f[i][j];
	    g[i][j]%=MOD;
	}
    }

    printf("%d\n",f[n][k]);
    
    return 0;
}
