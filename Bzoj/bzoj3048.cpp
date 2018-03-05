#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int A[maxm],Q[maxm],cnt[maxm];
int n,k,x,pos=1,head=1,tail=1,tot,kind,ans;

map<int,int>M;

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		if(!M[x])M[x]=++tot;
		A[i]=M[x];
	}
	
	while(pos<=n){
		while(head<=tail&&kind<=k&&pos<=n){
			if(!cnt[A[pos]])kind++;
			cnt[A[pos]]++;
			ans=max(ans,cnt[A[pos]]);
			Q[tail++]=A[pos++];
		}
		while(head<=tail&&kind==k+1&&pos<=n){
			if(!cnt[A[pos]])break;
			cnt[A[pos]]++;
			ans=max(ans,cnt[A[pos]]);
			Q[tail++]=A[pos++];
		}
		if(!--cnt[Q[head++]])kind--;
	}
	
	printf("%d\n",ans);

	return 0;
}
