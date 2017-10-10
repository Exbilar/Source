#include <cstdio>
#include <algorithm>
using namespace std;

#define id first
#define val second

typedef long long LL;
typedef pair<int,LL> pil;

static const int maxm=1e6+10;
static const LL INF=1LL<<62;

int A[maxm];
LL f[maxm];
pil Q[maxm];
int n,k,head=1,tail=1;
LL ans,Min=INF;

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),ans+=A[i];
	
	for(int i=1;i<=n;i++){
		f[i]=Q[head].val+A[i];
		while(head<=tail&&Q[tail].val>=f[i])tail--;
		Q[++tail].val=f[i];Q[tail].id=i;
		while(head<=tail&&Q[head].id<i-k)head++;
	}
	
	for(int i=n-k;i<=n;i++)Min=min(Min,f[i]);
	
	printf("%lld\n",ans-Min);
	
	return 0;
}
