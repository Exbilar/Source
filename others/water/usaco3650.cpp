#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;
static const int INF=~(1<<31);

int A[maxm];
int n,sum,maxd,ans=INF,mind=INF;

int sqr(int x){
    return x*x;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
	scanf("%d",&A[i]),maxd=max(maxd,A[i]);

    for(int h=0;h<=maxd;h++){
	sum=0;
	for(int i=1;i<=n;i++){
	    if(A[i]<h&&h-A[i]>17)sum+=sqr(h-A[i]-17);
	    if(A[i]>h)sum+=sqr(A[i]-h);
	}
	ans=min(ans,sum);
    }
    
    printf("%d\n",ans);

    return 0;
}
