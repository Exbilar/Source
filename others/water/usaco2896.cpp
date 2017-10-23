#include <cstdio>
#include<functional>
#include <cstring>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;
static const int INF=~(1<<31);

int A[maxm],f[maxm];
int n,ans=INF,maxd;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	
	
	
    /*	for(int i=1;i<=n;i++){
	f[i]=1;
	for(int j=1;j<i;j++)
	if(A[i]>=A[j])
	f[i]=max(f[j]+1,f[i]);    O(n^2)
	maxd=max(maxd,f[i]);
	}
	
	ans=min(ans,n-maxd);
	
	memset(f,0,sizeof f);maxd=0;
	
	for(int i=1;i<=n;i++){
	f[i]=1;
	for(int j=1;j<i;j++)
	if(A[i]<=A[j])
	f[i]=max(f[j]+1,f[i]);
	maxd=max(maxd,f[i]);
	}
	
	ans=min(ans,n-maxd);*/
	
    f[++maxd]=A[1];	
	
    for(int i=2;i<=n;i++){
	if(A[i]>=f[maxd])f[++maxd]=A[i];
	else {int pos=upper_bound(f+1,f+maxd+1,A[i])-f;f[pos]=A[i];}   //O(nlog2(n))
    }
	
    memset(f,0,sizeof f);
    maxd=0;f[++maxd]=A[1];
	
    ans=min(ans,n-maxd);
	
    for(int i=2;i<=n;i++){
	if(A[i]<=f[maxd])f[++maxd]=A[i];
	else {int pos=upper_bound(f+1,f+maxd+1,A[i],greater<int>())-f;f[pos]=A[i];}
    }
	
    ans=min(ans,n-maxd);
	
    printf("%d\n",ans);
	
    return 0;
}
