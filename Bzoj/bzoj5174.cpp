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
static const int maxm = 1e6 + 10;

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

int fst[maxm],nxt[maxm],to[maxm],f[maxm];
int cnt,n;

void ins(int f, int t) {
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

void dfs(int x, int fa, int k) {
	int tot = 0;
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(v == fa) continue;
		tot++;
	}
	
	f[x] = tot - k;
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(v == fa) continue;
		dfs(v, x, k);
		f[x] += f[v];
	}
	chkmax(f[x], 0);
}

int main() {

	read(n);
	int u, v;
	for(int i = 1;i < n;i++) read(u), read(v), ins(u, v);

	int l = 0, r = n, ans = n;

	while(l <= r) {
		int mid = (l + r) >> 1;
		dfs(1, 0, mid);
		if(f[1] == 0) ans = mid, r = mid - 1;
		else l = mid + 1;
	}

	printf("%d\n", ans);

	return 0;
}
