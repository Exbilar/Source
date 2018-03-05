#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int A[maxm],pre[maxm],f[maxm],pos[maxm],cnt[maxm];
int n,m;

int main(){

	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	memset(pre,-1,sizeof pre);memset(f,127/3,sizeof f);
	int block=(int)sqrt(n);
	f[0]=0;
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=block;j++)
			if(pre[A[i]]<=pos[j])cnt[j]++;
		pre[A[i]]=i;
		for(int j=1;j<=block;j++){
			if(cnt[j]>j){
				int now=pos[j]+1;
				while(pre[A[now]]>now)now++;
				pos[j]=now;cnt[j]--;
			}
		}
		for(int j=1;j<=block;j++)
			f[i]=min(f[i],f[pos[j]]+j*j);
	}
	
	printf("%d\n",f[n]);
	
	return 0;
}
