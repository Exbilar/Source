#include <cstdio>
#include <algorithm>

static const int maxm=1e2+10;

int f[maxm];
int in,n,now,ans;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&in); now=0;
		for(int j=0;j<=30;j++)
			if(in&(1<<j))now=std::max(now,f[j]);
		for(int j=0;j<=30;j++)
			if(in&(1<<j))f[j]=std::max(now+1,f[j]);
	}
	
	for(int i=1;i<=30;i++)ans=std::max(ans,f[i]);
	
	printf("%d\n",ans);
	
	return 0;
}
