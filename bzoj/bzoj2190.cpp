#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

static const int maxm=1e6+10;

bool npr[maxm];
LL phi[maxm],f[maxm],prm[maxm];
LL n,ans,cnt;

void shake(LL n){
    npr[0]=npr[1]=1;
    for(int i=2;i<=n;i++){
	if(!npr[i])prm[++cnt]=i;
	for(int j=i+i;j<=n;j+=i)npr[j]=1;
    }
    
    phi[1]=1;
    for(int i=2;i<=n;i++){
	if(!phi[i]){
	    for(int j=i;j<=n;j+=i){
		if(!phi[j])phi[j]=j;
		phi[j]=phi[j]/i*(i-1);
	    }
	}
    }

    for(int i=1;i<n;i++)ans+=(phi[i]<<1);
    ans++;
}

int main(){
    scanf("%lld",&n);
    shake(n);
    printf("%lld\n",ans);
    return 0;
}
