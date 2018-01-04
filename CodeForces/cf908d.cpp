#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 2e3 + 10;
static const int mod = 1e9 + 7;

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

LL f[maxm][maxm];
int Pa,Pb,K;

LL fpm(LL x,LL k){
	LL res = 1;
	while(k){
		if(k & 1) res = res * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return res;
}

LL inv(LL x){
	return fpm(x,mod - 2);
}

LL add(LL x,LL y){
	x %= mod,y %= mod;
	x += y; if(x >= mod) x -= mod;
	return x;
}

LL mul(LL x,LL y){
	x = (x + mod) % mod;
	y = (y + mod) % mod;
	return (x * y) % mod;
}

LL getProb(LL x){
	return mul(x,inv(add(Pa,Pb)));
}

LL getDP(LL n,LL m){
	if(n + m >= K) return add(add(n,m),mul(Pa,inv(Pb)));
	if(f[n][m]) return f[n][m];
	return f[n][m] = add(mul(getDP(n + 1,m),getProb(Pa)),mul(getDP(n,n + m),getProb(Pb)));
}

int main(){
	read(K),read(Pa),read(Pb);

	printf("%lld\n",getDP(1,0));
	
	return 0;
}
