#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int A[maxm],B[maxm];
int n,x,y;
long long ans;

int main(){
    scanf("%d%d%d",&n,&x,&y);
    for(int i=1;i<=n;i++)scanf("%d%d",&A[i],&B[i]);

    sort(A+1,A+n+1);
    sort(B+1,B+n+1);

    for(int i=1;i<=n;i++){
	if(A[i]<B[i])ans+=x*(B[i]-A[i]);
	else ans+=y*(A[i]-B[i]);
    }
    
    printf("%lld\n",ans);
    
    return 0;
}
