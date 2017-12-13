#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 4e6 + 10;
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

LL X[maxm],A[maxm],R[maxm],B[maxm],ans[maxm];
LL n,m,L,N,M,cnt;   

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

int main(){
	
	read(N),read(m);
	for(int i = 1;i <= N;i++)
		read(X[i]),A[X[i]]++;
	
	for(n = 1;n <= m + m;n <<= 1) L++;
	for(int i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	
	for(int i = 0;i < n;i++) B[i] = A[i];
	
	NTT(B,1);
	for(int i = 0;i < n;i++) B[i] = B[i] * B[i] % mod;
	NTT(B,-1);
	
	for(int i = 1;i <= m;i++){
		if(!A[i] && B[i]) return puts("NO"),0;
	}
	
	puts("YES");
	for(int i = 1;i <= m;i++){
		if(A[i] && !B[i]) ans[++cnt] = i;
	}
	
	printf("%lld\n",cnt);
	for(int i = 1;i <= cnt;i++) printf("%lld ",ans[i]);	
	
	putchar(10);
	
	return 0;
}
