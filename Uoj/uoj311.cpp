#include <cstdio>
#include <algorithm>

using std :: max;
using std :: min;

template <class T> bool chkmax(T &x, const T y) {
	return x < y ? x = y, true : false;
}

template <class T> bool chkmin(T &x, const T y) {
	return x > y ? x = y, true : false;
}

const int maxm = 500;
const int mod = 998244353;

int f[maxm][maxm], pwr[maxm][maxm], wi[maxm];
int n, k;

inline int add(int x, int y) {
	return x + y >= mod ? x + y - mod : x + y;
}

inline int dec(int x, int y) {
	return x - y < 0 ? x - y + mod : x - y;
}

int main() {
	scanf("%d%d", &n ,&k);

	for(int i = 1; i <= n; i++) scanf("%d", &wi[i]);
	for(int i = 1; i <= n; i++) {
		pwr[i][0] = 1;
		for(int j = 1; j <= k; j++)
			pwr[i][j] = 1LL * pwr[i][j - 1] * wi[i] % mod;
	}

	for(int i = 0; i < k; i++) {
		for(int j = 0; j <= n; j++) {
			f[i][j] = !i ? 1 : 1LL * f[i - 1][j] * j % mod;
		}
	}

	for(int i = k; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			for(int p = 1; p <= i; p++) {
				int tot = min(p, i - k + 1) - max(0, p - k);
				f[i][j] = add(f[i][j], 1LL * f[p - 1][j - 1] * pwr[j][tot] % mod * f[i - p][j] % mod);
			}
			f[i][j] = add(f[i][j], f[i][j - 1]);
		}
	}

	printf("%d\n", f[n][n]);

	return 0;
}
