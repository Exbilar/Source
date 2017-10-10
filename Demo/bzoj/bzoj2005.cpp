#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm=1e6+10;

LL f[maxm],g[maxm];
int n,m;
LL ans;

int main(){
	scanf("%d%d",&n,&m);
	if(n>m)std::swap(n,m);
	
	for(int i=1;i<=n;i++)f[i]=1LL*(n/i)*(m/i),g[i]=(i<<1)-1;
	
	for(int i=n;i>=1;i--)
		for(int j=i+i;j<=n;j+=i)
			f[i]-=f[j];
			
	for(int i=1;i<=n;i++)ans+=f[i]*g[i];
	
	printf("%lld\n",ans);
	return 0;
}
