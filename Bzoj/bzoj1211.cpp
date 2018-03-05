#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;

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

LL d[maxm],fac[maxm],prm[maxm],npr[maxm],num[maxm];
LL cnt,n,tot;

void getPrime(int N){
	for(int i = 2;i <= N;i++){
		if(!npr[i]) prm[++cnt] = i;
		for(int j = 1;j <= cnt && i * prm[j] <= N;j++){
			npr[i * prm[j]] = 1;
			if(i % prm[j] == 0) break;
		}
	}
}

void solve(int x,int f){
	for(int i = 1;i <= cnt;i++){
		if(x < prm[i]) break;
		while(x % prm[i] == 0) x /= prm[i],num[i] += f;
	}
}

LL fpm(LL x,LL k){
	LL res = 1;
	while(k){
		if(k & 1) res = res * x;
		x = x * x;
		k >>= 1;
	}
	return res;
}

int main(){

	read(n);

	getPrime(n + 10);
	
	fac[0] = 1;
	for(int i = 1;i <= n;i++) fac[i] = fac[i - 1] * i;
	
	for(int i = 1;i <= n;i++) read(d[i]),tot += d[i] - 1;
	
	if(n == 1 && d[1] != 0) return puts("0"),0;
	else if(n == 1) return puts("1"),0;
	
	if(tot != n - 2) return puts("0");

	for(int i = 1;i <= n;i++)
		if(!d[i]) return puts("0"),0;

	solve(fac[n - 2],1);
	for(int i = 1;i <= n;i++) solve(fac[d[i] - 1],-1);

	LL ans = 1;
	for(int i = 1;i <= cnt;i++) ans *= fpm(prm[i],num[i]);

	printf("%lld\n",ans);
	
	return 0;
}
