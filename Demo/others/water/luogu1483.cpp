#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

static const int maxm=1e5+10;

LL A[maxm],B[maxm];
int n,m,opt,l,r,x;
LL k,d;

struct BIT{
    LL tr1[maxm],tr2[maxm];
    
    BIT(){std:: memset(tr1,0,sizeof tr1), memset(tr2,0,sizeof tr2);}
    
    int lowbit(int x){
        return x&-x;
    }
    
    void Upt(int k,LL val){
        for(int i = k;i <= n;i += lowbit(i))
            tr1[i] += val ,tr2[i] += (LL) k*val; 
    }
    
    LL Query(int k){
        LL ret = 0;
        for(int i = k; i ;i -= lowbit(i))
            ret += (LL) (k+1) * tr1[i] - tr2[i]; 
        return ret;
    }
    
}bit;

int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++)scanf("%lld",&A[i]),B[i]=A[i]-A[i-1];
    for(int i = 1;i <= n;i++)bit.Upt(i,B[i]),bit.Upt(i+1,-B[i]); 
    
    while(m--){
        scanf("%d",&opt);
        if(opt == 1){
            scanf("%d%d%lld%lld",&l,&r,&k,&d);
            bit.Upt(l,k);bit.Upt(l+1,-k);
            bit.Upt(r+1,-d);bit.Upt(l+1,d);
            bit.Upt(r+1,-(k+d*(r-l)));
            bit.Upt(r+2,(k+d*(r-l)));
            
        }else scanf("%d",&x),printf("%lld\n",bit.Query(x));
    }
    
    
    return 0;
}
