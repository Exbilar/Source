#include <cstdio>
#include <cstring>
#include <algorithm>

using std :: memset;
using std :: max;
using std :: min;

typedef long long LL;

static const int maxm=1e6+10;

LL A[maxm],sum[maxm],Q[maxm],f[maxm],s[maxm];
int n,l,head=1,tail=1;

LL sqr(LL x){
	return x*x;
}

LL get_up(int i){
	return (f[i]+sqr(s[i])+2*l*s[i]);
}

LL get_down(int k,int j){
	return 2*(s[k]-s[j]);
}

double slp(int k,int j){
	return (double) (get_up(k)-get_up(j))/get_down(k,j);
}

int main(){
	scanf("%d%d",&n,&l); l++;
	for(int i=1;i<=n;i++)
		scanf("%lld",&A[i]),sum[i]=sum[i-1]+A[i],s[i]=sum[i]+i;
	
	for(int i=1;i<=n;i++){
		while(head<tail&&slp(Q[head+1],Q[head])<=s[i])head++;
		f[i]=f[Q[head]]+sqr(s[i]-s[Q[head]]-l);
		while(head<tail&&slp(i,Q[tail])<=slp(Q[tail],Q[tail-1]))tail--;
		Q[++tail]=i;
	}
	
	printf("%lld\n",f[n]);

	return 0;
}
