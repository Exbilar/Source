#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int f[maxm][5][2],c[maxm][5];
int n,ans;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d%d%d",&c[i][1],&c[i][2],&c[i][3]);

    for(int i=2;i<=n;i++){
		f[i][1][1]=max(f[i-1][2][0],f[i-1][3][0])+c[i][1];
		f[i][2][1]=f[i-1][3][0]+c[i][2];
		f[i][2][0]=f[i-1][1][1]+c[i][2];
		f[i][3][0]=max(f[i-1][2][1],f[i-1][1][1])+c[i][3];
    }
	
    ans=max(ans,f[n][3][0]+c[1][1]);
    ans=max(ans,f[n][2][0]+c[1][1]);
    ans=max(ans,f[n][1][1]+c[1][2]);
    ans=max(ans,f[n][3][0]+c[1][2]);
    ans=max(ans,f[n][1][1]+c[1][3]);
    ans=max(ans,f[n][2][1]+c[1][3]);
	
    printf("%d\n",ans);
    
    return 0;
}
