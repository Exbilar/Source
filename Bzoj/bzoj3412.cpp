#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int t[maxm],b[maxm],s[maxm];

int main(){
    int n,q,ask,ans;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)scanf("%d",&b[i]);

    for(int i=1;i<=n;i++)s[i]=s[i-1]+b[i];
    
    while(q--){
	scanf("%d",&ask);
	ans=upper_bound(s+1,s+n+1,ask)-s;
	printf("%d\n",ans);
    }

    return 0;
}
