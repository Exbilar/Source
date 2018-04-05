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
static const int maxm = 1e5 + 10;

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
	putchar(out % 10 - '0');
}

string procStatus() {
	std :: ifstream t("/proc/self/status");
	return string(std :: istreambuf_iterator<char> (t),
				  std :: istreambuf_iterator<char> ());
}

int fst[maxm], nxt[maxm], to[maxm];
int A[maxm], v[maxm], idx[maxm], rnk[maxm], ftr[maxm], ans[maxm];
int size[maxm];

short S[maxm][100 + 1];

int cnt, n, m, B, L;

struct Opt {
	int u, v, opt;
}q[maxm];

bool cmp(const int &x, const int &y) {
	return v[x] < v[y];
}

void ins(int f, int t) {
	nxt[++cnt] = fst[f], to[cnt] = t, fst[f] = cnt;
}

int find(int x) {
	return x == ftr[x] ? x : find(ftr[x]);
}

int query(int x, int y) {
	x = find(x); int cur, res;
	for(cur = 0; cur <= B; cur++) {
		if(y - S[x][cur] <= 0) break;
		y -= S[x][cur];
	}
	
	if(cur > B || y - S[x][cur] > 0) return -1;

	res = cur * L + 1;
	while(y--) {
		while(x != find(v[res])) res++;
		res += y > 0;
	}
	
	return res;
}

void dfs(int x) {
	if(q[x].opt == 1) {
		int fx = find(q[x].u), fy = find(q[x].v);
		if(fx == fy) {
			for(int u = fst[x]; u; u = nxt[u]) dfs(to[u]);
			return ;
		}
		
		if(size[fx] > size[fy]) std :: swap(fx, fy);
		ftr[fx] = fy, size[fy] += size[fx];
		for(int i = 0; i <= B; i++) S[fy][i] += S[fx][i];

		for(int u = fst[x]; u; u = nxt[u]) dfs(to[u]);

		for(int i = 0; i <= B; i++) S[fy][i] -= S[fx][i];
		ftr[fx] = fx; size[fy] -= size[fx];
	} else {
		if(q[x].opt == 3) ans[x] = query(q[x].u, q[x].v);
		for(int u = fst[x]; u; u = nxt[u]) dfs(to[u]);
	}
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("asd.in", "r", stdin);
#endif
	
	read(n); read(m);
	for(int i = 1; i <= n; i++) read(A[i]), v[i] = A[i], idx[i] = i;

	std :: sort(A + 1, A + n + 1);
	std :: sort(idx + 1, idx + n + 1, cmp);
	for(int i = 1; i <= n; i++) rnk[idx[i]] = i, v[i] = idx[i];

	B = min(100, (int) sqrt(n * log2(n)));
	L = (int) ceil(n * 1.0 / B);
	
	for(int i = 1; i <= m; i++) {
		read(q[i].opt);
		if(q[i].opt == 2) {
			read(q[i].u);
			ins(q[i].u, i);
		} else {
			read(q[i].u); read(q[i].v);
			ins(i - 1, i);
		}
	}

	for(int i = 1; i <= n; i++) {
		ftr[i] = i; size[i] = 1;
		S[i][(rnk[i] - 1) / L] += 1;
	}

	dfs(0);

	for(int i = 1; i <= m; i++) {
		if(q[i].opt == 3) printf("%d\n", ans[i] == -1 ? -1 : A[ans[i]]);
	}

	std :: cerr << procStatus() << std :: endl;
	
	return 0;
}
