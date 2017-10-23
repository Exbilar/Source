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

static const int INF = 1 << 30;
static const int maxm = 2e3 + 10;

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

int A[maxm];
double f[maxm][maxm];
int n,m;

int main(){
	int u,v;
	read(n); read(m);
	for(int i = 1;i <= n;i++) read(A[i]);
	
	for(int i = 1;i <= n;i++)
		for(int j = i + 1;j <= n;j++)
			f[i][j] = A[i] > A[j],f[j][i] = A[j] > A[i];
	
	while(m--){
		read(u),read(v);
		
		for(int i = 1;i <= n;i++)
			if(i != u && i != v)
				f[i][u] = f[i][v] = (f[i][u] + f[i][v]) / 2.0,
					f[u][i] = f[v][i] = (f[u][i] + f[v][i]) / 2.0;
		
		f[u][v] = f[v][u] = 0.5;
	}
	
	double ans = 0.0;
	
	for(int i = 1;i <= n;i++)
		for(int j = i + 1;j <= n;j++) ans += f[i][j];
	
	printf("%.7lf\n",ans);
	
	return 0;
}
