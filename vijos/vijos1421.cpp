#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: max;
using std :: min;

typedef long long LL;

static const int maxm = 1e3 + 10;
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

int w[maxm][maxm],f[maxm][maxm];
int n,m,c;

int main(){
	
	read(n),read(m),read(c);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) read(w[i][j]);

	memset(f,0x3f,sizeof f);
	
	for(int i = 1;i <= m;i++) f[0][i] = 0;
	
	for(int i = 1;i <= n;i++){
		int smin = INF;
		for(int j = 1;j <= m;j++){
			chkmin(f[i][j],f[i - 1][j] + w[i][j]);
			chkmin(smin,f[i - 1][j]);
		}
		for(int j = 1;j <= m;j++) chkmin(f[i][j],smin + w[i][j] + c);
	}
	
	int ans = INF;
	for(int i = 1;i <= m;i++) chkmin(ans,f[n][i]);
	
	printf("%d\n",ans);
	
	return 0;
}
