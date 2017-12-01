#include <bits/stdc++.h>

using std :: max;
using std :: min;

typedef long long LL;

static const int maxm = 1 << 18;
static const int maxn = 100 + 10;
static const int INF = 1 << 30;
static const LL oo = 1LL << 62;

template <class T> bool chkmax(T &x,T y){
	return x < y ? x = y,true : false;
}

template <class T> bool chkmin(T &x,T y){
	return x > y ? x = y,true : false;
}

template <class T> void read(T &in){
	in = 0; T f = 1; char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = (in << 3) + (in << 1) + ch - '0';
	in = in * f;
}

int f[maxn][maxm];
int c[maxn][maxn],d[maxn];
int n,m;

int main(){
	
	read(n),read(m);
	for(int i = 1;i <= n;i++){
		read(d[i]);
		for(int j = 1;j <= m;j++) read(c[i][j]);
	}
	
	int S = 1 << m;
	
	memset(f,0x3f,sizeof f); f[0][0] = 0;
	
	for(int i = 1;i <= n;i++){
		for(int j = 0;j < S;j++) f[i][j] = f[i - 1][j] + d[i];
		for(int j = 0;j < S;j++){
			for(int k = 0;k < m;k++){									
				if(j & (1 << k))
					chkmin(f[i][j],f[i][j ^ (1 << k)] + c[i][k + 1]);
			}
		}
		for(int j = 0;j < S;j++) chkmin(f[i][j],f[i - 1][j]);
	}
	
	printf("%d\n",f[n][S - 1]);
	
	return 0;
}
