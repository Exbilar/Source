#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;
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

LL f[maxm][2],bit[maxm];
LL n,cas;

LL add(LL x,LL y){
	x += y; if(x >= mod) x -= mod;
	return x;
}

LL mul(LL x,LL y){
	x = (x + mod) % mod;
	y = (y + mod) % mod;
	return (x * y) % mod;
}

struct Matrix{
	LL mtx[5][5];
	Matrix(){clr(mtx);}
	
	Matrix operator * (const Matrix &M) const {
		Matrix res;
		for(int i = 1;i <= 2;i++){
			for(int j = 1;j <= 2;j++){
				for(int k = 1;k <= 2;k++){
					res.mtx[i][j] = add(res.mtx[i][j],mul(mtx[i][k],M.mtx[k][j]));
				}
			}
		}
		return res;
	}
	
}Fib,get;

void getDP(int N){
	f[0][0] = 1;
	for(int i = 1;i <= N;i++){
		f[i][1] += f[i - 1][0];
		f[i][0] += f[i - 1][0] + f[i - 1][1];
	}
}

LL solve1(LL N){
	LL res = 0,len = 0;
	while(N){
		bit[++len] = N & 1;
		N >>= 1;
	}
	for(int i = 1;i < len;i++) res += f[i][1];

	int pre = 1;
	for(int i = len - 1;i >= 1;i--){
		if(bit[i]) res += f[i][0];
		if(pre && bit[i]) break;
		pre = bit[i];
	}
	
	return res;
}

Matrix fpm(Matrix x,LL k){
	Matrix res = x; k--;
	while(k){
		if(k & 1) res = res * x;
		x = x * x;
		k >>= 1;
	}
	return res;
}

LL solve2(LL N){
	Fib.mtx[1][1] = 2,Fib.mtx[1][2] = 3;
	get.mtx[1][1] = 0,get.mtx[1][2] = 1;
	get.mtx[2][1] = 1,get.mtx[2][2] = 1;

	if(N == 1) return 2;
	if(N == 2) return 3;

	Fib = Fib * fpm(get,N - 2);
	return Fib.mtx[1][2];
}

int main(){
	read(cas);
	getDP(63);
	
	while(cas--){
		read(n);
		printf("%lld\n%lld\n",solve1(n + 1),solve2(n));
	}
	return 0;
}
