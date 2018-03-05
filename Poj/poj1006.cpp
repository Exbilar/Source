#include <cstdio>
#include <algorithm>

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

int m[maxm],A[maxm];
int n;

int exgcd(int &x,int &y,int a,int b){
	if(!b){
		x = 1,y = 0;
		return a;
	}
	exgcd(y,x,b,a % b);
	y -= a / b * x;
}

int CRT(int A[],int m[],int n){
	int M = 1,res = 0;
	for(int i = 1;i <= n;i++) M *= m[i];
	for(int i = 1;i <= n;i++){
		int x,y;
		int Mi = M / m[i];
		exgcd(x,y,Mi,m[i]);
		res = (res + Mi * x * A[i]) % M;
	}
	while(res < 0) res += M;
	return res;
}

int main(){
	int p,e,i,d; int cas = 0;
	while(scanf("%d%d%d%d",&p,&e,&i,&d) != EOF){
		if(p == -1 && e == -1 && i == -1 && d == -1) break;
		A[1] = p,A[2] = e,A[3] = i,A[4] = d;
		m[1] = 23,m[2] = 28,m[3] = 33;
		int ans = CRT(A,m,3);
		if(ans <= d) ans += 21252;
		printf("Case %d: the next triple peak occurs in %d days.\n",++cas,ans - d);
	}
	
	return 0;
}
