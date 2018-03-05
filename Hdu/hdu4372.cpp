#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 3e3 + 10;
static const int mod = 1e9 + 7;

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

LL C[maxm][maxm],S[maxm][maxm];

void init(int N){
	for(int i = 0;i <= N;i++) C[i][0] = C[i][i] = 1;
	for(int i = 2;i <= N;i++){
		for(int j = 1;j < i;j++){
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
	}

	S[1][1] = 1;
	for(int i = 2;i <= N;i++){
		for(int j = 1;j <= i;j++){
			S[i][j] = (S[i - 1][j - 1] + (i - 1) * S[i - 1][j] % mod) % mod;
		}
	}
}

int main(){

	init(2000 + 10);

	LL N,F,B,cas;
	
	read(cas);

	while(cas--){
		read(N),read(F),read(B);
		if(F + B - 2 <= 2000)
			printf("%lld\n",C[F + B - 2][F - 1] * S[N - 1][F + B - 2] % mod);
		else puts("0");
	}

	return 0;
}
