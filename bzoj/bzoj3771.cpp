#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: complex;
using std :: swap;
using std :: max;
using std :: min;

typedef long long LL;
typedef complex<double> CP;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const double pi = acos(-1);
static const double eps = 1e-8;
static const int maxm = 3e5 + 10;

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

CP A[maxm],B[maxm],C[maxm],E[maxm];
int W[maxm],R[maxm];
int n,m,L;

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
	if(f == -1) for(int i = 0;i < n;i++) A[i] /= n;
}

int main(){

	//freopen("triple.in","r",stdin);
	
	read(n);
	for(int i = 1;i <= n;i++){
		int x; read(x); W[x]++;
		chkmax(m,x);
	}
	
	m = m * 3;
	for(n = 1;n <= m;n <<= 1) L++;
	
	for(int i = 0;i < n;i++)
		R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	
	for(int i = 0;i <= n;i++) A[i] = W[i];
	for(int i = 0;i <= n;i++) B[i * 2] = W[i];
	for(int i = 0;i <= n;i++) C[i * 3] = W[i];
	
	FFT(A,1),FFT(B,1),FFT(C,1);

	for(int i = 0;i <= n;i++)
		E[i] = A[i] + (A[i] * A[i] - B[i]) / 2.0 + (A[i] * A[i] * A[i] - A[i] * B[i] * 3.0 + 2.0 * C[i]) / 6.0;
	
	FFT(E,-1);
	
	for(int i = 0;i <= n;i++){
		if(E[i].real() > eps) printf("%d %d\n",i,(int) (E[i].real() + 0.5));
	}
	
	return 0;
}
