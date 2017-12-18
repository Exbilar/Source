#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: map;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const LL mod = 1000000007;
static const int maxm = 5e6 + 10;

template <class T> inline bool chkmax(T &x,T y){
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in){
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

LL prm[maxm],phi[maxm],P[maxm],sum[maxm];
bool npr[maxm];
LL cnt,lmt,N;

map<LL,LL> f;

LL add(LL x,LL y){
	x = (x + mod) % mod;
	y = (y + mod) % mod;
	x += y; if(x >= mod) x -= mod;
	return x;
}

LL minus(LL x,LL y){
	x = (x + mod) % mod;
	y = (y + mod) % mod;
	x -= y; if(x < 0) x += mod;
	return x;
}

LL mul(LL x,LL y){
	x = (x + mod) % mod;
	y = (y + mod) % mod;
	return (x * y) % mod;
}

LL fpm(LL x,LL k){
	LL res = 1;
	while(k){
		if(k & 1) res = mul(res,x);
		x = mul(x,x);
		k >>= 1;
	}
	return res;
}

LL inv6 = fpm(6,mod - 2);
LL inv2 = fpm(2,mod - 2);

void getPrime(LL N){
	phi[1] = 1;
	for(int i = 2;i <= N;i++){
		if(!npr[i]) prm[++cnt] = i,phi[i] = i - 1;
		for(int j = 1;j <= cnt && prm[j] * i <= N;j++){
			npr[prm[j] * i] = 1;
			if(i % prm[j] == 0){
				phi[prm[j] * i] = mul(phi[i],prm[j]);
				break;
			}
			phi[prm[j] * i] = mul(phi[i],prm[j] - 1);
		}
	}
	for(int i = 1;i <= N;i++) P[i] = add(P[i - 1],mul(mul(i,i),phi[i]));
}

LL calc(LL N){
	if(N <= lmt) return P[N];
	if(f[N]) return f[N];
	
	LL res = mul(N,add(N,1));
	res = mul(res,inv2);
	res = mul(res,res);
	
	for(LL l = 2,r = 0;l <= N;l = r + 1){
		r = N / (N / l);
		
		LL tmp1 = mul(r,add(r,1));
		tmp1 = mul(tmp1,add(mul(r,2),1));
		tmp1 = mul(tmp1,inv6);

		LL tmp2 = mul(l,minus(l,1));
		tmp2 = mul(tmp2,minus(mul(l,2),1));
		tmp2 = mul(tmp2,inv6);

		res = minus(res,mul(calc(N / l),minus(tmp1,tmp2)));
	}
	
	return f[N] = res;	
}

LL solve(LL N){
	LL res = 0;
	for(LL l = 1,r = 0;l <= N;l = r + 1){
		r = N / (N / l);
		LL tmp = mul(add(l,r),minus(add(r,1),l));
		tmp = mul(tmp,inv2);
		res = add(res,mul(tmp,calc(N / l)));
	}
	return res;
}

int main(){
	read(N);
	
	getPrime(lmt = pow(N,2 / (double) 3));
	
	printf("%lld\n",solve(N));
	
	return 0;
}
