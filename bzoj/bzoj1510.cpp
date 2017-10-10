#include <cstdio>
#include <algorithm>

static const int maxm = 2e6 + 10;

int A[maxm],d[maxm];
int n,m;

int solve(int l,int r,int w){
	int ret = 0;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(A[mid] >= w) ret = mid,l = mid + 1;
		else r = mid - 1;
	}
	return ret;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	for(int i = 1;i <= m;i++) scanf("%d",&d[i]);

	for(int i = 1;i < n;i++)
		if(A[i + 1] > A[i]) A[i + 1] = A[i];

	int l = 1,r = n;
	
	for(int i = 1;i <= m;i++) r = solve(l,r,d[i]) - 1;

	printf("%d\n",r + 1);
	
	return 0;
}
