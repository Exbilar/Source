#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int tr[maxm],A[maxm],B[maxm],f[maxm],cnt[maxm],pos[maxm][5+1];
int n,ans;

int lowbit(int x){
	return x&-x;
}

void Add(int k,int val){
	for(int i=k;i<=n;i+=lowbit(i))
		tr[i]=max(tr[i],val);
}

int Query(int k){
	int ret=0;
	for(int i=k;i;i-=lowbit(i))
		ret=max(ret,tr[i]);
	return ret;
}

int main(){
	scanf("%d",&n);n*=5;
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),pos[A[i]][++cnt[A[i]]]=i;
	for(int i=1;i<=n;i++)scanf("%d",&B[i]);
	
	for(int i=1;i<=n;i++){
		for(int j=5;j;j--){
			int now=pos[B[i]][j];
			f[now]=max(f[now],Query(now-1)+1);
			Add(now,f[now]);
			ans=max(ans,f[now]);
		}
	}
	
	printf("%d\n",ans);

	return 0;
}
