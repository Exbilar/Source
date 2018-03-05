#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 2e2 + 10;

LL fib[maxm];
int t,f;
LL n;

int main(){
	scanf("%d",&t);
	fib[1] = 1,fib[2] = 1;
	for(int i = 3;i <= 45;i++) fib[i] = fib[i - 1] + fib[i - 2];

	while(t--){
		f = 0;
		scanf("%lld",&n);
		for(int i = 0;i <= 45;i++)
			for(int j = i;j <= 45;j++)
				if(fib[i] * fib[j] == n) f = 1;
		if(f) puts("TAK");
		else puts("NIE");
	}

	return 0;
}
