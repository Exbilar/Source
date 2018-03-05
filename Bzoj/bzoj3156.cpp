#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm=1e6+10;

LL Q[maxm],A[maxm],f[maxm];
int n,head=1,tail=1;

LL sqr(LL x){
	return x*x;
}

LL get_up(int i,int j){
	return (f[i]+((sqr(i)+i)/2))-(f[j]+((sqr(j)+j)/2));
}

LL get_down(int i,int j){
	return (i-j);
}

double slp(int x,int y){ 
    return (double) get_up(x,y)/get_down(x,y);  
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
	
	for(int i=1;i<=n;i++){
		while(head<tail&&slp(Q[head+1],Q[head])<=i)head++;
		f[i]=f[Q[head]]+A[i]+((i-Q[head])*(i-Q[head]-1))/2;
		while(head<tail&&slp(i,Q[tail])<=slp(Q[tail],Q[tail-1]))tail--;
		Q[++tail]=i;
	}
	
	printf("%lld\n",f[n]);
	
	return 0;
}
