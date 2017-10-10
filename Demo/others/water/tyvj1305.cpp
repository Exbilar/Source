#include <cstdio>
#include <deque>
#include <algorithm>
using namespace std;

#define id first
#define val second

typedef pair<int,long> pil;
typedef long long LL;

static const int maxm=1e6+10;

deque<pil>Q;

LL A[maxm],sum[maxm];
int n,k;
LL ans;

int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%lld",&A[i]),sum[i]=sum[i-1]+A[i];	
	
    for(int i=1;i<=n;i++){
		while(!Q.empty()&&Q.back().val>=sum[i])Q.pop_back();
		Q.push_back(make_pair(i,sum[i]));
		while(!Q.empty()&&Q.front().id<i-k)Q.pop_front();
		if(i>1)ans=max(ans,sum[i]-Q.front().val);
		else ans=max(ans,sum[i]);
    }
	
    printf("%lld\n",ans);
	
    return 0;
}
