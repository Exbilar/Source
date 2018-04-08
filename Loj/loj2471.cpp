#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: map;
using std :: pair;
using std :: string;
using std :: make_pair;

typedef long long LL;
typedef unsigned long long ull;
typedef pair<LL, LL> pll;
typedef pair<int, int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 100;
static const int base = 131;

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

int n, m, sumB;

int A[maxm][maxm], B[maxm][maxm];

map<ull, int> vis[2], f[2];

struct Hash {
	int hsh[100];

	Hash() { memset(hsh, 0, sizeof hsh); }
	
	ull get() {
		ull res = 0;
		for(int i = 1; i <= n; i++) {
			res = res * base + hsh[i];
		}
		return res;
	}
};

int dfs(Hash st, int cur) {
	ull S = st.get();
	if(vis[cur][S]) return f[cur][S];
	
	vis[cur][S] = 1;
	
	int res = cur ? 0 : INF;
	int trans = 0;
	
	for(int i = 1; i <= n; i++) {
		if((i == 1 || st.hsh[i] < st.hsh[i - 1]) && st.hsh[i] < m) {
			trans = 1;
			
			Hash nxt = st; nxt.hsh[i] += 1;
			int val = A[i][nxt.hsh[i]] + B[i][nxt.hsh[i]];
			
			if(cur) chkmax(res, dfs(nxt, cur ^ 1) + val);
			else chkmin(res, dfs(nxt, cur ^ 1));
		}
	}
	
	return trans ? f[cur][S] = res : 0;
}

int main() {

	read(n); read(m);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			read(A[i][j]);
		}
	}

	for(int i = 1;i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			read(B[i][j]); sumB += B[i][j];
		}
	}

	Hash st;
	printf("%d\n", dfs(st, 1) - sumB);
	
	return 0;
}

	
