#include <bits/stdc++.h>

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
static const int maxm = 1e6 + 10;
static const int mod = 1e9 + 7;

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

int fst[maxm],nxt[maxm],to[maxm],size[maxm],sizmax[maxm];
int col[maxm],vis[maxm];
LL cnt[maxm],ans[maxm];
int __cnt__,__sum,rt,n;

void ins(int f,int t) {
	nxt[++__cnt__] = fst[f],to[__cnt__] = t,fst[f] = __cnt__;
	nxt[++__cnt__] = fst[t],to[__cnt__] = f,fst[t] = __cnt__;
}

void getRoot(int x,int fa) {
	size[x] = 1; sizmax[x] = 0;
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(vis[v] || v == fa) continue;
		getRoot(v,x);
		size[x] += size[v];
		chkmax(sizmax[x],size[v]);
	}
	chkmax(sizmax[x],__sum - size[x]);
	if(sizmax[x] < sizmax[rt]) rt = x;
}

int has[maxm],exi[maxm],stk[maxm];
LL __cnt[maxm],__stk[maxm];

int top,tot,tdn,tp;

void modify(int x,int fa,LL lst) {
	LL ddf = lst;
	if(++has[col[x]] == 1) ddf += tdn - cnt[col[x]];
	ans[x] += ddf + tot;
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(v == fa || vis[v]) continue;
		modify(v,x,ddf);
	}
	has[col[x]]--;
}

void getSize(int x,int fa) {
	size[x] = 1;
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(vis[v] || v == fa) continue;
		getSize(v,x);
		size[x] += size[v];
	}
}

void dfs(int x,int fa,LL *cnt) {
	if(!exi[col[x]]) stk[++top] = col[x],exi[col[x]] = 1;
	if(++has[col[x]] == 1) cnt[col[x]] += size[x];
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(vis[v] || v == fa) continue;
		dfs(v,x,cnt);
	}
	has[col[x]]--;
}

void transform(int x) {
	tot = top = 0;
	getSize(x,0); dfs(x,0,cnt);
	for(int i = 1;i <= top;i++) exi[stk[i]] = 0;
	for(int i = 1;i <= top;i++) {
		tot += cnt[stk[i]];
	}
	ans[x] += tot;

	int tp = top;
	for(int i = 1;i <= tp;i++) __stk[i] = stk[i];
	
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(vis[v]) continue;
		
		has[col[x]] = 1; top = 0;
		
		dfs(v,x,__cnt);
		cnt[col[x]] -= size[v]; tot -= size[v];
		for(int i = 1;i <= top;i++) {
			cnt[stk[i]] -= __cnt[stk[i]];
			tot -= __cnt[stk[i]];
		}

		tdn = size[x] - size[v];

		has[col[x]] = 0;
		for(int i = 1;i <= top;i++) exi[stk[i]] = 0;
		
		modify(v,x,0);

		for(int i = 1;i <= top;i++) {
			tot += __cnt[stk[i]];
			cnt[stk[i]] += __cnt[stk[i]];
			__cnt[stk[i]] = 0;
		}
		tot += size[v]; cnt[col[x]] += size[v];
	}
	
	for(int i = 1;i <= tp;i++) cnt[__stk[i]] = 0;
}

void solve(int x) {
	vis[x] = 1; transform(x);
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(vis[v]) continue;
		rt = 0; __sum = size[v];
		getRoot(v,x);
		solve(rt);
	}
}

int main() {

	read(n);
	for(int i = 1;i <= n;i++) read(col[i]);

	int u,v;
	for(int i = 1;i < n;i++) {
		read(u); read(v); ins(u,v);
	}

	sizmax[0] = INF; rt = 0; __sum = n;

	getRoot(1,0);
	solve(rt);

	for(int i = 1;i <= n;i++) printf("%lld\n",ans[i]);

	return 0;
}
