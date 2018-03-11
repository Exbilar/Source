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
static const int maxm = 2e5 + 10;

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

string procStatus(){
    std :: ifstream t("/proc/self/status");
    return string(std :: istreambuf_iterator<char> (t),
				  std :: istreambuf_iterator<char> ());
}

LL f[maxm], ai[maxm];
int lst[maxm], pos[maxm];
int n, m, k;

LL ans;

int main() {

	read(n); read(m); read(k);
	int S = max((int) 2, (int) sqrt(n));
	for(int i = 1;i <= n;i++) read(ai[i]);

	memset(f, 0x3f3f3f, sizeof f);
	
	for(int i = 1;i <= S;i++) {
		for(int j = 1;i + j <= n;j++) {
			chkmin(f[j], min(f[j + 1], 1LL * abs(ai[i + j] - ai[j])));
			if(i + 1 >= k) chkmax(ans, 1LL * f[j] * i);
		}
	}

	chkmax(S, k - 1);
	int Lim = m / (S - 1);

	for(int i = 1;i <= n;i++) {
		int posmax = 0;
		for(int j = 0;j <= Lim;j++) {                   // j : s(l, r)
			if(ai[i] - j >= 1) chkmax(pos[j], lst[ai[i] - j]);
			if(ai[i] + j <= m) chkmax(pos[j], lst[ai[i] + j]);
			if(pos[j] > posmax && i - posmax > S)
				chkmax(ans, 1LL * j * (i - posmax - 1));
			chkmax(posmax, pos[j]);
		}
		lst[ai[i]] = i;
	}

	printf("%lld\n", ans);

	return 0;
}
