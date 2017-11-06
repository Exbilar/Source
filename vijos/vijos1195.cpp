#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: map;
using std :: max;
using std :: min;

typedef long long LL;

static const int maxm = 1e6 + 10;
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

int A[maxm],sum[maxm],get[maxm];
int n;

int main(){
	
	read(n);	
	for(int i = 1;i <= n;i++){
		read(A[i]);
		if(A[i] == 1) sum[i] = sum[i - 1] + 1;
		if(A[i] == 0) sum[i] = sum[i - 1] - 1;
	}	
	
	int ans = 0;

	memset(get,-1,sizeof get);
	
	for(int i = 0;i <= n;i++){
		if(get[sum[i] + n] != -1){
			chkmax(ans,i - get[sum[i] + n]);
		}
		else get[sum[i] + n] = i;
	}
	
	printf("%d\n",ans);
	
	return 0;
}
