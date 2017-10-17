#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int A[maxm],B[maxm],C[maxm];
int n;

int main(){

	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	for(int i = 1;i <= n - 1;i++) scanf("%d",&B[i]);
	for(int i = 1;i <= n - 2;i++) scanf("%d",&C[i]);

	std :: sort(A + 1,A + n + 1);
	std :: sort(B + 1,B + n - 1 + 1);
	std :: sort(C + 1,C + n - 2 + 1);

	for(int i = 1;i <= n;i++){
		if(A[i] != B[i]){
			printf("%d\n",A[i]);
			break;
		}
	}

	for(int i = 1;i <= n - 1;i++){
		if(B[i] != C[i]){
			printf("%d\n",B[i]);
			break;
		}
	}
	
	return 0;
}
