#include <cstdio>
#include <cstring>
#include <algorithm>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: make_pair;

typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 2e6 + 10;
static const int mod = 998244353;

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

int fst[maxm],nxt[maxm],to[maxm],can[maxm],frm[maxm];
int n,m,cnt,cas,isCactus;

void ins(int f, int t) {
	nxt[++cnt] = fst[f],to[cnt] = t,frm[cnt] = f,fst[f] = cnt,can[cnt] = 1;
	nxt[++cnt] = fst[t],to[cnt] = f,frm[cnt] = t,fst[t] = cnt,can[cnt] = 1;
}

int stk[maxm],low[maxm],dfn[maxm],ddf[maxm];
int top;

void tarjan(int x, int fa) {
	low[x] = dfn[x] = ++dfn[0];
	stk[++top] = x;

	bool flag = 0;
	
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(v == fa) continue;
		if(!dfn[v]) {
			tarjan(v, x); chkmin(low[x], low[v]);
			if(low[v] < dfn[x]) {
				if(flag) return isCactus = 0,void();
				flag = 1;
			}
		} else {
			chkmin(low[x], dfn[v]);
			if(dfn[v] < dfn[x]) {
				if(flag) return isCactus = 0,void();
				flag = 1;
			}
		}
	}

	if(dfn[x] == low[x]) {
		while(stk[top + 1] != x) ddf[stk[top--]] = x;
	}	
}

LL h[maxm],f[maxm],g[maxm];
int vis[maxm];
LL ans;

void pretreat() {
	h[0] = 1; h[1] = 1;
	for(int i = 2;i <= 1000000;i++) {
		h[i] = (h[i - 1] + 1LL * (i - 1) * h[i - 2] % mod) % mod;
	}
}

void dfs(int x, int fa) {
	f[x] = 1; g[x] = 0; vis[x] = 1;
	LL tot = 0;
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(!can[u] || v == fa) continue;
		dfs(v, x);
		f[x] = f[x] * g[v] % mod;
		tot++;
	}
	g[x] = (f[x] * h[tot] % mod + f[x] * h[tot - 1] % mod * tot % mod) % mod;
	f[x] = f[x] * h[tot] % mod;
}

void init() {
	read(n); read(m);
	cnt = 0; top = 0; isCactus = 1; ans = 1;
	for(int i = 0;i <= n;i++) {
		vis[i] = 0; fst[i] = 0; ddf[i] = 0;
		dfn[i] = 0; low[i] = 0; stk[i] = 0;
	}
}

void solve() {
	init(); int u,v;
	for(int i = 1;i <= m;i++) read(u),read(v),ins(u,v);
	
	tarjan(1, 0);
	if(!isCactus) return puts("0"),void();

	for(int i = 1;i <= cnt;i++) {
		if(ddf[to[i]] == ddf[frm[i]]) can[i] = 0;
	}
	
	for(int i = 1;i <= n;i++) {
		if(vis[i]) continue;
		dfs(i, 0);
		ans = 1LL * ans * f[i] % mod;
	}
	
	printf("%lld\n",ans);
}

int main() {

	read(cas); pretreat();

	while(cas--) solve();
	
	return 0;
}
