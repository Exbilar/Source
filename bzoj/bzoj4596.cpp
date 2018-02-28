#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: vector;
using std :: make_pair;

typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 20 + 5;
static const int mod = 1e9 + 7;

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

int edge[maxm][maxm * maxm][2],deg[maxm][maxm];
int E[maxm][maxm];
int n;

int fpm(int x,int k) {
	int res = 1;
	while(k) {
		if(k & 1) res = 1LL * res * x % mod;
		x = 1LL * x * x % mod;
		k >>= 1;
	}
	return res;
}

int gauss(int n) {
	
	int pos;
	for(int i = 1;i <= n;i++) {
		for(pos = i;pos <= n && !E[pos][i];pos++);
		if(pos >= n + 1) return 0;
		
		for(int j = 1;j <= n;j++) std :: swap(E[pos][j],E[i][j]);
		
		const int inv = fpm(E[i][i],mod - 2);
		
		for(int k = 1;k <= n;k++) {
			if(k == i) continue;
			const int cur = 1LL * E[k][i] * inv % mod;
			for(int j = 1;j <= n;j++) E[k][j] = (E[k][j] - 1LL * E[i][j] * cur % mod + mod) % mod;
		}
		
	}
	
	int res = 1;
	for(int i = 1;i <= n;i++) {
		res = 1LL * res * E[i][i] % mod;
	}
	return res;
}

int main() {

	int ans = 0;
	
	read(n);
	for(int i = 1;i < n;i++) {
		read(edge[i][0][0]);
		for(int j = 1;j <= edge[i][0][0];j++) {
			read(edge[i][j][0]),read(edge[i][j][1]);
		}
	}

	for(int i = 1;i < n;i++) {
		for(int j = 1;j <= edge[i][0][0];j++) {
			deg[i][edge[i][j][0]]--; deg[i][edge[i][j][1]]--;
		}
		for(int j = 1;j < n;j++) deg[i][j] = (deg[i][j] + mod) % mod;
	}

	for(int i = 1;i < n;i++) {
		int tot = edge[i][0][0]; edge[i][0][0] = 0;
		for(int j = 1;j <= tot;j++) {
			if(edge[i][j][0] != n && edge[i][j][1] != n) {
				edge[i][0][0]++;
				edge[i][edge[i][0][0]][0] = edge[i][j][0];
				edge[i][edge[i][0][0]][1] = edge[i][j][1];
			}
		}
	}

	for(int i = 0;i < (1 << (n - 1));i++) {
		memset(E,0,sizeof E);
		bool xi = 0;
		for(int j = 1;j < n;j++) {
			if((i >> (j - 1)) & 1) {
				for(int k = 1;k <= edge[j][0][0];k++) {
					E[edge[j][k][0]][edge[j][k][1]]++;
					E[edge[j][k][1]][edge[j][k][0]]++;
				}
				for(int k = 1;k <= n - 1;k++) {
					E[k][k] = (E[k][k] + deg[j][k]) % mod;
				}
				xi ^= 1;
			}
		}

		int res = gauss(n - 1);
		if(xi) ans = (ans - res + mod) % mod;
		else ans = (ans + res) % mod;
	}

	printf("%d\n",ans);
	
	return 0;
}
