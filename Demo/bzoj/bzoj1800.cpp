#include <cstdio>

typedef long long LL;

static const int maxm = 2e6 + 10;

int A[maxm];
int sum,n,tot,tmp,pos;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),sum += A[i];
	
	if(sum & 1) return puts("0"),0;
	
	sum >>= 1;

	for(int i = 1;i < n;i++){
		tmp += A[i];
		while(tmp > sum) tmp -= A[++pos];
		if(tmp == sum) tot++;
	}

	printf("%d\n",tot * (tot - 1) >> 1);
	
	return 0;
}
