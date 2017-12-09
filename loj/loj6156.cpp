#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: complex;

typedef long long LL;
typedef complex<double> CP;

static const LL INF = 1 << 30;
static const LL oo = 1LL << 62;
static const LL mod = 469762049;
static const LL maxm = 2e5 + 10;
static const double pi = acos(-1);

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

CP A[maxm];
LL B[maxm],R[maxm],ind[maxm],X[maxm],pwr[maxm];
LL n,m,L,N,M;

LL add(LL x,LL y,LL P){
	x += y; if(x >= P) x -= P;
	return x;
}

LL minus(LL x,LL y,LL P){
	x -= y; if(x < 0) x += P;
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
	for(LL i = 2;i * i <= P;i++)
		if((P - 1) % i == 0 && fpm(g,(P - 1) / i,P) == 1) return 0;
	return 1;
}

LL getG(LL P){
	if(P == 2) return 1;
	LL res = 2;
	while(!chk(res,P)) res++;
	return res;
}

void NTT(LL *A,LL f){
    for(LL i = 0;i < n;i++)
        if(i < R[i]) std :: swap(A[i],A[R[i]]);
    
    for(int i = 1;i < n;i <<= 1){
        LL gn = fpm(3,(mod - 1) / (i << 1),mod);
        if(f == -1) gn = fpm(gn,mod - 2,mod);
            
        for(int j = 0;j < n;j += (i << 1)){
            LL g = 1;
            for(int k = 0;k < i;k++,g = 1LL * g * gn % mod){
                int x = A[j + k],y = 1LL * A[i + j + k] * g % mod;
                A[j + k] = add(x,y,mod);
                A[i + j + k] = minus(x,y,mod);
            }
        }
    }
    if(f == -1){
        LL inv = fpm(n,mod - 2,mod);
        for(int i = 0;i < n;i++) A[i] = 1LL * A[i] * inv % mod;
    }
}

void FFT(CP *A,int f){
    for(int i = 0;i < n;i++)
        if(i < R[i]) swap(A[i],A[R[i]]);
    for(int i = 1;i < n;i <<= 1){
        CP wn(cos(pi / i),sin(pi / i) * f),x,y;
        for(int j = 0;j < n;j += (i << 1)){
            CP w(1,0);
            for(int k = 0;k < i;k++,w *= wn){
                x = A[j + k],y = A[i + j + k] * w;
                A[j + k] = x + y;
                A[i + j + k] = x - y;
            }
        }
    }
    
    if(f == -1)
		for(int i = 0;i < n;i++) A[i].real() = A[i].real() / n + 0.5;
}
void init(){
	clr(X),clr(A),clr(B),clr(R),clr(pwr),clr(ind);
	L = 0,n = 0,m = 0,N = 0,M = 0;
}

void solve(){
	read(N),read(M);
	for(LL i = 0;i < N;i++) read(X[i]),X[i] %= M;
	
	LL G = getG(M);
	
	pwr[0] = 1,ind[1] = 0;
	for(LL i = 1;i < M - 1;i++){
		pwr[i] = pwr[i - 1] * G % M;
		ind[pwr[i]] = i;
	}
	
	LL tot = 0;
	for(LL i = 0;i < N;i++){
		if(!X[i]) tot++;
		else B[1LL * X[i] * X[i] % M]++,A[ind[X[i]]].real() += 1.0;
	}
	
	m = M + M;
	for(n = 1;n <= m;n <<= 1) L++;
	for(LL i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	
	printf("%lld\n",1LL * (N - 1) * tot - 1LL * tot * (tot - 1) / 2);
	
	FFT(A,1);
	for(LL i = 0;i < n;i++) A[i] = A[i] * A[i];
	FFT(A,-1);
	
	for(LL i = 1;i <= M - 1;i++){
		printf("%lld\n",(LL)
			   ((A[ind[i]].real() + A[ind[i] + M - 1].real() - B[i]) / 2.0));
	}
}

int main(){   
	
	LL cas;
	read(cas);
	
	while(cas--){
		init();
		solve();
	}
	
	return 0;
}
