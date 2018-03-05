#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int A[maxm];
int B[maxm];
int n,m;

int main(){
    while(scanf("%d%d",&n,&m)==2&&n&&m){
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1;i<=m;i++)scanf("%d",&B[i]);
	int ans=0;int cur=1;
	sort(A+1,A+n+1);
	sort(B+1,B+m+1);
	for(int i=1;i<=m;i++){
	    if(B[i]>=A[cur]){
		ans+=B[i];
		if(++cur==n+1)break;
	    }
	}
	if(cur<=n) puts("Loowater is doomed!");
	else printf("%d\n",ans);
    }


    return 0;
}
