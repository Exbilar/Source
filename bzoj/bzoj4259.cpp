#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: max;
using std :: min;
using std :: complex;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const double pi = acos(-1);
static const int maxm = 2e6 + 10;

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

struct CP{
	double r,i;
	CP(double _r = 0,double _i = 0){r = _r,i = _i;}
	CP operator + (const CP &x){return CP(r + x.r,i + x.i);}
	CP operator - (const CP &x){return CP(r - x.r,i - x.i);}
	CP operator * (const CP &x){return CP(r * x.r - i * x.i,r * x.i + i * x.r);}
};

char str1[maxm],str2[maxm];
CP A[maxm],B[maxm],f[maxm];
int R[maxm],X[maxm],Y[maxm],ans[maxm];
int n,m,L,len1,len2,cnt;

void FFT(CP *A,int f){
    for(int i = 0;i < n;i++)
        if(i < R[i]) std :: swap(A[i],A[R[i]]);
    
    for(int i = 1;i < n;i <<= 1){
        CP wn(cos(pi / i),sin(pi / i) * f),x,y;
        for(int j = 0;j < n;j += (i << 1)){
            CP w(1,0);
            for(int k = 0;k < i;k++,w = w * wn){
                x = A[j + k],y = A[i + j + k] * w;
                A[j + k] = x + y;
                A[i + j + k] = x - y;
            }
        }
    }
    
    if(f == -1) for(int i = 0;i < n;i++) A[i].r = A[i].r / n;
}

int main(){   
	
	read(len1),read(len2);
	scanf("%s",str1);
	scanf("%s",str2);
	
	for(int i = 0;i < len1;i++)
		if(str1[len1 - i - 1] != '*') X[i] = str1[len1 - i - 1] - 'a' + 1;
	
	for(int i = 0;i < len2;i++)
		if(str2[i] != '*') Y[i] = str2[i] - 'a' + 1;
	
	m = len2 + len2;
	for(n = 1;n <= m;n <<= 1) L++;
	for(int i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

	//------------------------------------------------
	
	for(int i = 0;i < n;i++) A[i] = X[i] * X[i] * X[i];
	for(int i = 0;i < n;i++) B[i] = Y[i];
	
	FFT(A,1),FFT(B,1);
	for(int i = 0;i < n;i++) A[i] = A[i] * B[i];	
	for(int i = 0;i < n;i++) f[i] = f[i] + A[i];
	
	//------------------------------------------------
	
	for(int i = 0;i < n;i++) A[i] = X[i];
	for(int i = 0;i < n;i++) B[i] = Y[i] * Y[i] * Y[i];
	
	FFT(A,1),FFT(B,1);
	for(int i = 0;i < n;i++) A[i] = A[i] * B[i];	
	for(int i = 0;i < n;i++) f[i] = f[i] + A[i];
		
	//------------------------------------------------

	for(int i = 0;i < n;i++) A[i] = X[i] * X[i];
	for(int i = 0;i < n;i++) B[i] = Y[i] * Y[i];

	FFT(A,1),FFT(B,1);
	for(int i = 0;i < n;i++) A[i] = A[i] * B[i];
	for(int i = 0;i < n;i++) f[i] = f[i] - A[i] * CP(2.0,0.0);
	
	//------------------------------------------------
	
	FFT(f,-1);		
	
	for(int i = len1 - 1;i <= len2 - 1;i++)
		if(f[i].r < 0.1) ans[++cnt] = i - len1 + 2;
	
	printf("%d\n",cnt);
	
	for(int i = 1;i < cnt;i++) printf("%d ",ans[i]);
	if(cnt) printf("%d\n",ans[cnt]);
	
	return 0;
}
