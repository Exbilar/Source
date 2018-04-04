#include <bits/stdc++.h>

using std :: max;
using std :: min;

typedef long long LL;

template <class T> void read(T &in) {
	in = 0; T f = 1; char ch = getchar();
	for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for(; isdigit(ch); ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

const int maxm = 300 + 10;
const int maxn = 90000 + 10;
const int mod = 1e9 + 7;

int wi[maxm], f[maxm][maxn], g[maxm][maxn];
int n, m, k, sum;

int add(int x, int y) {
	return x + y >= mod ? x + y - mod : x + y;
}

int dec(int x, int y) {
	return x - y < 0 ? x - y + mod : x - y;
}

int fpm(int x, int k) {
	int res = 1;
	while(k) {
		if(k & 1) res = 1LL * res * x % mod;
		x = 1LL * x * x % mod;
		k >>= 1;
	}
	return res;
}

int getInv(int x) {
	return fpm(x, mod - 2);
}

int calc(int n, int m) {
	int facn = 1, facm = 1, facnm = 1;
	for(int i = 1; i <= n; i++) facn = 1LL * facn * i % mod;
	for(int i = 1; i <= m; i++) facm = 1LL * facm * i % mod;
	for(int i = 1; i <= n - m; i++) facnm = 1LL * facnm * i % mod;
	return 1LL * facn * getInv(facm) % mod * getInv(facnm) % mod;
}

int ans;

void dfs(int cur, int rem) {
	if(cur == n) return ans = (ans + 1) % mod, void();
	if(cur <= m) {
		for(int i = 0; i <= min(wi[cur], rem); i++) dfs(cur + 1, rem - i);
		return ;
	}
	for(int i = 0; i <= rem; i++) dfs(cur + 1, rem - i);
}

int main() {

	read(n); read(m); read(k);
	for(int i = 1; i <= m; i++) read(wi[i]), sum += wi[i];

	for(int i = 0; i <= sum; i++) g[0][i] = 1;

	for(int i = 1; i <= m; i++) {
		for(int j = 0; j <= sum; j++) {
			f[i][j] = add(f[i][j], dec(g[i - 1][j], j < wi[i] + 1 ? 0 : g[i - 1][j - wi[i] - 1]));
			g[i][j] = add(g[i][j - 1], f[i][j]);
		}
	}

	int C = calc(k + (n - m - 1), n - m - 1);

	for(int i = 0; i <= min(k, sum); i++) {
		ans = add(ans, 1LL * f[m][i] * C % mod);
		C = 1LL * C * (k - i) % mod * getInv(k - i + n - m - 1) % mod;
	}
	
	printf("%d\n", ans);

	return 0;
}
