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

static const int maxm = 3e3 + 10;
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

int f[maxm][maxm];
int A[maxm],sum[maxm];
int n;

int main(){
	read(n);
	for(int i = n;i >= 1;i--) read(A[i]);
	for(int i = 1;i <= n;i++) sum[i] = sum[i - 1] + A[i];
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			f[i][j] = f[i][j - 1];
			int k = j << 1;
			if(i >= k) f[i][j] = max(f[i][j],sum[i] - f[i - k][k]);
			if(i >= k - 1) f[i][j] = max(f[i][j],sum[i] - f[i - k + 1][k - 1]);
		}
	}
	
	printf("%d\n",f[n][1]);

	return 0;
}
