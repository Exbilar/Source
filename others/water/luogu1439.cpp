#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

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

int A[maxm],B[maxm],tmp[maxm],ddf[maxm],bit[maxm],f[maxm];
int n;

int lowbit(int x){
	return x & -x;
}

void Upt(int k,int v){
	for(int i = k;i <= n;i += lowbit(i)) chkmax(bit[i],v);
}

int Qry(int k){
	int res = 0;
	for(int i = k;i;i -= lowbit(i)) chkmax(res,bit[i]);
	return res;
}

int main(){
	read(n);
	for(int i = 1;i <= n;i++) read(A[i]),tmp[A[i]] = i;
	for(int i = 1;i <= n;i++) read(B[i]),ddf[i] = tmp[B[i]];

	int ans = 0;
	for(int i = 1;i <= n;i++){
		f[i] = Qry(ddf[i] - 1) + 1;
		Upt(ddf[i],f[i]);		
	}
	
	for(int i = 1;i <= n;i++) chkmax(ans,f[i]);
	
	printf("%d\n",ans);
	
	return 0;
}
