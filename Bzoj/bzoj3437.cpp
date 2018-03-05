#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm=1e6+10;

LL Q[maxm],T[maxm],A[maxm],f[maxm],B[maxm],sum[maxm];
int n,head=1,tail=1;

double slp(int k,int j){
	return (double) (f[k]+T[k]-f[j]-T[j])/(sum[k]-sum[j]);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
	for(int i=1;i<=n;i++)
		scanf("%lld",&B[i]),sum[i]=sum[i-1]+B[i],T[i]=T[i-1]+i*B[i];
	
	for(int i=1;i<=n;i++){
		while(head<tail&&slp(Q[head],Q[head+1])<=i)head++;
		f[i]=f[Q[head]]+(sum[i]-sum[Q[head]])*i-(T[i]-T[Q[head]])+A[i];
		while(head<tail&&slp(i,Q[tail])<=slp(Q[tail],Q[tail-1]))tail--;
		Q[++tail]=i;
	}
	
	printf("%lld\n",f[n]);
	
	return 0;
}
