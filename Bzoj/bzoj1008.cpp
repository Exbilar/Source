#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

static const int MOD = 100003;

typedef long long LL;

LL pow(LL x,LL n){
    x%=MOD;
    LL ret = 1;
    while(n){
	if(n&1) ret = (ret*x)%MOD;
	x = (x*x)%MOD;
	n >>= 1;
    }
    return (ret%MOD);
}

LL m,n;

int main(){
    scanf("%lld%lld",&m,&n);
    LL ans=pow(m%MOD,n)%MOD;
    ans=(ans-((m%MOD)*pow(m-1,n-1))%MOD)%MOD;
    ans=(ans+MOD)%MOD;
    printf("%lld\n",ans%MOD);

    return 0;
}
