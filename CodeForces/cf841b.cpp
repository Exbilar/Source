#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e6 + 10;

LL A[maxm];
int n;
LL sum;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%I64d",&A[i]); sum += A[i];
	}

	if(sum & 1) return puts("First"),0;

	for(int i = 1;i <= n;i++){
		if(A[i] & 1) return puts("First"),0;
	}

	puts("Second");
	
	return 0;
}
