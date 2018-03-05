#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

static const int maxm = 1e7 + 10;

int A[maxm],npr[maxm],pr[maxm],phi[maxm];
LL sum[maxm];
LL ans;
int cnt,n;

void shake(int n){
	phi[1] = 1;
	for(int i = 2;i <= n;i++){
		if(!npr[i]) phi[i] = i - 1,pr[++cnt] = i;
		for(int j = 1;j <= cnt && i * pr[j] <= n;j++){
			npr[pr[j] * i] = 1;
			if(i % pr[j] == 0){phi[i * pr[j]] = phi[i] * pr[j];break;}
			else phi[i * pr[j]] = phi[i] * phi[pr[j]];
		}
	}
}

int main(){			
	scanf("%d",&n);
	shake(n);

	for(int i = 1;i <= n;i++)
		sum[i] = sum[i - 1] + phi[i];

	for(int i = 1;i <= cnt;i++)
		ans += sum[n / pr[i]] * 2 - 1;

	printf("%lld\n",ans);
	
    return 0;
}
