#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

static const int maxm=2e4+10;
static const int maxn=2e2+10;
static const int INF=~(1<<31);

int f[maxn][maxn],node[maxm];
int Q,n,m,S,x,y,z,ans,dis;
LL tot;

int main(){
	
    memset(f,127/3,sizeof f);

    scanf("%d%d%d%d",&n,&m,&S,&Q);
    for(int i=1;i<=m;i++)
	scanf("%d%d%d",&x,&y,&z),
	    f[x][y]=z;
		
    for(int i=1;i<=n;i++)f[i][i]=0;
	
    for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=n;j++)
		f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	
    while(Q--){
	dis=INF;
	scanf("%d%d",&x,&y);
	for(int i=1;i<=S;i++)
	    dis=min(dis,f[x][i]+f[i][y]);
	if(dis<f[0][0])ans++,tot+=dis;
    }
	
    printf("%d\n%lld\n",ans,tot);
	
    return 0;
}
