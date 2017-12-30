#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;

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

int fst[maxm],nxt[maxm],to[maxm],val[maxm],vis[maxm];
int size[maxm],f[maxm],dis[maxm],dpt[maxm],V[maxm];
int cnt,n,m,rt,sum,ans,K;

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,val[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,val[cnt] = v,fst[t] = cnt;
}

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

void getDis(int x,int fa){
	if(dis[x] <= K) chkmin(ans,dpt[x] + V[K - dis[x]]);
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(vis[v] || v == fa) continue;
		dpt[v] = dpt[x] + 1;
		dis[v] = dis[x] + val[u];
		getDis(v,x);
	}
}

void modify(int x,int fa,int opt){
	if(dis[x] <= K){
		if(opt) chkmin(V[dis[x]],dpt[x]);
		else V[dis[x]] = INF;
	}
	
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(vis[v] || v == fa) continue;
		modify(v,x,opt);
	}
}

void solve(int x){
	vis[x] = 1,V[0] = 0;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(vis[v]) continue;
		dpt[v] = 1,dis[v] = val[u];
		getDis(v,0);
		modify(v,0,1);
	}
	
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(vis[v]) continue;
		modify(v,0,0);
	}
	
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(vis[v]) continue;
		rt = 0,sum = size[v];
		getRoot(v,0);
		solve(rt);
	}
	
}

int main(){
	
	int u,v,w;
	read(n),read(K);
	for(int i = 1;i <= K;i++) V[i] = n;
	for(int i = 1;i < n;i++) read(u),read(v),read(w),ins(++u,++v,w);

	ans = n,sum = n,f[0] = n + 1;
	getRoot(1,0);
	solve(rt);

	if(ans != n) printf("%d\n",ans);
	else puts("-1");
	
	return 0;
}
