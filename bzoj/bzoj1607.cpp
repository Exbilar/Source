#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int cnt[maxm],A[maxm],ans[maxm];
int MAX,n;

int main(){
    scanf("%d",&n);

    for(int i=1;i<=n;i++)scanf("%d",&A[i]),cnt[A[i]]++,MAX=max(MAX,A[i]);

    for(int i=1;i<=MAX;i++)
	if(cnt[i])
	    for(int j=i;j<=MAX;j+=i)
		ans[j]+=cnt[i];

    for(int i=1;i<=n;i++)
	printf("%d\n",ans[A[i]]-1);
    
    return 0;
}
