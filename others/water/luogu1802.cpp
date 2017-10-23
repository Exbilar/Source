#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

static const int maxm=1e3+10;

LL f[maxm],ls[maxm],wn[maxm],w[maxm];
int n,m;

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%lld%lld%lld",&ls[i],&wn[i],&w[i]);

    for(int i=1;i<=n;i++){
	for(int v=m;v>=0;v--){
	    if(v>=w[i])
		f[v]=max(f[v]+ls[i],f[v-w[i]]+wn[i]);
	    else f[v]=f[v]+ls[i];
	}
    }

    printf("%lld\n",f[m]*5);

    return 0;
}
