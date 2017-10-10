#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int MOD = 20170927;

LL dx[maxm],dy[maxm];
LL n,m,opt,l,r,p,x,y;

LL sqr(LL x){
	return x * x % MOD;
}

LL calc(int i,int j){
	return sqr(dx[i] * dy[j]) + sqr(dx[j] * dy[i]) -
		(2 * dx[i] * dx[j] % MOD * dy[i] % MOD * dy[j] % MOD) % MOD;
}

int main(){
	scanf("%lld%lld",&n,&m);

	for(int i = 1;i <= n;i++){
		scanf("%lld%lld",&dx[i],&dy[i]);
	}

	for(int i = 1;i <= m;i++){
		scanf("%lld",&opt);
		if(opt == 1){
			scanf("%lld%lld%lld",&p,&x,&y);
			dx[p] = x,dy[p] = y;
		}
		if(opt == 2){
			scanf("%lld%lld",&l,&r);
			LL ans = 0;
			for(int i = l;i <= r;i++){
				for(int j = i + 1;j <= r;j++){
					ans = (ans + calc(i,j)) % MOD;
				}
			}
			printf("%lld\n",ans);
		}
	}
	
	return 0;
}
