#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

static const int maxm=10000001;
static const int maxx=10000000+50;

bool npr[maxx];
int rev[maxx+10],fac[maxx+10],ans[maxx+10],pr[maxx+10];
int p,cnt;

void solve(){
    fac[1]=1;rev[1]=1;ans[1]=1;npr[1]=1;npr[0]=1;
    for(int i=2;i<=maxm;i++){  
        if(!npr[i])pr[++cnt]=(LL)i;  
        for(int j=1;j<=cnt&&pr[j]*i<=maxm;j++){  
            npr[pr[j]*(LL)i]=1;  
            if((LL)i%pr[j]==0)break;  
        }  
    }  
    for(int i=2;i<=maxm;i++){
	fac[i]=((LL)fac[i-1]*i)%p;
	if(i<p)rev[i]=(LL)(p-p/i)*rev[p%i]%p;
	if(!npr[i])ans[i]=(LL)ans[i-1]*(i-1)%p*rev[i%p]%p;
	else ans[i]=ans[i-1]; 
    }
}

int main(){
    int n,m,T;
    scanf("%d%d",&T,&p);
    solve();
    while(T--){
	scanf("%d%d",&n,&m);
	printf("%lld\n",(LL)fac[n]*ans[m]%p);
    }
    
    return 0;
}
