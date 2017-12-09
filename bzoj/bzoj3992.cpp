#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const LL mod = 1004535809;
static const int maxm = 2e5 + 10;

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

LL A[maxm],B[maxm],C[maxm],R[maxm],S[maxm];
LL ind[maxm],pwr[maxm],cnt[maxm],ans[maxm];
LL n,m,L,N,M,X,NUM;

LL add(LL x,LL y){
	x += y; if(x >= mod) x -= mod;
	return x;
}

LL minus(LL x,LL y){
	x -= y; if(x < 0) x += mod;
	return x;
}

LL fpm(LL x,LL k,LL P){
	LL res = 1;
	while(k){
		if(k & 1) res = res * x % P;
		x = x * x % P;
		k >>= 1;
	}
	return res;
}

bool chk(LL g,LL P){
	for(int i = 2;i * i <= P;i++)
		if(fpm(g,(P - 1) / i,P) == 1 && (P - 1) % i == 0) return 0;
	return 1;
}

LL getG(LL P){
	if(P == 2) return 1;
	
	LL res = 2;
	while(!chk(res,P)) res++;	
	return res;
}

void NTT(LL *A,int f){
	for(int i = 0;i < n;i++)
		if(i < R[i]) std :: swap(A[i],A[R[i]]);

	for(int i = 1;i < n;i <<= 1){
		LL gn = fpm(3LL,(mod - 1) / (i << 1),mod);
		if(f == -1) gn = fpm(gn,mod - 2,mod);
			
		for(int j = 0;j < n;j += (i << 1)){
			LL g = 1LL;
			for(int k = 0;k < i;k++,g = g * gn % mod){
				LL x = A[j + k],y = A[i + j + k] * g % mod;
				A[j + k] = add(x,y);
				A[i + j + k] = minus(x,y);
			}
		}
	}

	if(f == -1){
		LL inv = fpm(n,mod - 2,mod);
		for(int i = 0;i < n;i++) A[i] = A[i] * inv % mod;
	}
	
}

void mul(LL *A,LL *BB,LL *CC){
	for(int i = 0;i < n;i++) B[i] = BB[i],C[i] = CC[i];
	NTT(B,1),NTT(C,1);
	for(int i = 0;i < n;i++) A[i] = B[i] * C[i] % mod;
	NTT(A,-1);
	for(int i = M - 1;i < n;i++){
		A[i - M + 1] = (A[i - M + 1] + A[i]) % mod;
		A[i] = 0;
	}
}

void fPwr(LL k){
	ans[0] = 1;
	while(k){
		if(k & 1) mul(ans,ans,A);
		mul(A,A,A);
		k >>= 1;
	}
}

int main(){   
	
	read(N),read(M),read(X),read(NUM);
	for(int i = 0;i < NUM;i++) read(S[i]);
	
	LL G = getG(M);
	
	pwr[0] = 1,ind[1] = 0;
	for(int i = 1;i < M - 1;i++){
		pwr[i] = pwr[i - 1] * G % M;
		ind[pwr[i]] = i;
	}
	
	m = M + M;
	for(n = 1;n <= m;n <<= 1) L++;
	for(int i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	
	for(int i = 0;i < NUM;i++)
		if(S[i] != 0) A[ind[S[i]]]++;
	
	fPwr(N);
	
	printf("%lld\n",ans[ind[X]]);
	
	return 0;
}
