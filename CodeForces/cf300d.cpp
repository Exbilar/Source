#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const LL mod = 7340033;
static const int maxm = 7e4 + 10;

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

LL R[maxm],ans[40][maxm];
LL L,n,m,N,K,Q;

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

void NTT(LL A[],int f){
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

void solve(LL *F,LL *P){
	for(int i = 0;i < 1024;i++) F[i] = P[i];	
	NTT(F,1);
	for(int i = 0;i < n;i++) F[i] = F[i] * F[i] % mod;
	NTT(F,-1);	
}

int main(){   
	
	m = 1024 + 1024;
	for(n = 1;n <= m;n <<= 1) L++;
	for(int i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	
	ans[0][0] = 1;
	for(int i = 1;i <= 35;i++){
		solve(ans[i],ans[i - 1]),solve(ans[i],ans[i]);
		for(int j = 1024 - 1;j > 0;j--) ans[i][j] = ans[i][j - 1];
		ans[i][0] = 1;
	}
	
	read(Q);
	   	
	while(Q--){
		read(N),read(K);
		int cnt = 0;
		while((N & 1) && (N > 1)) N >>= 1,cnt++;
		printf("%lld\n",ans[cnt][K]);
	}
	
	return 0;
}
