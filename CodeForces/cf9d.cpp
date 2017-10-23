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

static const int maxm = 2e3 + 10;
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

LL f[maxm][maxm],sum[maxm];
int n,h;

int main(){
	read(n),read(h); f[0][0] = 1;
	
	for(int i = 1;i <= n;i++){
		for(int j = 0;j <= n;j++){
			for(int k = 0;k < j;k++){
				f[i][j] += 2 * f[i - 1][k] * sum[j - k - 1];
				f[i][j] += f[i - 1][k] * f[i - 1][j - k - 1];
			}
		}
		for(int j = 0;j <= n;j++) sum[j] += f[i - 1][j];
	}
	
	LL ans = 0;
	for(int i = h;i <= n;i++) ans += f[i][n];
	
	printf("%lld\n",ans);

	return 0;
}
