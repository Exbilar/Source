#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

static const int maxm=5;
static const int size=1e6+10;

int D[maxm],C[maxm];
LL f[size];
int T,tot;
LL ans;

void dfs(int x,int k,int sum){
	if(sum<0)return;
	if(x==5){
		if(k&1)ans-=f[sum];
		else ans+=f[sum];
		return;
	}
	dfs(x+1,k,sum);
	dfs(x+1,k+1,sum-(D[x]+1)*C[x]);
}

int main(){
	for(int i=1;i<=4;i++)scanf("%d",&C[i]);
	scanf("%d",&T);
	
	f[0]=1;
	for(int i=1;i<=4;i++)
		for(int v=C[i];v<=100000;v++)
			f[v]+=f[v-C[i]];
	
	while(T--){
		for(int i=1;i<=4;i++)scanf("%d",&D[i]);
		scanf("%d",&tot);ans=0;
		dfs(1,0,tot);
		printf("%lld\n",ans);
	}
	
	
	return 0;
}
