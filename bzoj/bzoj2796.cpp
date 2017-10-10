#include <cstdio>
#include <map>
#include <algorithm>

using std :: map;

typedef long long LL;

static const int maxm = 1e3 + 10;

LL f[maxm];
map<LL,LL> ans;

LL solve(LL x){
	if(ans[x]) return ans[x];
	int pos = std :: lower_bound(f + 1,f + 91 + 1,x) - f;
	if(f[pos] == x) return 1;
	return ans[x] = std :: min(solve(x - f[pos - 1]),solve(f[pos] - x)) + 1;
}

int main(){
	int T;LL x;
	scanf("%d",&T);

	f[1] = 1,f[2] = 1;
	for(int i = 3;i <= 91;i++) f[i] = f[i - 1] + f[i - 2];
	
	while(T--){
		scanf("%lld",&x);
		printf("%lld\n",solve(x));
	}


	return 0;
}
