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

int vis[maxm],size[maxm],dis[maxm],dpt[maxm],f[maxm];
int fst[maxm],nxt[maxm],to[maxm],val[maxm],V[maxm];
LL F[maxm][2],G[maxm][2];

int cnt,rt,sum,n,maxdpt;
LL ans;

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
	chkmax(maxdpt,dpt[x]);
	if(V[dis[x]]) F[dis[x]][1]++;
	else F[dis[x]][0]++;
	
	V[dis[x]]++;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(vis[v] || v == fa) continue;
		dpt[v] = dpt[x] + 1;
		dis[v] = dis[x] + val[u];
		getDis(v,x);
	}
	V[dis[x]]--;
	
}

void solve(int x){
	vis[x] = 1,G[n][0] = 1;
	int smax = 0;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(vis[v]) continue;
		dpt[v] = 1,dis[v] = val[u] + n,maxdpt = 1;
		getDis(v,0);
		chkmax(smax,maxdpt);
		ans += (G[n][0] - 1) * F[n][0];
		for(int i = -maxdpt;i <= maxdpt;i++){
			ans += G[n - i][1] * F[n + i][1] + G[n - i][0] * F[n + i][1] + G[n - i][1] * F[n + i][0];
		}
		for(int i = n - maxdpt;i <= n + maxdpt;i++){
			G[i][0] += F[i][0];
			G[i][1] += F[i][1];
			F[i][0] = F[i][1] = 0;
		}
	}
	for(int i = n - smax;i <= n + smax;i++) G[i][0] = G[i][1] = 0;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(vis[v]) continue;
		sum = size[v],rt = 0;
		getRoot(v,0);
		solve(rt);
	}
}

int main(){
	
	int u,v,w;
	read(n);
	for(int i = 1;i < n;i++){
		read(u),read(v),read(w);
		if(w == 0) ins(u,v,-1);
		if(w == 1) ins(u,v,1);
	}

	sum = n,f[0] = n + 1;
	getRoot(1,0);
	solve(rt);

	printf("%lld\n",ans);

	return 0;
}
