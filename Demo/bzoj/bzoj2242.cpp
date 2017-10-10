#include <map>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

LL x,y,p,m,z;
int t,opt;
map<LL,LL>mp;

LL pow(LL x,LL n,LL MOD){
    LL ret=1;
    while(n){
		if(n&1)ret=(ret*x)%MOD;
		x=(x*x)%MOD;
		n>>=1;
    }
    return ret;
}

int solve(LL y,LL z,LL p){
    int f = 0;
    if(!y&&!z)return puts("1"),0; 
    if(!y&& z!=0){puts("Orz, I cannot find x!");return 0;}
    mp.clear();
    LL tmp=0,m=sqrt(p);
    for(LL i=0;i<=m;i++){
        if(!i){tmp=z%p;mp[tmp]=i;continue;}
        tmp=(tmp*y)%p;
        mp[tmp]=i;
    }
    LL t=pow(y,m,p);
    tmp=1;
    for(LL i=1;i*i<=p;i++){
        tmp=(tmp*t)%p;
        if(mp[tmp]){
             LL ans=(i*m)-mp[tmp];
             printf("%lld\n",(ans%p+p)%p);
             f=1;
             break;
        }
    }
    if(!f)
        puts("Orz, I cannot find x!");
}

int main(){
	scanf("%d%d",&t,&opt);
	while(t--){
		scanf("%lld%lld%lld",&y,&z,&p);
		y%=p;
		if(opt==1)printf("%lld\n",pow(y,z,p));
		else if(opt==2){
			z%=p;
			if(!y&&z)puts("Orz, I cannot find x!");
			else printf("%lld\n",((z%p)*pow(y,p-2,p))%p);
		}
		else if(opt==3)solve(y,z,p);
	}

    return 0;
}   
