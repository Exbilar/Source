#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int A[maxm];
int n,t,c,lst,ans;

int main(){
	scanf("%d%d%d",&n,&t,&c);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);

	for(int i = 1;i <= n;i++){
		if(A[i] > t){
			if(i - 1 - lst >= c) ans += i - 1 - lst - c + 1;
			lst = i;
		}
	}

	
	if(lst != n && n - lst >= c) ans += n - lst - c + 1;
	
	printf("%d\n",ans);
	
	return 0;
}
