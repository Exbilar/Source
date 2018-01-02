#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;
static const int maxn = 6e6 + 10;

template <class T> inline bool chkmax(T &x,T y){
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in){
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

int fst[maxm],nxt[maxn],to[maxn],ddf[maxm];
int cnt,rt,sum,n,m;

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

namespace __DFS__{
	
	int dpt[maxm],top[maxm],size[maxm],ftr[maxm],son[maxm];
	
	void dfs1(int x){
		size[x] = 1;
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(v == ftr[x]) continue;
			dpt[v] = dpt[x] + 1;
			ftr[v] = x;
			dfs1(v);
			size[x] += size[v];
			if(size[son[x]] < size[v]) son[x] = v;
		}
	}

	void dfs2(int x,int chain){
		top[x] = chain;
		if(son[x]) dfs2(son[x],chain);
		for(int u = fst[x];u;u = nxt[u])
			if(to[u] != ftr[x] && to[u] != son[x]) dfs2(to[u],to[u]);
	}

	int LCA(int x,int y){
		while(top[x] != top[y]){
			if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
			x = ftr[top[x]];
		}
		return dpt[x] < dpt[y] ? x : y;
	}

	int dist(int x,int y){
		return dpt[x] + dpt[y] - (dpt[LCA(x,y)] << 1);
	}
	
}

namespace SMT{
	
	int sum[maxn],lc[maxn],rc[maxn];
	int sz;

	void insert(int &x,int l,int r,int pos,int v){
		if(!x) x = ++sz;
		sum[x] += v;
		if(l == r) return ;
		
		int mid = (l + r) >> 1;
		if(pos <= mid) insert(lc[x],l,mid,pos,v);
		else insert(rc[x],mid + 1,r,pos,v);
	}

	int Query(int x,int l,int r,int L,int R){
		if(!x) return 0;
		if(l >= L && r <= R) return sum[x];
		
		int mid = (l + r) >> 1;
		if(R <= mid) return Query(lc[x],l,mid,L,R);
		else if(L > mid) return Query(rc[x],mid + 1,r,L,R);
		else return Query(lc[x],l,mid,L,mid) + Query(rc[x],mid + 1,r,mid + 1,R);
	}
	
}

namespace Solve{

	using SMT :: insert;
	using SMT :: Query;

	int dpt[maxm],_rt[maxm][2],size[maxm],f[maxm],vis[maxm],P[maxm];
	
	void getRoot(int x,int fa){
		size[x] = 1,f[x] = 0;
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(vis[v] || v == fa) continue;
			getRoot(v,x);
			size[x] += size[v];
			chkmax(f[x],size[v]);
		}
		chkmax(f[x],sum - size[x]);
		if(f[x] < f[rt]) rt = x;
	}
	
	void getDis(int x,int fa,int root,int asd){
		insert(_rt[root][asd],0,n,dpt[x],ddf[x]);
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(vis[v] || v == fa) continue;
			dpt[v] = dpt[x] + 1;
			getDis(v,x,root,asd);
		}
	}
	
	void solve(int x){
		vis[x] = 1,dpt[x] = 0;
		getDis(x,0,x,0);
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(vis[v]) continue;
			sum = size[v],dpt[v] = 1,rt = 0;
			getRoot(v,0);
			getDis(v,x,rt,1);
			P[rt] = x;
			solve(rt);
		}
	}

	int _Query(int x,int k){
		int res = Query(_rt[x][0],0,n,0,k);
		for(int u = x;P[u];u = P[u]){
			int dist = __DFS__ :: dist(x,P[u]);
			res += Query(_rt[P[u]][0],0,n,0,k - dist);
			res -= Query(_rt[u][1],0,n,0,k - dist);
		}
		return res;
	}

	void modify(int x,int k){
		int tmp = k - Query(_rt[x][0],0,n,0,0);
		insert(_rt[x][0],0,n,0,tmp);
		for(int u = x;P[u];u = P[u]){
			int dist = __DFS__ :: dist(x,P[u]);
			insert(_rt[P[u]][0],0,n,dist,tmp);
			insert(_rt[u][1],0,n,dist,tmp);
		}
	}
}

int main(){

	int u,v,lstans = 0;
	read(n),read(m);
	for(int i = 1;i <= n;i++) read(ddf[i]);

	for(int i = 1;i < n;i++) read(u),read(v),ins(u,v);

	__DFS__ :: dfs1(1);
	__DFS__ :: dfs2(1,1);
	
	Solve :: f[0] = n,sum = n;
	Solve :: getRoot(1,0);
	Solve :: solve(rt);
	
	while(m--){
		int opt,x,k;
		read(opt),read(x),read(k);
		x ^= lstans,k ^= lstans;
		if(opt == 0) lstans = Solve :: _Query(x,k),printf("%d\n",lstans);
		if(opt == 1) Solve :: modify(x,k);
	}
	
	return 0;
}
