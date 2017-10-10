#include <cstdio>
#include <algorithm>

static const int maxm = 2e6 + 10;

int f[maxm],A[maxm];
int n;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	
	std :: sort(A + 1,A + n + 1);
	
	for(int i = 1;i <= n;i++)
		f[i] = std :: max(f[i - 1],A[i] - f[i - 1]);
	
	printf("%d\n",f[n]);
	
	return 0;
}
