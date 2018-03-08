#include <cstdio>
#include <cctype>
#include <algorithm>

using std :: max;
using std :: min;

typedef long long LL;

const int maxm = 2e5 + 10;

template <class T> inline bool chkmin(T &x, T y) {
	return x > y ? x = y,true : false;
}

template <class T> inline bool chkmax(T &x, T y) {
	return x < y ? x = y,true : false;
}

template <class T> inline void read(T &in) {
	in = 0; T f = 1; char ch = getchar();
	for(;!isdigit(ch);ch = getchar()) if(ch == '-') f = -1;
	for(;isdigit(ch);ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

LL f[maxm][25],g[maxm][25],ai[maxm],bi[maxm],dis[maxm];
int dpt[maxm];
int n;

int lc(int x) {
	return x << 1;
}

int rc(int x) {
	return x << 1 | 1;
}

int fa(int x) {
	return x >> 1;
}

int LE(int x) {
	return bi[(x << 1) - 1];
}

int RE(int x) {
	return bi[x << 1];
}

int main() {

	read(n);
	for(int i = 1;i <= n;i++) read(ai[i]);
	for(int i = 1;i < n;i++) read(bi[i]);

	for(int i = 1;i <= n;i++) {
		dpt[i] = dpt[fa(i)] + 1;
		dis[i] = dis[fa(i)] + bi[i - 1];
	}

	for(int i = n;i >= 1;i--) {
		for(int j = dpt[i],z = i;j > 1;z = fa(z),j--) {
			int bro = (z & 1) ? z - 1 : z + 1;
			if(lc(i) > n && rc(i) > n) f[i][j] = ai[bro] * (dis[i] + dis[bro] - 2 * dis[fa(z)]);
			else if(rc(i) > n) f[i][j] = f[lc(i)][j] + LE(i) * ai[lc(i)];
			else f[i][j] =
					 min(
						 f[lc(i)][dpt[i] + 1] + LE(i) * ai[lc(i)] + f[rc(i)][j],
						 f[rc(i)][dpt[i] + 1] + RE(i) * ai[rc(i)] + f[lc(i)][j]
						 );
		}
	}

	for(int i = n;i >= 1;i--) {
		for(int j = dpt[i],z = i;j >= 0;z = fa(z),j--) {
			if(lc(i) > n && rc(i) > n) g[i][j] = ai[z] * (dis[i] - dis[z]);
			else if(rc(i) > n) g[i][j] = g[lc(i)][j] + ai[lc(i)] * LE(i);
			else g[i][j] =
					 min(
						 f[lc(i)][dpt[i] + 1] + LE(i) * ai[lc(i)] + g[rc(i)][j],
						 f[rc(i)][dpt[i] + 1] + RE(i) * ai[rc(i)] + g[lc(i)][j]
						 );
		}
	}

	LL ans = g[1][0];
	
	for(int i = 2;i <= n;i++) {
		LL res = g[i][dpt[i] - 1];
		int ftr = fa(i),bro = (i & 1) ? i - 1 : i + 1,cur = i;
		while(ftr) {
			if(rc(ftr) <= n) res += g[bro][dpt[ftr] - 1] + bi[bro - 1] * ai[bro];
			else res += bi[ftr - 1] * ai[fa(ftr)];
			cur = ftr; ftr = fa(cur); bro = (cur & 1) ? cur - 1 : cur + 1;
		}
		chkmin(ans, res);
	}

	printf("%lld\n", ans);

	return 0;
}
