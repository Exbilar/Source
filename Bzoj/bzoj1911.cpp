#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

static const int maxm=1e6+10;

LL Q[maxm],A[maxm],f[maxm],sum[maxm];
LL a,b,c;
int n,head=1,tail=1;

template<class T>
T sqr(T x){
	return x*x;
}

LL get_up(int i){
	return f[i]+a*sqr(sum[i])-b*sum[i];
}

LL get_down(int j,int k){
	return (a<<1)*(sum[j]-sum[k]);
}

double slp(int k,int j){
	return (double)(get_up(j)-get_up(k))/get_down(j,k);
}

LL calc(LL x){
	return a*sqr(x)+b*x+c;
}

int main(){
	scanf("%d%lld%lld%lld",&n,&a,&b,&c);
	for(int i=1;i<=n;i++)
		scanf("%lld",&A[i]),sum[i]=sum[i-1]+A[i];
	
	for(int i=1;i<=n;i++){
		while(head<tail&&slp(Q[head+1],Q[head])<=sum[i])head++;
		f[i]=f[Q[head]]+calc(sum[i]-sum[Q[head]]);
		while(head<tail&&slp(i,Q[tail])<=slp(Q[tail],Q[tail-1]))tail--;
		Q[++tail]=i;
	}
	
	printf("%lld\n",f[n]);
	
	return 0;
}
