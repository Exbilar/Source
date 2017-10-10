#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int sum[maxm],f[maxm];
int n,x;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
	scanf("%d",&x),sum[i]=sum[i-1]+x,f[i]=sum[i]>=0?1:0;
        
    for(int i=1;i<=n;i++){
	for(int j=1;j<i;j++){
	    if(f[j]&&sum[i]-sum[j]>=0)f[i]=max(f[i],f[j]+1);
	}
    }
    if(!f[n])return puts("Impossible"),0;
    printf("%d\n",f[n]);

    return 0;
}
