#include <cstdio>
#include <algorithm>
using namespace std;

#define REP(i,l,r) for(int i=l;i<=r;i++)

static const int maxm=5e3+10;

int sum[maxm][maxm];
int n,r,ans,x,y,v;

int main(){
    scanf("%d%d",&n,&r);
    for(int i=1;i<=n;i++)
	scanf("%d%d%d",&x,&y,&v),
	    x++,y++,sum[x][y]+=v;

    REP(i,1,5001)REP(j,1,5001) sum[i][j]+=sum[i][j-1];
    
    REP(i,1,5001)REP(j,1,5001) sum[i][j]+=sum[i-1][j];
 
    REP(i,r,5001)REP(j,r,5001)
	{int x=sum[i][j]-sum[i-r][j]-sum[i][j-r]+sum[i-r][j-r];ans=max(x,ans);}

    printf("%d\n",ans);
    
    return 0;
}
