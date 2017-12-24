#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: max_element;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1000000 + 10;

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
int n,cas;

int main(){

	read(cas);

	while(cas--){
		read(n);
		for(int i = 1;i <= n;i++) read(A[i]);

		int ans = 0;
		for(int i = 1;i <= n;i++) ans ^= A[i];

		int _max = *max_element(A + 1,A + n + 1);

		if(_max == 1 && ans == 0) puts("John");
		if(_max == 1 && ans != 0) puts("Brother");
		if(_max > 1 && ans == 0) puts("Brother");
		if(_max > 1 && ans != 0) puts("John");
	}
	
	return 0;
}
