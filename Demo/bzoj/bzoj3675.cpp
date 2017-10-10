#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

static const int maxm=1e6+10;

LL Q[maxm],f[maxm][2],sum[maxm],A[maxm];
int n,m;

LL sqr(LL x){
	return x*x;
}

long long get_up(int x,int y,int k){
	return f[x][k]-f[y][k]+sqr(sum[y])-sqr(sum[x]);
}
long long get_down(int x,int y){
	return sum[y]-sum[x];
}

double slp(int x,int y,int k){
	return (double) get_up(x,y,k)/get_down(x,y);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&A[i]),sum[i]=sum[i-1]+A[i];
	
	int cur=1;
	for(int j=1;j<=m;j++){
        cur^=1;int head=0,tail=0;Q[head]=0;
        for(int i=1;i<=n;i++){
            while(head<tail&&get_up(Q[head],Q[head+1],cur^1)<=get_down(Q[head],Q[head+1])*sum[i])head++;
            f[i][cur]=f[Q[head]][cur^1]+sum[Q[head]]*(sum[i]-sum[Q[head]]);
            while(head<tail&&get_up(Q[tail-1],Q[tail],cur^1)*get_down(Q[tail],i)>=get_up(Q[tail],i,cur^1)*get_down(Q[tail-1],Q[tail]))tail--;
            Q[++tail]=i;
        }
    }
    
	printf("%lld\n",f[n][cur]);
	
	return 0;
}
