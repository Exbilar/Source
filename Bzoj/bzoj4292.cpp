#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;

template <class T> inline bool chkmax(T &x,T y){
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in){
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

LL k,l,r;

LL F(LL x){
	LL res = 0;
	while(x){
		res += (x % 10) * (x % 10);
		x /= 10;
	}
	return res;
}

LL solve(LL n){
	LL res = 0;
	for(LL i = 0;i <= 1458;i++){
		LL N = k * i;
		if(N > n) break;
		if(F(N) == i) res++;
	}
	return res;
}

int main(){
	//freopen("bzoj4292.in","r",stdin);
	
	read(k),read(l),read(r);

	printf("%lld\n",solve(r) - solve(l - 1));

	return 0;
}
