#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 2e3 + 10;

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

int tmp[maxm],SG[maxm],A[maxm],B[maxm];
int n,m;

void getSG(int N){
	for(int i = 1;i <= N;i++){
		clr(tmp); int cur = 0;
		for(int j = 1;B[j] <= i && j <= m;j++) tmp[SG[i - B[j]]] = 1;
		while(tmp[cur]) cur++;
		SG[i] = cur;
	}
}

int main(){
	
	read(n);
	for(int i = 1;i <= n;i++) read(A[i]);
	
	read(m);
	for(int i = 1;i <= m;i++) read(B[i]);
	
	getSG(1000 + 10);

	int ans = 0;
	for(int i = 1;i <= n;i++) ans ^= SG[A[i]];

	if(ans){
		puts("YES");
		for(int i = 1;i <= n;i++){
			for(int j = 1;B[j] <= A[i] && j <= m;j++){
				if((ans ^ SG[A[i]] ^ SG[A[i] - B[j]]) == 0) return printf("%d %d\n",i,B[j]),0;
			}
		}
	}
	else puts("NO");

	return 0;
}
