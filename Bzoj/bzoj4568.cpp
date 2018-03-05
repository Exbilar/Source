#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: swap;
using std :: make_pair;

typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 4e4 + 10;

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

struct Basis{
	LL bas[62];
	Basis() { clr(bas); }
}E[maxm << 1];

Basis operator + (const Basis lhs,const Basis rhs) {
	Basis res = lhs;
	for(int i = 60;i >= 0;i--) {
		if(!rhs.bas[i]) continue;
		LL cur = rhs.bas[i];
		
		for(int j = 60;j >= 0;j--) {
			if(!(cur & (1LL << j))) continue;
			if(!res.bas[j]) {
				res.bas[j] = cur;
				break;
			} else cur ^= res.bas[j];
		}
	}
	return res;
}

int fst[maxm],nxt[maxm],to[maxm],pos[maxm];
int ftr[maxm],dpt[maxm],top[maxm],size[maxm],son[maxm];
LL val[maxm],bin[63];

int cnt,sz,n,m;

void ins(int f,int t) {
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

void dfs1(int x) {
	size[x] = 1;
	for(int u = fst[x];u;u = nxt[u]) {
		int v = to[u];
		if(v == ftr[x]) continue;
		ftr[v] = x,dpt[v] = dpt[x] + 1;
		dfs1(v);
		size[x] += size[v];
		if(size[son[x]] < size[v]) son[x] = v;
	}
}

void dfs2(int x,int chain) {
	pos[x] = ++sz,top[x] = chain;
	if(son[x]) dfs2(son[x],chain);
	for(int u = fst[x];u;u = nxt[u]) {
		if(to[u] != ftr[x] && to[u] != son[x]) dfs2(to[u],to[u]);
	}
}

LL calc(Basis Bas) {
	LL res = 0;
	for(int i = 60;i >= 0;i--)
		chkmax(res,res ^ Bas.bas[i]);
	return res;
}

void insert(int x,LL v) {
	for(int i = 60;i >= 0;i--) {
		if(!(v & bin[i])) continue;
		if(!E[x].bas[i]) return E[x].bas[i] = v,void();
		else v ^= E[x].bas[i];
	}
}

void modify(int x,int l,int r,int pos,LL v) {
	insert(x,v);
	if(l == r) return ;
	int mid = (l + r) >> 1;
	if(pos <= mid) modify(x << 1,l,mid,pos,v);
	else modify(x << 1 | 1,mid + 1,r,pos,v);
}

Basis Query(int x,int l,int r,int L,int R) {
	if(l >= L && r <= R) return E[x];
	int mid = (l + r) >> 1;
	if(R <= mid) return Query(x << 1,l,mid,L,R);
	else if(L > mid) return Query(x << 1 | 1,mid + 1,r,L,R);
	else return Query(x << 1,l,mid,L,mid) + Query(x << 1 | 1,mid + 1,r,mid + 1,R);
}

LL solve(int x,int y) {
	Basis res;
	while(top[x] != top[y]) {
		if(dpt[top[x]] < dpt[top[y]]) swap(x,y);
		res = res + Query(1,1,n,pos[top[x]],pos[x]);
		x = ftr[top[x]];
	}
	
	if(pos[x] > pos[y]) swap(x,y);
	res = res + Query(1,1,n,pos[x],pos[y]);
	return calc(res);
}

int main() {

	freopen("lucky4.in","r",stdin);

	bin[0] = 1;
	for(int i = 1;i <= 61;i++) bin[i] = bin[i - 1] << 1;
	
	read(n); read(m);
	for(int i = 1;i <= n;i++) read(val[i]);

	int u,v;
	for(int i = 1;i < n;i++) {
		read(u),read(v);
		ins(u,v);
	}

	dfs1(1),dfs2(1,1);

	for(int i = 1;i <= n;i++) {
		modify(1,1,n,pos[i],val[i]);
	}

	while(m--) {
		read(u),read(v);
		printf("%lld\n",solve(u,v));
	}

	return 0;
}
