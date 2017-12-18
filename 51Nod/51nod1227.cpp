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
static const int maxm = 4e6 + 10;

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

LL prm[maxm],phi[maxm],P[maxm];
bool npr[maxm];
LL cnt,lmt,L,R;

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
	for(int i = 1;i <= N;i++) P[i] = add(P[i - 1],mul(i,phi[i]));
}

LL calc(LL N){
	if(N <= lmt) return P[N];
	if(f[N]) return f[N];
		
	LL res = mul(N,add(N,1));
	res = mul(res,add(mul(N,2),1));
	res = mul(res,inv6);
	
	for(LL l = 2,r = 0;l <= N;l = r + 1){
		r = N / (N / l);
		
		LL tmp = mul(add(l,r),add(minus(r,l),1));
		tmp = mul(tmp,inv2);
		
		res = minus(res,mul(calc(N / l),tmp));
	}
	
	return f[N] = res;	
}

LL solve(LL N){
	LL res = 0;
	for(LL l = 1,r = 0;l <= N;l = r + 1){
		r = N / (N / l);
		LL tmp = add(minus(r,l),1);
		res = add(res,mul(tmp,calc(N / l)));
	}
	return add(res,N);
}

int main(){	
	read(L),read(R);
	
	getPrime(lmt = pow(R,2 / (double) 3));
	
	LL ansR = mul(solve(R),inv2);
	LL ansL = mul(solve(L - 1),inv2);

	printf("%lld\n",minus(ansR,ansL));
	
	return 0;
}
