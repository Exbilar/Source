#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: max;
using std :: min;
using std :: vector;

typedef long long LL;

static const int maxm = 2e6 + 10;
static const int INF = 1 << 30;
static const LL oo = 1LL << 63;

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

vector<int> vec[maxm];
int A[maxm];
int n,m;

int main(){
	read(n),read(m);
	for(int i = 1;i <= n;i++) read(A[i]),vec[A[i]].push_back(i);
	
	while(m--){
		int opt,l,r,c,x;
		read(opt);
		if(opt == 1){
			read(l),read(r),read(c);
			int posl =
				std :: lower_bound(vec[c].begin(),vec[c].end(),l) - vec[c].begin();
			int posr = 
				std :: upper_bound(vec[c].begin(),vec[c].end(),r) - vec[c].begin() - 1;
			printf("%d\n",posr - posl + 1);
		}
		if(opt == 2){
			read(x);
			if(A[x] == A[x + 1]) continue;
			int posx =
				std :: lower_bound(vec[A[x]].begin(),vec[A[x]].end(),x) - vec[A[x]].begin();
			int posy =
				std :: lower_bound(vec[A[x + 1]].begin(),vec[A[x + 1]].end(),x + 1) - vec[A[x + 1]].begin();
			vec[A[x]][posx] = x + 1;
			vec[A[x + 1]][posy] = x;
			std :: swap(A[x],A[x + 1]);
		}
	}
	
	return 0;
}
