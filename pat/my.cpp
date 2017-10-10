#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 3e6 + 10;
static const int INF = 1 << 30;
static const int MOD = 20170927;

int n,m;

struct BIT{
	LL tr[maxm];
	
	int lowbit(int x){
		return x & -x;
	}

	void Upt(int k,LL v){
		for(int i = k;i <= n;i += lowbit(i)) tr[i] = (tr[i] + v) % MOD;
	}

	LL Qry(int k){
		LL res = 0;
		for(int i = k;i;i -= lowbit(i)) res = (res + tr[i]) % MOD;
		return res;
	}

}xy,xi,yi;

LL dx[maxm],dy[maxm];

LL sqr(LL x){
	return (x * x) % MOD;
}

int main(){
	
	LL x,y,opt,l,r,p;
	
	scanf("%d%d",&n,&m);

	for(int i = 1;i <= n;i++){
		scanf("%lld%lld",&dx[i],&dy[i]);
		xi.Upt(i,sqr(dx[i]));
		yi.Upt(i,sqr(dy[i]));
		xy.Upt(i,(dx[i] * dy[i]) % MOD);
	}

	while(m--){
		scanf("%lld",&opt);
		if(opt == 1){
			scanf("%lld%lld%lld",&p,&x,&y);
			xi.Upt(p,-sqr(dx[p]));
			yi.Upt(p,-sqr(dy[p]));
			xy.Upt(p,-((dx[p] * dy[p]) % MOD));
			dx[p] = x,dy[p] = y;
			xi.Upt(p,sqr(dx[p]));
			yi.Upt(p,sqr(dy[p]));
			xy.Upt(p,((dx[p] * dy[p]) % MOD));
		}
		if(opt == 2){
			scanf("%lld%lld",&l,&r);
			if(l == r){
				puts("0");
			}
			else{
				LL xi2 = (xi.Qry(r) - xi.Qry(l - 1) + MOD) % MOD;
				LL yi2 = (yi.Qry(r) - yi.Qry(l - 1) + MOD) % MOD;
				LL xy2 = (xy.Qry(r) - xy.Qry(l - 1) + MOD) % MOD;
				LL ans = ((xi2 * yi2) % MOD - sqr(xy2) + MOD) % MOD;
				printf("%lld\n",ans);
			}
		}
	}
	
	return 0;
}
