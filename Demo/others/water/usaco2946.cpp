#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=2e3+10;
static const int MOD=1e8;

int f[maxm][maxm],r[maxm];
int n,F;

int main(){
    scanf("%d%d",&n,&F);
    for(int i=1;i<=n;i++)scanf("%d",&r[i]);

    f[0][0]=1;
    
    for(int i=1;i<=n;i++){
	for(int v=0;v<=F;v++){
	    f[i][v]=(f[i][v]+f[i-1][v])%MOD;
	    f[i][v]=(f[i][v]+f[i-1][(v+r[i])%F])%MOD;
	}
    }

    printf("%d\n",f[n][F]);   
    
    return 0;
}
