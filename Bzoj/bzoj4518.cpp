#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

static const int maxm=1e6+10;

LL Q[maxm],f[maxm][2],A[maxm],sum[maxm];
int n,m,head=1,tail=1;

LL sqr(LL x){
	return x*x;
}

double slp(int i,int j,int k){
	return (double) (f[i][k]+sqr(sum[i])-f[j][k]-sqr(sum[j]))/(sum[i]-sum[j]);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&A[i]),sum[i]=sum[i-1]+A[i];
	memset(f,63,sizeof f);f[0][0]=0;int cur=0;
	
	for(int j=1;j<=m;j++){
		cur^=1,head=1,tail=1;
		for(int i=1;i<=n;i++){
			while(head<tail&&slp(Q[head+1],Q[head],cur^1)<=(sum[i]<<1))head++;
			f[i][cur]=f[Q[head]][cur^1]+sqr(sum[i]-sum[Q[head]]);
			while(head<tail&&slp(i,Q[tail],cur^1)<=slp(Q[tail],Q[tail-1],cur^1))tail--;
			Q[++tail]=i;
		}
	}
	
	printf("%lld\n",m*f[n][cur]-sqr(sum[n]));
	
	return 0;
}
