#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;
static const int INF=0x3f3f3f3f;

int f[maxm];
int n,N,t1,t2,t3,ans=INF;

int main(){
	memset(f,INF,sizeof f);
	f[0]=0;
	
	scanf("%d",&n);N=n*5;
	
	while(n--){
		scanf("%d%d%d",&t1,&t2,&t3);
		for(int i=N;i>=0;i--){
			int tmp=INF;
			if(i>=t1&&t1)tmp=min(tmp,f[i-t1]);
			if(t2)tmp=min(tmp,f[i]+t2);
			if(i>=t3&&t3)tmp=min(tmp,f[i-t3]+t3);
			f[i]=tmp;
		}
	}
	
	for(int i=0;i<=N;i++)
		ans=min(ans,max(f[i],i));
	
	printf("%d\n",ans);
	
	return 0;
}
