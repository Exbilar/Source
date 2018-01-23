#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;
static const int mod = 1e9 + 7;

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

int fst[maxm],nxt[maxm],to[maxm];
LL fac[maxm],inv[maxm],size[maxm],f[maxm];

int cnt,n;
LL ans,tmp;

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

LL fpm(LL x,LL k){
	LL res = 1;
	while(k){
		if(k & 1) res = res * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return res;
}

void dfs1(int x,int fa){
	size[x] = 1;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == fa) continue;
		dfs1(v,x);
		size[x] += size[v];
		tmp = tmp * inv[size[v]] % mod;
	}
}

void dfs2(int x,int fa,LL val){
	ans = (ans + val) % mod;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == fa) continue;
		dfs2(v,x,1LL * val * size[v] % mod * inv[n - size[v]] % mod);
	}
}

int main(){

	read(n);

	int u,v;
	for(int i = 1;i < n;i++) read(u),read(v),ins(u,v);

	fac[0] = 1;
	for(int i = 1;i <= n;i++){
		fac[i] = 1LL * fac[i - 1] * i % mod;
	}

	inv[1] = 1;
	for(int i = 2;i <= n;i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;

	tmp = fac[n - 1];
	dfs1(1,0);
	
	dfs2(1,0,tmp);

	printf("%lld\n",ans);

	return 0;
}
