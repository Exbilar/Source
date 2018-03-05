#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: make_pair;

typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 1e5 + 10;

template <class T> inline bool chkmax(T &x, T y) {
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x, T y) {
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in) {
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if (ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

int A[maxm],B[maxm],posA[maxm],posB[maxm],bit[maxm];
int n;

inline int lowbit(RG int x) {
	return x & -x;
}

inline void Upt(RG int k,RG int v) {
	for(RG int i = k;i <= n;i += lowbit(i)) chkmax(bit[i],v);
}

inline int Qry(RG int k) {
	RG int res = 0;
	for(RG int i = k;i;i -= lowbit(i)) chkmax(res,bit[i]);
	return res;
}

int main() {

	read(n);
	for(RG int i = 1;i <= n;i++) read(A[i]),posA[A[i]] = i;
	for(RG int i = 1;i <= n;i++) read(B[i]),posB[B[i]] = i;

	for(RG int i = 1;i <= n;i++) {
		if(Qry(posA[i]) > posB[i]) return puts("NO"),0;
		Upt(posA[i],posB[i]);
	}

	puts("YES");
	
	return 0;
}
