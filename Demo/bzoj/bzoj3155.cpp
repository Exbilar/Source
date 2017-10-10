#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e5 + 10;

LL tr1[maxm],tr2[maxm],A[maxm],sum[maxm];
char ch[10];
int n,m,pos;

int lowbit(int x){
	return x&-x;
}

void Upt(int k,LL val){
	for(int i = k; i <= n ;i += lowbit(i))
		tr1[i] += val,tr2[i] += 1LL * k * val;
}

LL Query(int k){
	LL ret = 0;
	for(int i = k ; i ;i -= lowbit(i))
		ret += 1LL * (k+1) * tr1[i] - tr2[i];
	return ret;
}

int main(){
	LL x;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n ;i++)
		scanf("%lld",&A[i]),sum[i]=sum[i-1]+A[i];
	
	for(int i = 1;i <= n ;i++)
		Upt(i,sum[i]),Upt(i+1,-sum[i]);
	
	while(m--){
		scanf("%s",ch);	
		if(ch[0]=='M'){
			scanf("%d%lld",&pos,&x);
			Upt(pos,x-A[pos]);Upt(n+1,A[pos]-x);
			A[pos]=x;
		}else{
			scanf("%d",&pos);
			printf("%lld\n",Query(pos));
		}
	}

	return 0;
}
