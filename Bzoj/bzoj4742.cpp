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

static const int maxm = 1e3 + 10;
static const int INF = 1 << 30;
static const int MOD = 1000000009;

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

int f[maxm][maxm][15],A[maxm],B[maxm];
int n,m,k;

int plus(int x,int y){
	x = (x + y) % MOD;
	return x;
}

int minus(int x,int y){
	x = (x - y) % MOD;
	while(x < 0) x += MOD;
	return x;
}

int main(){
	read(n);read(m);read(k);
	for(int i = 1;i <= n;i++) read(A[i]);
	for(int i = 1;i <= m;i++) read(B[i]);
	
	for(int i = 0;i <= n;i++)
		for(int j = 0;j <= m;j++) f[i][j][0] = 1;

	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			for(int p = 1;p <= k && p <= i && p <= j;p++){
				f[i][j][p] = minus(plus(f[i - 1][j][p],f[i][j - 1][p]),f[i - 1][j - 1][p]);
				if(A[i] > B[j]) f[i][j][p] = plus(f[i][j][p],f[i - 1][j - 1][p - 1]);
			}
		}
	}

	printf("%d\n",(f[n][m][k] + MOD) % MOD);

	return 0;
}
