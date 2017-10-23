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

static const int maxm = 1000 + 10;
static const int INF = 1 << 30;
static const int MOD = 1e9 + 7;

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

int f[3][maxm][maxm][3];
char A[maxm],B[maxm];
int n,m,K;

int main(){
	read(n),read(m),read(K);
	scanf("%s",A + 1);
	scanf("%s",B + 1);
	
	int cur = 0;
	f[cur][0][0][0] = 1;
	for(int i = 1;i <= n;i++){
		cur ^= 1; f[cur][0][0][0] = 1;
		for(int j = 1;j <= min(i,m);j++){
			for(int k = 1;k <= K;k++){
				f[cur][j][k][0] = f[cur][j][k][1] = 0;
				f[cur][j][k][0] = (f[cur ^ 1][j][k][0] + f[cur ^ 1][j][k][1]) % MOD;
				if(A[i] == B[j]){
					f[cur][j][k][1] = (f[cur ^ 1][j - 1][k - 1][0] + f[cur ^ 1][j - 1][k - 1][1]) % MOD;
					f[cur][j][k][1] = (f[cur][j][k][1] + f[cur ^ 1][j - 1][k][1]) % MOD;
				}
			}
		}
	}
	
	printf("%d\n",(f[cur][m][K][0] + f[cur][m][K][1]) % MOD);
	
	return 0;
}
