#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: string;
using std :: make_pair;

typedef long long LL;
typedef pair<LL, LL> pll;
typedef pair<int, int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 2e6 + 10;
static const int mod = 1e9 + 7;

template <class T> inline bool chkmax(T &x, T y) {
    return x < y ? x = y, true : false;
}

template <class T> inline bool chkmin(T &x, T y) {
    return x > y ? x = y, true : false;
}

template <class T> inline void read(T &in) {
    in = 0; char ch = getchar(); T f = 1;
    for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

template <class T> inline void write(T out) {
	if(out >= 10) write(out / 10);
	putchar(out % 10 + '0');
}

string procStatus() {
	std :: ifstream t("/proc/self/status");
	return string(std :: istreambuf_iterator<char> (t),
				  std :: istreambuf_iterator<char> ());
}

int A[maxm], f[maxm], bin[maxm];
int n;

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

int main() {

	freopen("asd.in", "r", stdin);
	
	read(n);
	for(int i = 1; i <= n; i++) read(A[i]), f[A[i]]++;

	for(int i = 20; i >= 0; i--) {
		for(int j = 0; j <= 1000000; j++) {
			if(j >> i & 1) {
				f[j ^ (1 << i)] = add(f[j ^ (1 << i)], f[j]);
			}
		}
	}

	int ans = 0;

	for(int i = 0; i < (1 << 20); i++) {
		int xi = __builtin_popcount(i);
		if(xi & 1) ans = dec(ans, fpm(2, f[i]));
		else ans = add(ans, fpm(2, f[i]));
	}

	printf("%d\n", ans);

	return 0;
}
