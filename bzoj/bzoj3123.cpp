#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e5 + 10;

template <class T> inline void swap(T &x,T &y){
	x ^= y ^= x ^= y;
}

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

int sum[maxm * 100],rt[maxm],lc[maxm * 100],rc[maxm * 100];
int fst[maxm],nxt[maxm << 1],to[maxm << 1],A[maxm],tmp[maxm];
int gnd[maxm][18],dpt[maxm];
int sz,cnt,n,m,cas,Q,tot;

char opt[10];

struct DSU{
	int ftr[maxm],size[maxm];

	void init(int N){
		for(int i = 1;i <= N;i++) ftr[i] = i,size[i] = 1;
	}
	
	int find(int x){
		return x == ftr[x] ? x : ftr[x] = find(ftr[x]);
	}

	void merge(int x,int y){
		x = find(x),y = find(y);
		size[y] += size[x];
		ftr[x] = y;
	}
}UFS;

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

void insert(int &x,int lst,int l,int r,int pos,int v){
	x = ++sz; lc[x] = lc[lst]; rc[x] = rc[lst]; sum[x] = sum[lst] + v;
	if(l == r) return ;
	int mid = (l + r) >> 1;
	if(pos <= mid) insert(lc[x],lc[lst],l,mid,pos,v);
	else insert(rc[x],rc[lst],mid + 1,r,pos,v);
}

int Query(int x,int y,int z,int w,int l,int r,int kth){
	if(l == r) return l;
	int mid = (l + r) >> 1;
	int cur = sum[lc[x]] + sum[lc[y]] - sum[lc[z]] - sum[lc[w]];
	if(kth <= cur) return Query(lc[x],lc[y],lc[z],lc[w],l,mid,kth);
	else return Query(rc[x],rc[y],rc[z],rc[w],mid + 1,r,kth - cur);
}

void dfs(int x,int fa){
	insert(rt[x],rt[fa],1,tot,A[x],1);

	for(int i = 1;i <= 17;i++){
		if(dpt[x] < (1 << i)) gnd[x][i] = 0;
		else gnd[x][i] = gnd[gnd[x][i - 1]][i - 1];
	}
	
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == fa) continue;
		dpt[v] = dpt[x] + 1;
		gnd[v][0] = x;
		dfs(v,x);
	}
}

int LCA(int x,int y){
	if(dpt[x] < dpt[y]) swap(x,y);
	
	int d = dpt[x] - dpt[y];
	for(int i = 0;i <= 17;i++)
		if(d & (1 << i)) x = gnd[x][i];
	
	for(int i = 17;i >= 0;i--)
		if(gnd[x][i] != gnd[y][i]) x = gnd[x][i],y = gnd[y][i];
	
	return x == y ? x : gnd[x][0];
}

void Link(int x,int y){
	ins(x,y);
	int fx = UFS.find(x),fy = UFS.find(y);
	if(UFS.size[fx] > UFS.size[fy]) gnd[y][0] = x,dpt[y] = dpt[x] + 1,dfs(y,x);
	else gnd[x][0] = y,dpt[x] = dpt[y] + 1,dfs(x,y);
	UFS.merge(x,y);
}

int main(){

	read(cas);
	read(n),read(m),read(Q);

	for(int i = 1;i <= n;i++) read(A[i]),tmp[i] = A[i];

	std :: sort(tmp + 1,tmp + n + 1);
	tot = std :: unique(tmp + 1,tmp + n + 1) - tmp - 1;

	for(int i = 1;i <= n;i++){
		A[i] = std :: lower_bound(tmp + 1,tmp + tot + 1,A[i]) - tmp;
	}

	int x,y,k,lstans = 0;

	UFS.init(n);
	
	for(int i = 1;i <= m;i++){
		read(x),read(y);
		ins(x,y);
		UFS.merge(x,y);
	}	

	for(int i = 1;i <= n;i++)
		if(!rt[i]) dfs(i,0);
	
	while(Q--){
		scanf("%s",opt);
		if(opt[0] == 'Q'){
			read(x),read(y),read(k);
			x ^= lstans,y ^= lstans,k ^= lstans;
			int lca = LCA(x,y),fa = gnd[lca][0];
			printf("%d\n",lstans = tmp[Query(rt[x],rt[y],rt[lca],rt[fa],1,tot,k)]);
		}
		
		if(opt[0] == 'L'){
			read(x),read(y);
			x ^= lstans,y ^= lstans;
			Link(x,y);
		}
	}

	return 0;
}
