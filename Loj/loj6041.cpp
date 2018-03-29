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
using std :: vector;
using std :: make_pair;

typedef long long LL;
typedef pair<LL, LL> pll;
typedef pair<int, int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 1e6 + 10;

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

template <class T> inline void write(T out) {
	if(out >= 10) write(out / 10);
	putchar(out % 10 + '0');
}

string procStatus(){
    std :: ifstream t("/proc/self/status");
    return string(std :: istreambuf_iterator<char> (t),
				  std :: istreambuf_iterator<char> ());
}

int n, m;

char str[maxm];

namespace Suffix_Automaton {
	int len[maxm], fail[maxm], ch[maxm][2], rht[maxm], idx[maxm];
	int lst, sz, rt;

	void init() {
		sz = 0; rt = lst = ++sz;
		len[rt] = 0; fail[rt] = 0;
	}
	
	void insert(int i, int v) {
		int x = ++sz, cur = lst; idx[x] = i;
		len[x] = len[lst] + 1, rht[x] = 1, lst = x;
		
		while(cur && !ch[cur][v]) ch[cur][v] = x, cur = fail[cur];
		if(!cur) return fail[x] = rt, void();
		
		int pos = ch[cur][v];
		if(len[pos] == len[cur] + 1) return fail[x] = pos, void();
		
		int clone = ++sz;
		fail[clone] = fail[pos];
		len[clone] = len[cur] + 1;
		memcpy(ch[clone], ch[pos], sizeof ch[pos]);
		
		fail[x] = fail[pos] = clone;
		while(cur && ch[cur][v] == pos) ch[cur][v] = clone, cur = fail[cur];
	}
	
}

namespace SMT {
	int E[maxm], lc[maxm], rc[maxm];
	int rt, sz;

	void insert(int &x, int l, int r, int pos, int v) {
		if(!x) x = ++sz; E[x] += v;
		if(l == r) return ;
		int mid = (l + r) >> 1;
		if(pos <= mid) insert(lc[x], l, mid, pos, v);
		else insert(rc[x], mid + 1, r, pos, v);
	}

	int findL(int x, int l, int r, int pos) {
		if(E[x] == 0 || l > pos) return  0;
		if(l == r) return l;
		int mid = (l + r) >> 1;
		if(r <= pos) {
			if(!E[rc[x]]) return findL(lc[x], l, mid, pos);
			return findL(rc[x], mid + 1, r, pos);
		}
		int res = findL(rc[x], mid + 1, r, pos);
		if(res) return res;
		return findL(lc[x], l, mid, pos);
	}

	int findR(int x, int l, int r, int pos) {
		if(E[x] == 0 || r < pos) return 0;
		if(l == r) return l;
		int mid = (l + r) >> 1;
		if(l >= pos) {
			if(!E[lc[x]]) return findR(rc[x], mid + 1, r, pos);
			return findR(lc[x], l, mid, pos);
		}
		int res = findR(lc[x], l, mid, pos);
		if(res) return res;
		return findR(rc[x], mid + 1, r, pos);
	}

}

int fst[maxm], nxt[maxm], to[maxm], size[maxm], ftr[maxm], dpt[maxm];
int cnt;

void ins(int f, int t) {
	nxt[++cnt] = fst[f], to[cnt] = t, fst[f] = cnt;
}

void build() {
	using namespace Suffix_Automaton;
	for(int i = 1; i <= sz; i++) {
		if(ftr[i] = fail[i]) ins(fail[i], i);
		size[i] = 1; dpt[i] = len[i];
	}
}

int OP[maxm], ED[maxm], pos[maxm], son[maxm];

vector<pii> ddf[maxm];

void dfs1(int x) {
	pos[OP[x] = ++OP[0]] = x;
	for(int u = fst[x]; u; u = nxt[u]) {
		int v = to[u];
		dfs1(v);
		size[x] += size[v];
		if(size[son[x]] < size[v]) son[x] = v;
	}
	ED[x] = OP[0];
}

void Insert(int x, int v) {
	int L = SMT :: findL(1, 1, n, x - 1);
	int R = SMT :: findR(1, 1, n, x + 1);
	if(L) ddf[L].push_back(make_pair(x, v));
	if(R) ddf[x].push_back(make_pair(R, v));
	SMT :: insert(SMT :: rt, 1, n, x, 1);
}

void dfs2(int x, int chain) {
	using Suffix_Automaton :: idx;
	
	for(int u = fst[x]; u; u = nxt[u])
		if(to[u] != son[x]) dfs2(to[u], 0);
	
	if(son[x]) dfs2(son[x], 1);

	for(int u = fst[x]; u; u = nxt[u]) {
		int v = to[u];
		if(v == son[x]) continue;
		for(int i = OP[v]; i <= ED[v]; i++) {
			if(idx[pos[i]]) Insert(idx[pos[i]], dpt[x]);
		}
	}
	
	if(idx[x]) Insert(idx[x], dpt[x]);
	
	if(chain == 0) {
		for(int i = OP[x]; i <= ED[x]; i++) {
			if(idx[pos[i]]) SMT :: insert(SMT :: rt, 1, n, idx[pos[i]], -1);
		}
	}
}

struct Query {
	int l, r, id;
	bool operator < (const Query &rhs) const {
		return l > rhs.l;
	}
}q[maxm];

int ans[maxm], bit[maxm];

int lowbit(int x) {
	return x & -x;
}

void Upt(int k, int v) {
	for(int i = k; i <= n; i += lowbit(i)) chkmax(bit[i], v);
}

int Qry(int k) {
	int res = 0;
	for(int i = k; i; i -= lowbit(i)) chkmax(res, bit[i]);
	return res;
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("loj6041.in", "r", stdin);
	freopen("loj6041.out", "w", stdout);
#endif
	
	read(n); read(m); scanf("%s", str);

	Suffix_Automaton :: init();
	for(int i = 0; i < n; i++) {
		Suffix_Automaton :: insert(i + 1, str[i] - '0');
	}

	build(); dfs1(1); dfs2(1, 1);

	for(int i = 1; i <= m; i++) read(q[i].l), read(q[i].r), q[i].id = i;

	std :: sort(q + 1, q + m + 1);

	int cur = n;
	
	for(int i = 1; i <= m; i++) {
		while(cur >= q[i].l) {
			for(int j = 0; j < (int) ddf[cur].size(); j++) {
				Upt(ddf[cur][j].px, ddf[cur][j].py);
			}
			cur--;
		}
		ans[q[i].id] = Qry(q[i].r);
	}

	for(int i = 1; i <= m; i++) {
		printf("%d\n", ans[i]);
	}
	
	return 0;
}
