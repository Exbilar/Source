#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 2000 + 10;

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

int SG[maxm];
int f[maxm],tmp[maxm];

void getSG(int N){
	clr(SG); int cur;
	for(int i = 1;i <= N;i++){
		clr(tmp),cur = 0;
		for(int j = 1;f[j] <= i;j++) tmp[SG[i - f[j]]] = 1;
		while(tmp[cur]) cur++;
		SG[i] = cur;
	}
}

int main(){
	f[1] = 1,f[2] = 1;
	for(int i = 3;i <= 20;i++) f[i] = f[i - 1] + f[i - 2];
	getSG(1000);

	int n,m,k;
	while(scanf("%d%d%d",&n,&m,&k) != EOF){
		if(n == 0 && m == 0 && k == 0) break;
		if(SG[n] ^ SG[m] ^ SG[k]) puts("Fibo");
		else puts("Nacci");
	}

	return 0;
}
