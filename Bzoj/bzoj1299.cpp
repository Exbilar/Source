#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1000 + 10;

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

int A[maxm];
int n;

bool solve(){
	int lmt = 1 << n;
	for(int i = 1;i < lmt;i++){
		int SG = 0;
		for(int j = 0;(1 << j) <= i;j++)
			if((1 << j) & i) SG ^= A[j + 1];
		if(!SG) return false;
	}
	return true;
}

int main(){
	
	int cas = 10;
	while(cas--){
		read(n);
		for(int i = 1;i <= n;i++) read(A[i]);
		puts(solve() ? "YES" : "NO");
	}

	return 0;
}
