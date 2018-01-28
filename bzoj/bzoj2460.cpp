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

struct Node{
	LL x,y;
	bool operator < (const Node &rhs) const {
		return y > rhs.y;
	}
}A[maxm];

LL bin[maxm],bas[maxm];
int n;

int main(){
	read(n);
	for(int i = 1;i <= n;i++) read(A[i].x),read(A[i].y);

	bin[0] = 1;
	for(int i = 1;i <= 63;i++) bin[i] = bin[i - 1] << 1;

	std :: sort(A + 1,A + n + 1);

	LL ans = 0;
	
	for(int i = 1;i <= n;i++){
		for(int j = 63;j >= 0;j--){
			if(A[i].x & bin[j]){
				if(!bas[j]){
					bas[j] = i; break;
				}
				else A[i].x ^= A[bas[j]].x;
			}
		}
		if(A[i].x) ans += A[i].y;
	}

	printf("%lld\n",ans);

	return 0;
}
