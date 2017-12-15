#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;
static const LL mod = 998244353;

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
		if(k & 1) res = res * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return res;
}

LL A[maxm],B[maxm],C[maxm],T[maxm],RT[maxm],R[maxm];
LL inv2 = fpm(2LL,mod - 2);
LL n,m,N,M,L;

void NTT(LL *A,int f){
	for(int i = 0;i < n;i++)
		if(i < R[i]) std :: swap(A[i],A[R[i]]);
	
	for(int i = 1;i < n;i <<= 1){
		LL gn = fpm(3LL,(mod - 1) / (i << 1));
		if(f == -1) gn = fpm(gn,mod - 2);
		
		for(int j = 0;j < n;j += (i << 1)){
			LL g = 1;
			for(int k = 0;k < i;k++,g = g * gn % mod){
				LL x = A[j + k],y = A[i + j + k] * g % mod;
				A[j + k] = add(x,y);
				A[i + j + k] = minus(x,y);
			}
		}		
	}
	if(f == -1){
		LL inv = fpm(n,mod - 2);
		for(int i = 0;i < n;i++) A[i] = A[i] * inv % mod;
	}
}

void getRev(LL *A,LL *B,LL N){
	if(N == 1) return B[0] = fpm(A[0],mod - 2),void();
	getRev(A,B,N >> 1);
	
	m = N + N; L = 0;
	for(n = 1;n <= m;n <<= 1) L++;
	for(int i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	
	for(int i = 0;i < n;i++) T[i] = A[i];
	for(int i = N;i < n;i++) T[i] = 0;
	
	NTT(T,1),NTT(B,1);
	for(int i = 0;i < n;i++) B[i] = (B[i] * (2LL - T[i] * B[i] % mod + mod)) % mod;
	NTT(B,-1);
	
	for(int i = N;i < n;i++) B[i] = 0;
}

void getSqrt(LL *A,LL *B,LL N){
	if(N == 1) return B[0] = 1,void();
	getSqrt(A,B,N >> 1);
	
	m = N + N; L = 0;
	for(n = 1;n <= m;n <<= 1) L++;
	for(int i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	
	for(int i = 0;i < n;i++) RT[i] = 0;
	getRev(B,RT,N);
	
	for(int i = 0;i < n;i++) T[i] = A[i];
	for(int i = N;i < n;i++) T[i] = 0;

	NTT(T,1),NTT(RT,1),NTT(B,1);
	for(int i = 0;i < n;i++) B[i] = (inv2 * (B[i] + T[i] * RT[i] % mod) % mod) % mod;
	NTT(B,-1);
	
	for(int i = N;i < n;i++) B[i] = 0;
}

int main(){
	
	read(N),read(M); M++;
	
	C[0] = 1;
	for(int i = 1,in;i <= N;i++) read(in),C[in] -= 4;
	for(int i = 0;i < M;i++)
		if(C[i] < 0) C[i] += mod;
	
	LL len = 1;
	while(len < M) len <<= 1;
	getSqrt(C,A,len);
	
	A[0] = add(A[0],1);
	getRev(A,B,len);
	
	for(int i = 1;i < M;i++) printf("%lld\n",B[i] * 2 % mod);
	
	return 0;
}
