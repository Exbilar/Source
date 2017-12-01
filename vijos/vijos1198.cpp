#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: max;
using std :: min;

typedef long long LL;

static const int maxm = 2e3 + 10;
static const int maxn = 1e6 + 10;
static const int INF = 1 << 30;
static const LL oo = 1LL << 62;

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

LL ddf[maxm][maxm],f[maxn];
LL n,m;

LL fpm(LL x,LL k){
	LL res = 1;
	while(k){
		if(k & 1) res = res * x;
		x = x * x;
		k >>= 1;
	}
	return res;
}

int main(){
	int A,B;
	
	read(m),read(n);

	for(int i =1;i <= n;i++){
		read(A),read(B);
		for(int j = 1;j <= m;j++) ddf[i][j] = A * fpm((LL)j,B);
	}

	memset(f,0x3f,sizeof f); f[0] = 0;
	
	for(int i = 1;i <= n;i++)
		for(int v = m;v >= 0;v--)
			for(int k = 1;k <= v;k++)
				chkmin(f[v],f[v - k] + ddf[i][k]);
	
	printf("%lld\n",f[m]);
	
	return 0;
}
