#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e5 + 10;
static const LL mod = 998244353;

template <class T> inline bool chkmax(T &x,T y){
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
    return x > y ? x = y,true : false;
}

class FasterInput{
private:
	
	static const int L = 1 << 15 | 1;
	char buffer[L], *_, *__;

	inline void NextChar(char &ch){
		if(_ == __) __ = (_ = buffer) + fread(buffer, 1, L, stdin);
		ch = _ == __? EOF : *_++;
	}

public:
	
	template <class T> void operator() (T &in){
		char ch; int f = 1;
		for(NextChar(ch); !isdigit(ch); NextChar(ch)) if(ch == '-') f = -1;
		for(in = 0; isdigit(ch); NextChar(ch)) in = in * 10 + ch - '0';
		in *= f;
	}
}read;

inline LL add(LL x,LL y){
	x += y; if(x >= mod) x -= mod;
	return x;
}

inline LL minus(LL x,LL y){
	x -= y; if(x < 0) x += mod;
	return x;
}

inline LL fpm(LL x,LL k){
	LL res = 1;
	while(k){
		if(k & 1) res = 1LL * res * x % mod;
		x = 1LL * x * x % mod;
		k >>= 1;
	}
	return res;
}

LL A[maxm],B[maxm],cntl[maxm],cntr[maxm];
int R[maxm],X[maxm];

int n,m,L,N;
LL ans;

inline void NTT(LL *A,int f){
	for(register int i = 0;i < n;i++)
		if(i < R[i]) std :: swap(A[i],A[R[i]]);
	
	for(register int i = 1;i < n;i <<= 1){
		LL gn = fpm(3LL,(LL) (mod - 1) / (i << 1));
		if(f == -1) gn = fpm(gn,mod - 2);
		
		for(register int j = 0;j < n;j += (i << 1)){
			LL g = 1;
			for(register int k = 0;k < i;k++,g = 1LL * g * gn % mod){
				LL x = A[j + k],y = 1LL * A[i + j + k] * g % mod;
				A[j + k] = add(x,y);
				A[i + j + k] = minus(x,y);
			}
		}
	}
	
	if(f == -1){
		LL inv = fpm(n,mod - 2);
		for(register int i = 0;i < n;i++) A[i] = A[i] * inv % mod;
	}
	
}

int main(){

	//freopen("bzoj3509.in","r",stdin);
	
	read(N);
	for(int i = 1;i <= N;i++) read(X[i]),cntr[X[i]]++;
	
	int blck = min(N,(int) (sqrt(N)) * 6);
	
	for(register int l = 1;l < N;l += blck){
		int r = min(l + blck - 1,N);
		for(register int i = l;i <= r;i++) cntr[X[i]]--;
		for(register int i = l;i <= r;i++){
			for(register int j = i + 1;j <= r;j++){
				int x = 2 * X[i] - X[j];
				int y = 2 * X[j] - X[i];
				if(x >= 0) ans += cntl[x];
				if(y >= 0) ans += cntr[y];
			}
			cntl[X[i]]++;
		}
	}
	
	for(register int l = 1;l < N;l += blck){
		int r = min(l + blck - 1,N);
		
		m = 0,L = 0;
		for(register int i = 1;i < l;i++) A[X[i]]++,chkmax(m,X[i]);
		for(register int i = r + 1;i <= N;i++) B[X[i]]++,chkmax(m,X[i]);
		
		for(n = 1;n <= m + m;n <<= 1) L++;
		for(register int i = 0;i < n;i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
		
		NTT(A,1),NTT(B,1);
		for(register int i = 0;i < n;i++) A[i] = A[i] * B[i] % mod;
		NTT(A,-1);
		
		for(register int i = l;i <= r;i++) ans += A[X[i] << 1];
		
		for(register int i = 0;i < n;i++) A[i] = 0,B[i] = 0;
		
	}
	
	printf("%lld\n",ans);	

	return 0;
}
