#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x,v) memset(x,v,sizeof x)

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

CP A[maxm],B[maxm];

int col1[maxm],col2[maxm],lst[maxm],nxt[maxm];
int R[maxm],can[maxm][7];

LL ans[maxm];

char str1[maxm],str2[maxm];

int N,M,K,L,n,m;

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

	if(f == -1) for(int i = 0;i < n;i++) A[i] /= n;	
}

int calc(char chr){
	if(chr == 'A') return 1;
	if(chr == 'G') return 2;
	if(chr == 'T') return 3;
	if(chr == 'C') return 4;
	return 0;
}

void init(int col){	
	clr(A,0),clr(B,0),clr(can,0);
	
	int pre = -1;
	for(int i = 0;i < N;i++){
		if(col1[i] == col){
			lst[i] = i,nxt[i] = i;
			pre = i;
		}
		else lst[i] = pre;
	}
	
	pre = N;
	for(int i = N - 1;i >= 0;i--){
		if(col1[i] == col){
			lst[i] = i,nxt[i] = i;
			pre = i;
		}
		else nxt[i] = pre;
	}	
	
	for(int i = 0;i < N;i++){
		if(i - lst[i] <= K && lst[i] >= 0) can[i][col] = 1;
		else if(nxt[i] - i <= K && nxt[i] < N) can[i][col] = 1;
	}
	
	for(int i = 0;i < N;i++) A[i] = can[i][col];
	for(int i = 0;i < M;i++)
		if(col2[i] == col) B[i] = 1;
	
}

int main(){
	
	read(N),read(M),read(K);
	scanf("%s%s",str1,str2);

	for(int i = 0;i < N;i++) col1[i] = calc(str1[i]);
	for(int i = 0;i < M;i++) col2[i] = calc(str2[M - i - 1]);
	
	m = N + N;
	for(n = 1;n <= m;n <<= 1) L++;
	for(int i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	
	for(int i = 1;i <= 4;i++){
		init(i);
		
		FFT(A,1),FFT(B,1);
		for(int j = 0;j < n;j++) A[j] = A[j] * B[j];
		FFT(A,-1);
		
		for(int j = 0;j < N;j++) ans[j] = ans[j] + round(A[j].real());		
	}

	int _ans = 0;
	for(int i = 0;i < N;i++)
		if(ans[i] == M) _ans++;

	printf("%d\n",_ans);
	
	return 0;
}
