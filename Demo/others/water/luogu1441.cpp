#include <cstdio>
#include <cstring>
#include <algorithm>

using std :: max;
using std :: min;

static const int maxm = 1e4 + 10;

int A[maxm],f[maxm],vis[maxm];
int n,m,cnt,ans,M;

void calc(){
	int res = 0;
	for(int i = 0;i <= M;i++) f[i] = 0;
	f[0] = 1;
	
	for(int i = 1;i <= n;i++){
		if(vis[i]) continue;
		for(int v = M;v >= A[i];v--){
			f[v] += f[v - A[i]];
		}
	}
	
	for(int i = 1;i <= M;i++) if(f[i]) res++;
	
	ans = max(res,ans);
}

void dfs(int pos,int rmn){
	if(!rmn) return calc(),void();
	for(int i = pos;i <= n - rmn + 1;i++){
		vis[i] = 1;
		dfs(i + 1,rmn - 1);
		vis[i] = 0;
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),M += A[i];

	dfs(1,m);

	printf("%d\n",ans);
	
	return 0;
}
