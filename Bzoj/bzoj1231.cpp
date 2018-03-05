#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm=16+1;

LL f[maxm][1<<maxm],A[maxm];
int n,m;
LL ans;

int main(){
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
	
	for(int i=1;i<=n;i++)f[i][1<<(i-1)]=1;
	
	for(int i=0;i<(1<<n);i++){
		for(int j=1;j<=n;j++){
			if(i&(1<<(j-1))){
				for(int k=1;k<=n;k++){
					if(!(i&(1<<(k-1)))&&std::abs(A[j]-A[k])>m){
						f[k][i|(1<<(k-1))]+=f[j][i];
					}
				}
			}
		}
	}
	
	for(int i=1;i<=n;i++)
		ans+=f[i][(1<<n)-1];
	
	printf("%lld\n",ans);
	
	return 0;
}
