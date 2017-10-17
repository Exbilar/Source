#include <bits/stdc++.h>

using std :: max;
using std :: min;
using std :: map;

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int A[maxm];
char str[maxm];

map<LL,LL> f[30];

LL ans,sum;

int main(){
	for(int i = 1;i <= 26;i++) scanf("%d",&A[i]);	
	scanf("%s",str + 1);
	int len = strlen(str + 1);
	
	for(int i = 1;i <= len;i++){
		int tmp = str[i] - 'a' + 1;
		ans += f[tmp][sum];
		sum += A[tmp];
		f[tmp][sum]++;
	}

	printf("%lld\n",ans);

	return 0;
}
