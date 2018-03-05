#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: bitset;

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

bitset<maxm> A[maxm];
int n,m,ans,tmp;

void gauss(){
	int cur = 0;
	for(int i = 1;i <= n;i++){
		int pos = cur + 1;
		while(!A[pos][i] && pos <= m) pos++;
		if(pos == m + 1) return ans = -1,void();
		else chkmax(ans,pos);
		std :: swap(A[pos],A[++cur]);
		for(int k = 1;k <= m;k++)
			if(k != cur && A[k][i]) A[k] ^= A[cur];
	}
}

int main(){
	
	read(n),read(m);
	for(int i = 1;i <= m;i++){
		for(int j = 1;j <= n;j++) scanf("%1d",&tmp),A[i][j] = tmp;
		scanf("%d",&tmp); A[i][n + 1] = tmp;
	}

	gauss();
	if(ans == -1) return puts("Cannot Determine"),0;

	printf("%d\n",ans);
	for(int i = 1;i <= n;i++)
		if(A[i][n + 1]) puts("?y7M#");
		else puts("Earth");

	return 0;
}
