#include <cstdio>

typedef long long LL;

int n;
LL ans,cur,last;

int main(){
    scanf("%d",&n);

    for(int i=1;i<=n;i++){
	scanf("%lld",&cur);
	if(cur-last>0)ans+=cur-last;
	last=cur;
    }

    printf("%lld\n",ans);
    
    return 0;
}
