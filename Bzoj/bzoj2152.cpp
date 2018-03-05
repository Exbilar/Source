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

int fst[maxm],nxt[maxm],to[maxm],val[maxm],dis[maxm];
int V[maxm],size[maxm],f[maxm],vis[maxm];
int n,m,rt,sz,cnt,sum,ans;

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,val[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,val[cnt] = v,fst[t] = cnt;
}

void getRoot(int x,int fa){
	f[x] = 0,size[x] = 1;
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
	V[dis[x] % 3]++;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(vis[v] || v == fa) continue;
		dis[v] = dis[x] + val[u];
		getDis(v,x);
	}
}

int Query(int x,int Dis){
	dis[x] = Dis;
	V[0] = V[1] = V[2] = 0;
	getDis(x,0);
	return V[0] * V[0] + V[1] * V[2] * 2;
}

void solve(int x){
	ans += Query(x,0);
	vis[x] = 1;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(vis[v]) continue;
		ans -= Query(v,val[u]);
		rt = 0,sum = size[v];
		getRoot(v,0);
		solve(rt);
	}
}

int main(){
	
	read(n);
	for(int i = 1,x,y,w;i < n;i++){
		read(x),read(y),read(w);
		ins(x,y,w);
	}

	f[0] = n + 1,sum = n;
	getRoot(1,0),solve(rt);

	int g = std :: __gcd(ans,n * n);
	
	printf("%d/%d\n",ans / g,n * n / g);
	
	return 0;
}
