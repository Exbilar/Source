#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

char str[maxm];
int num[maxm];
int n,k;

int main(){
	scanf("%d%d",&n,&k);
	scanf("%s",str + 1);

	for(int i = 1;i <= n;i++) num[str[i] - 'a']++;

	for(int i = 0;i < 26;i++)
		if(num[i] > k) return puts("NO"),0;

	puts("YES");

	return 0;
}
