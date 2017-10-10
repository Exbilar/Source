#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e6 + 10;

LL Q[maxm],f[maxm],sum[maxm],T[maxm],P[maxm],C[maxm],X[maxm];
int n,head=1,tail=1;

double slp(int k,int j){
	return (double) (f[k]+T[k]-f[j]-T[j])/(sum[k]-sum[j]);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&X[i],&P[i],&C[i]);
		sum[i]=sum[i-1]+P[i];
		T[i]=T[i-1]+X[i]*P[i];
	}
	
	for(int i=1;i<=n;i++){
		while(head<tail&&slp(Q[head+1],Q[head])<=X[i])head++;
		f[i]=f[Q[head]]+1LL*(sum[i]-sum[Q[head]])*X[i]-(T[i]-T[Q[head]])+C[i];
		while(head<tail&&slp(i,Q[tail])<=slp(Q[tail],Q[tail-1]))tail--;
		Q[++tail]=i;
	}
	
	printf("%lld\n",f[n]);
	
	return 0;
}
