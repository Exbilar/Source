#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int mod = 998244353;
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

LL A[maxm],B[maxm],finv[maxm],fac[maxm],R[maxm],f[maxm];
LL L,n,m,N;

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

void NTT(LL *A,int f){
    for(int i = 0;i < n;i++)
        if(i < R[i]) std :: swap(A[i],A[R[i]]);
	
    for(int i = 1;i < n;i <<= 1){
        LL gn = fpm(3LL,(mod - 1) / (i << 1));
        if(f == -1) gn = fpm(gn,mod - 2);
            
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
        LL inv = fpm(n,mod - 2);
        for(int i = 0;i < n;i++) A[i] = A[i] * inv % mod;
    }
    
}

void solve(int l,int r){
	if(l == r) return ;
	int mid = (l + r) >> 1;
	solve(l,mid);
	
	m = (r - l + 1),L = 0;
	for(n = 1;n <= m;n <<= 1) L++;
	for(int i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	
	for(int i = 0;i < n;i++) A[i] = B[i] = 0;
	for(int i = l;i <= mid;i++) A[i - l] = f[i];
	for(int i = 0;i <= r - l;i++) B[i] = finv[i];
	
	NTT(A,1),NTT(B,1);
	for(int i = 0;i < n;i++) A[i] = A[i] * B[i] % mod;
	NTT(A,-1);
	
	for(int i = mid + 1;i <= r;i++) f[i] = (f[i] + 2 * A[i - l]) % mod;
	solve(mid + 1,r);
}

int main(){
	
	read(N);
	fac[0] = finv[0] = 1;
	for(LL i = 1;i <= N;i++){
		fac[i] = fac[i - 1] * i % mod;
		finv[i] = fpm(fac[i],mod - 2);
	}
	
	f[0] = 1;
	
	solve(0,N);
	
	LL ans = 0;
	for(int i = 0;i <= N;i++) ans = (ans + (f[i] * fac[i] % mod) % mod) % mod;
	
	printf("%lld\n",(ans + mod) % mod);
	
	return 0;
}
