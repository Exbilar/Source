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

bitset<maxm> ddf[maxm];
int ans[maxm];
int n,m,smin = INF;

void gauss(){
	for(int i = 1;i <= n;i++){
		int pos = i;
		while(pos <= n && !ddf[pos][i]) pos++;
		
		if(pos > n) continue;
		if(pos != i) std :: swap(ddf[pos],ddf[i]);
		
		for(int j = 1;j <= n;j++)
			if(j != i && ddf[j][i]) ddf[j] ^= ddf[i];
	}
}

void dfs(int x,int tot){
	if(tot > smin) return ;
	if(x <= 0) return chkmin(smin,tot),void();
	
	if(ddf[x][x]){
		ans[x] = ddf[x][n + 1];
		for(int i = x + 1;i <= n;i++)
			ans[x] ^= ans[i] & ddf[x][i];
		dfs(x - 1,tot + ans[x]);
	}
	else{
		ans[x] = 1;
		dfs(x - 1,tot + 1);
		ans[x] = 0;
		dfs(x - 1,tot);
	}
}

void print(){
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n + 1;j++){
			printf("%d ",(int) ddf[i][j]);
		}
		putchar(10);
	}
	putchar(10);
}

int main(){
	
	read(n); read(m);

	int x,y;
	
	for(int i = 1;i <= n;i++){
		ddf[i][i] = 1,ddf[i][n + 1] = 1;
	}
	
	for(int i = 1;i <= m;i++){
		read(x),read(y);
		ddf[x][y] = 1,ddf[y][x] = 1;
	}

	gauss();
	print();
	dfs(n,0);
	printf("%d\n",smin);
	
	return 0;
}
