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
static const int maxm = 1024 * 1024 + 10;
static const int Lim = 1e6 + 5;

template <class T> inline bool chkmax(T &x, T y) {
    return x < y ? x = y, true : false;
}

template <class T> inline bool chkmin(T &x, T y) {
    return x > y ? x = y, true : false;
}

template <class T> inline void read (T &in) {
    in = 0; char ch = getchar(); T f = 1;
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

string procStatus(){
    std :: ifstream t("/proc/self/status");
    return string(std :: istreambuf_iterator<char> (t),
				  std :: istreambuf_iterator<char> ());
}

LL bit[maxm][2], ai[maxm], sum[maxm], bin[100];
int n;

int lowbit(int x) {
	return x & -x;
}

void Upt(int k, int v, int p) {
	for(int i = k; i <= Lim; i += lowbit(i)) bit[i][p] += v;
}

LL Qry(int k, int p) {
	LL res = 0;
	for(int i = k; i; i -= lowbit(i)) res += bit[i][p];
	return res;
}

void clear() {
	memset(bit, 0, sizeof bit);
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("bzoj4888.in", "r", stdin);
#endif
	
	read(n);
	for(int i = 1; i <= n; i++) {
		read(sum[i]); sum[i] += sum[i - 1];
	}

	bin[0] = 1;
	for(int i = 1; i <= 20; i++) bin[i] = bin[i - 1] << 1;

	LL ans = 0;
	
	for(int w = 0; w <= 20; w++) {
		if(bin[w] > sum[n]) break;
		clear(); Upt(0 + 1, 1, 0);
		LL res = 0;
		for(int i = 1; i <= n; i++) {
			int k = sum[i] & bin[w];
			if(k) res += Qry(ai[i] + 1, 0) + Qry(Lim, 1) - Qry(ai[i] + 1, 1);
			else  res += Qry(ai[i] + 1, 1) + Qry(Lim, 0) - Qry(ai[i] + 1, 0);
			Upt(ai[i] + 1, 1, k != 0);
			ai[i] |= (k != 0) * bin[w];
		}
		ans |= bin[w] * (res & 1);
	}

	printf("%lld\n", ans);

	return 0;
}
