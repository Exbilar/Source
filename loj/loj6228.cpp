#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: max;
using std :: min;
using std :: complex;

typedef long long LL;
typedef complex<double> CP;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;
static const double pi = acos(-1);

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

CP A[maxm],B[maxm],C[maxm];
LL X[maxm],R[maxm],bit[maxm],ddf[maxm];
LL n,m,N,L;
LL ans;

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
	if(f == -1)
		for(int i = 0;i < n;i++) A[i].real() = (A[i].real() / n + 0.1);
}

int lowbit(int x){
	return x & -x;
}

void Upt(int k,int v){
	for(int i = k;i <= m;i += lowbit(i)) bit[i] += v;
}

LL Qry(int k){
	LL res = 0;
	for(int i = k;i;i -= lowbit(i)) res += bit[i];
	return res;
}

int main(){

	//freopen("loj6228.in","r",stdin);
	
	read(N);
	for(int i = 0;i < N;i++)
		read(ddf[i]),X[ddf[i]]++,chkmax(m,ddf[i]);
	
	m = m + m;

	for(int i = 0;i < N;i++) Upt(ddf[i],1);
	
	for(n = 1;n <= m;n <<= 1) L++;
	for(int i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	
	for(int i = 1;i <= m / 2;i++)
		A[i] = X[i],B[i * 2] = X[i];
	
	FFT(A,1),FFT(B,1);
	for(int i = 0;i < n;i++) C[i] = A[i] * A[i] - B[i];
	FFT(C,-1);
	
	for(int i = 0;i <= m;i++) C[i].real() /= 2.0;
	for(int i = 1;i <= m;i++){
		ans += (N - Qry(i - 1)) * (LL) (C[i].real());		
	}
	
	LL tot = N * (N - 1) / 6 * (N - 2);
	printf("%.6lf\n",(double) ((double) (tot - ans) / (double) (tot)));
	
	return 0;
}
