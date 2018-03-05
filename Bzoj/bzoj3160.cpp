#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: complex;

typedef long long LL;
typedef complex<double> CP;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;
static const int mod = 1e9 + 7;
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

char str[maxm],_str[maxm];

CP A[maxm],B[maxm];

LL F[maxm],bin[maxm];

int RL[maxm],R[maxm];

LL n,L,len,ans;

inline LL add(LL x,LL y){
	x += y; if(x >= mod) x -= mod;
	return x;
}

inline LL minus(LL x,LL y){
	return (x - y + mod) % mod;
}

inline LL mul(LL x,LL y){
	return (x * y) % mod;
}

inline LL fpm(LL x,LL k){
	LL res = 1;
	while(k){
		if(k & 1) res = res * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return res;
}

void FFT(CP *A,int f){
	for(int i = 0;i < n;i++){
		if(i < R[i]) std :: swap(A[i],A[R[i]]);
	}
	for(int i = 1;i < n;i <<= 1){
		CP wn(cos(pi / i),sin(pi / i) * f);
		for(int j = 0;j < n;j += (i << 1)){
			CP w(1,0);
			for(int k = 0;k < i;k++,w *= wn){
				CP x = A[j + k],y = A[i + j + k] * w;
				A[j + k] = x + y;
				A[i + j + k] = x - y;
			}
		}
	}
	if(f == -1){
		for(int i = 0;i < n;i++){
			A[i].real() = (A[i].real() + 0.5) / n;
		}
	}
}

void pretreat(){
	_str[0] = '%',_str[1] = '#';
	for(int i = 1;i <= len;i++){
		_str[i << 1] = str[i - 1];
		_str[i << 1 | 1] = '#';
	}
}

LL manacher(){
	pretreat();
	int maxR = 0,pos = 0;
	LL res = 0;
	for(int i = 1;i <= (len << 1 | 1);i++){
		if(i < maxR) RL[i] = min(RL[pos * 2 - i],maxR - i);
		else RL[i] = 1;
		while(_str[i + RL[i]] == _str[i - RL[i]]) RL[i]++;
		if(i + RL[i] > maxR) maxR = i + RL[i],pos = i;
		res = (res + RL[i] / 2) % mod;
	}
	return res;
}

int main(){

	//freopen("bzoj3160.in","r",stdin);

	bin[0] = 1;
	for(int i = 1;i <= maxm;i++) bin[i] = (bin[i - 1] << 1) % mod;
	
	scanf("%s",str);
	len = strlen(str);

	for(n = 1;n <= len << 1;n <<= 1) L++;
	for(int i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));

	for(int i = 0;i < len;i++){
		if(str[i] == 'a') B[i] = 0;
		else B[i] = 1;
	}

	FFT(B,1);
	for(int i = 0;i < n;i++){
		A[i] += B[i] * B[i];
	}

	clr(B);
	
	for(int i = 0;i < len;i++){
		if(str[i] == 'b') B[i] = 0;
		else B[i] = 1;
	}

	FFT(B,1);
	for(int i = 0;i < n;i++){
		A[i] += B[i] * B[i];
	}

	FFT(A,-1);

	for(int i = 2;i < (len << 1 | 1);i++){
		F[i] += (LL) (A[i - 2].real());
	}

	for(int i = 2;i < (len << 1 | 1);i++){
		ans = (ans + bin[(F[i] + 1) >> 1] - 1) % mod;
	}

	LL _ans = manacher();

	printf("%lld\n",minus(ans,_ans));

	return 0;
}
