#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

static const int maxm=1e5+10;

LL A[maxm];
int n;

struct BIT{
	LL tr[maxm];
	BIT(){memset(tr,0,sizeof tr);}
	
	int lowbit(int x){
		return x&-x;
	}	
	
	void Add(int k,LL val){
		for(int i=k;i<=n;i+=lowbit(i))
			tr[i]+=val;
	}
	
	LL Query(int k){
		LL ret=0;
		for(int i=k;i;i-=lowbit(i))ret+=tr[i];
		return ret;
	}
	
};

int main(){

	while(scanf("%d",&n)!=EOF){
		memset(A,0,sizeof A);
		BIT sum,cnt;
		LL S=0,ans=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&A[i]);
			sum.Add(A[i],A[i]);
			cnt.Add(A[i],1);
			S+=A[i];
			ans+=(i-cnt.Query(A[i]))*A[i];
			ans+=S-sum.Query(A[i]);
		}
		printf("%lld\n",ans);
	}

	return 0;
}
