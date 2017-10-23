#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;
static const int MOD=1000000009;

long long tr[maxm],A[maxm],sum[maxm],C[maxm];
int n;
long long ans;

int lowbit(int x){
	return x&-x;
}

void Add(int k,int val){
	for(int i=k;i<=n;i+=lowbit(i))
		tr[i]+=val;
}

long long Query(int k){
	long long ret=0;
	for(int i=k;i;i-=lowbit(i))ret+=tr[i];
	return ret;
}

int hsh(int x){
	return lower_bound(C+1,C+n+1,x)-C;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&A[i]),sum[i]=sum[i-1]+A[i],C[i]=sum[i];
	sort(C+1,C+n+1);
	Add(hsh(0),1);
	for(int i=1;i<=n;i++)
		ans=Query(hsh(sum[i]))%MOD,Add(hsh(sum[i]),ans);
	
	printf("%lld\n",ans);

	return 0;
}
