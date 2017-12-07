#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: max;
using std :: min;
using std :: complex;

typedef long long LL;
typedef complex<double> CP;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const double pi = acos(-1);
static const int maxm = 1e6 + 10;

template <class T> inline bool chkmax(T &x,T y){
	return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
	return x > y ? x = y,true : false;
}

template <typename T> inline void read (T &in){
	in = 0; char ch = getchar(); T f = 1;
	for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
	for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

CP A[maxm],B[maxm];
LL R[maxm],X[maxm],Y[maxm];
LL N,n,m,L,K;

void FFT(CP *A,int f){
	for(int i = 0;i < n;i++)
		if(i < R[i]) std :: swap(A[i],A[R[i]]);
	
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
}

int main(){
	
	read(n); N = n; n--;
	for(int i = 0;i <= n;i++) read(X[i]),read(Y[i]);

	for(int i = 0;i <= n;i++) A[i] = X[i],B[i] = Y[N - i - 1];

	m = n + n;
	for(n = 1;n <= m;n <<= 1) L++;
	for(int i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

	FFT(A,1),FFT(B,1);
	for(int i = 0;i <= n;i++) A[i] = A[i] * B[i];
	FFT(A,-1);
	
	for(int i = 0;i < N;i++)
		printf("%lld\n",(LL) (A[N + i - 1].real() / n + 0.1));
	
	return 0;
}
