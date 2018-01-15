#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 4000 + 10;
static const int maxn = 50 + 10;

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

int ans[maxm],f[maxn][maxn][maxm],g[maxn][maxn][maxm],pos[maxn][maxn][maxm];
int sum[maxn][maxm],L[maxm],R[maxm],C[maxm],tmp[maxm];
int n,m;

void solve(int l,int r,int k){
	if(l > r) return ;
	int t = pos[l][r][k],mid = f[l][r][t];
	ans[mid] = tmp[t];
	solve(l,mid - 1,t),solve(mid + 1,r,t);
}

int main(){
	read(n),read(m);
	for(int i = 1;i <= m;i++){
		read(L[i]),read(R[i]),read(C[i]);
		tmp[i] = C[i];
	}

	std :: sort(tmp + 1,tmp + m + 1);
	int tot = std :: unique(tmp + 1,tmp + m + 1) - tmp - 1;

	for(int i = 1;i <= m;i++){
		C[i] = std :: lower_bound(tmp + 1,tmp + tot + 1,C[i]) - tmp;
	}

	for(int l = n;l >= 1;l--){
		for(int r = l;r <= n;r++){
			
			for(int i = l;i <= r;i++) clr(sum[i]);
			
			for(int i = 1;i <= m;i++){
				if(l <= L[i] && R[i] <= r){
					for(int x = L[i];x <= R[i];x++) sum[x][C[i]]++;
				}
			}
			
			for(int i = l;i <= r;i++)
				for(int x = tot - 1;x >= 1;x--) sum[i][x] += sum[i][x + 1];
			
			for(int x = tot;x >= 1;x--){
				int smax = 0,ddf = 0;
				for(int k = l;k <= r;k++){
					ddf = g[l][k - 1][x] + g[k + 1][r][x] + sum[k][x] * tmp[x];
					if(ddf >= smax) smax = ddf,f[l][r][x] = k;
				}
				
				if(smax >= g[l][r][x + 1]) g[l][r][x] = smax,pos[l][r][x] = x;
				else g[l][r][x] = g[l][r][x + 1],pos[l][r][x] = pos[l][r][x + 1];
			}
			
		}
	}

	printf("%d\n",g[1][n][1]);
	
	solve(1,n,1);
	
	for(int i = 1;i < n;i++) printf("%d ",ans[i]);
	printf("%d\n",ans[n]);

	return 0;
}
