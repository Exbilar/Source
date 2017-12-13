#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const LL mod = 1004535809;
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

LL A[maxm],B[maxm],fac[maxm],finv[maxm],R[maxm],two[maxm],f[maxm];
LL n,m,L,N;

LL add(LL x,LL y){
	return (x + y) % mod;
}

LL minus(LL x,LL y){		
	return ((x - y) % mod + mod) % mod;
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

void NTT(LL *A,LL f){
	for(LL i = 0;i < n;i++)
		if(i < R[i]) std :: swap(A[i],A[R[i]]);
	
	for(LL i = 1;i < n;i <<= 1){
		LL gn = fpm(3LL,(mod - 1) / i / 2);
		if(f == -1) gn = fpm(gn,mod - 2);
		
		for(LL j = 0;j < n;j += (i << 1)){
			LL g = 1;
			for(LL k = 0;k < i;k++,g = 1LL * g * gn % mod){
                LL x = A[j + k],y = 1LL * A[i + j + k] * g % mod;
                A[j + k] = add(x,y);
                A[i + j + k] = minus(x,y);
            }
		}
	}
	
	if(f == -1){
		LL inv = fpm(n,mod - 2);
		for(LL i = 0;i < n;i++) A[i] = A[i] * inv % mod;
	}
}

void solve(int l,int r){
	if(l == r){
		f[l] = minus(two[l],fac[l - 1] * f[l] % mod);
		return ;
	}
	
	int mid = (l + r) >> 1;
	
	solve(l,mid);
	
	m = mid - l + 1 + r - mid,L = 0;
	for(n = 1;n <= m;n <<= 1) L++;
	for(int i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	
	for(int i = 0;i < n;i++) A[i] = 0,B[i] = 0;
	for(int i = l;i <= mid;i++) A[i - l] = (f[i] * finv[i - 1]) % mod;
	for(int i = 1;i <= r - l;i++) B[i - 1] = (1LL * two[i] * finv[i]) % mod;   
	
	NTT(A,1);
	NTT(B,1);
	
	for(int i = 0;i < n;i++) A[i] = (1LL * A[i] * B[i]) % mod;
	
	NTT(A,-1);	
	
	for(int i = mid + 1;i <= r;i++) f[i] = (f[i] + A[i - l - 1]) % mod;
		
	solve(mid + 1,r);
}

int main(){
	read(N);
	
	fac[0] = 1,finv[0] = 1;
	for(LL i = 1;i <= N;i++){
		fac[i] = fac[i - 1] * i % mod;
		finv[i] = fpm(fac[i],mod - 2);
	}
	
	for(LL i = 0;i <= N;i++){
		two[i] = fpm(2LL,i * (i - 1) / 2);
	}
	
	solve(1,N);
	
	printf("%lld\n",f[N]);
	
	return 0;
}
