#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)

using std :: max;
using std :: min;
using std :: set;
using std :: pair;
using std :: make_pair;
using std :: vector;
using std :: queue;
using std :: multiset;
using std :: priority_queue;

typedef long long LL;
typedef pair<int,int> pii;

static const int maxm = 2e2 + 10;
static const int INF = 1 << 30;

template <class T> void read(T &in){
	in = 0; int f = 1 ;char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

template <class T> inline bool chkmax(T &x,T y){
	return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
	return x > y ? x = y,true : false;
}

double C[maxm][maxm],f[maxm][maxm][maxm],g[maxm];
int n,m;

void getC(){
	for(int i = 0;i <= n + m;i++) C[i][0] = 1,C[i][i] = 1;
	for(int i = 1;i <= n + m;i++){
		for(int j = 1;j < i;j++){
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}
}

double fpm(double x,LL k){
	double res = 1;
	while(k){
		if(k & 1) res = res * x;
		x = x * x;
		k >>= 1;
	}
	return res;
}

int main(){

	read(n),read(m);

	getC();
	
	for(int i = 1;i <= m;i++) read(g[i]);
	
	f[0][0][0] = 1;
	
	for(int i = 1;i <= m;i++){
		f[i][0][0] = 1;
		for(int j = 1;j <= n;j++){
			for(int l = 0;l <= j;l++){
				int B = l * g[i],A = (l - 1) * g[i] + 1;
				for(int k = 0;k <= l;k++){
					for(int p = max(A,0);p <= B && p <= j;p++){
						f[i][j][l] += f[i - 1][j - p][k] * C[n - j + p][p];
					}
				}
				for(int p = 0;p < A && p <= j;p++)
					f[i][j][l] += f[i - 1][j - p][l] * C[n - j + p][p];
			}
		}		
	}
	
	double ans = 0.0;
	for(int i = 1;i <= n;i++) ans += f[m][n][i] * i;
	
	printf("%.14lf\n",ans / fpm(m,n));
	
	return 0;
}
