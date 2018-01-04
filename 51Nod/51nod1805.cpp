#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int mod = 1e9 + 7;
static const int maxm = 1e6 + 10;

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

LL n,m;
LL CC[maxm];

LL mul(LL x,LL y){
	x = (x + mod) % mod;
	y = (y + mod) % mod;
	return (x * y) % mod;
}

LL add(LL x,LL y){
	x += y; if(x >= mod) x -= mod;
	return x;
}

LL minus(LL x,LL y){
	x -= y; if(x < 0) x += mod;
	return x;
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

LL C(LL n,LL m){
	LL res = 1;
	for(int i = n - m + 1;i <= n;i++) res = mul(res,i);
	for(LL i = 1;i <= m;i++) res = mul(res,fpm(i,mod - 2));
	return res;
}

int main(){

	read(n),read(m);

	LL ans = 0;

	CC[0] = 1;
	for(int i = 1;i <= n - m;i++)
		CC[i] = mul(CC[i - 1],n - m - i + 1),CC[i] = mul(CC[i],fpm(i,mod - 2));

	for(int i = 1;i <= n - m + 1;i++){
		LL tmp = mul(CC[i - 1],fpm(n - m - i + 1,n - 2));
		if(i & 1) ans = add(ans,tmp);
		else ans = minus(ans,tmp);
	}

	printf("%lld\n",mul(ans,C(n,m)));
	
	return 0;
}
