#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

static const int maxm=15+1;
static const int MOD=1e9+7;

LL f[maxm][maxm][maxm][maxm][maxm][maxm];
int cnt[maxm];
int n,x;

LL dfs(int a,int b,int c,int d,int e,int last){
    LL ret=0;
    if(!(a+b+c+d+e))return f[a][b][c][d][e][last]=1;
    if(f[a][b][c][d][e][last])return f[a][b][c][d][e][last];
    if(a)ret+=(a-(last==2))*dfs(a-1,b,c,d,e,1),ret%=MOD;
    if(b)ret+=(b-(last==3))*dfs(a+1,b-1,c,d,e,2),ret%=MOD;
    if(c)ret+=(c-(last==4))*dfs(a,b+1,c-1,d,e,3),ret%=MOD;
    if(d)ret+=(d-(last==5))*dfs(a,b,c+1,d-1,e,4),ret%=MOD;
    if(e)ret+=e*dfs(a,b,c,d+1,e-1,5),ret%=MOD;
    return f[a][b][c][d][e][last]=ret;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
	scanf("%d",&x),cnt[x]++;

    printf("%lld\n",dfs(cnt[1],cnt[2],cnt[3],cnt[4],cnt[5],0));
    return 0;
}
