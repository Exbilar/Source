#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)

using std :: max;
using std :: min;
using std :: pair;
using std :: make_pair;
using std :: vector;
using std :: queue;
using std :: priority_queue;

typedef long long LL;
typedef pair<int,int> pii;

static const int maxm = 2e3 + 10;
static const int INF = 1 << 30;
static const int mod = 1e9 + 7;

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

int A[maxm],f[maxm][maxm];
int n,k;

int main(){
	read(n); read(k);
	for(int i = 1;i <= n;i++) f[1][i] = 1;
	
	for(int i = 2;i <= k;i++){
		for(int j = 1;j <= n;j++){
			for(int k = 1;k * k <= j;k++){
				if(j % k == 0){
					f[i][j] = (f[i][j] + f[i - 1][k]) % mod;
					int x = j / k;
					if(x == k) continue;
					f[i][j] = (f[i][j] + f[i - 1][x]) % mod;
				}
			}
		}
	}

	int ans = 0;
	for(int i = 1;i <= n;i++) ans = (ans + f[k][i]) % mod;

	printf("%d\n",ans);
	
	return 0;
}
