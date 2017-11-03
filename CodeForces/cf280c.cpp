#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: max;
using std :: min;

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;
static const LL oo = 1LL << 62;

template <class T> inline bool chkmax(T &x,T y){
	return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
	return x > y ? x = y,true : false;
}

template <typename T> inline void read (T &in){
	in = 0; char ch = getchar(); T f = 1;
	for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
	for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

int size[maxm],fst[maxm],nxt[maxm],to[maxm],dpt[maxm];
int n,cnt;

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

void dfs(int x,int fa){
	size[x] = 1;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == fa) continue;
		dpt[v] = dpt[x] + 1;
		dfs(v,x);
	}
}

int main(){
	int x,y;
	read(n);
	for(int i = 1;i < n;i++) read(x),read(y),ins(x,y);

	double ans = 0.0;
	
	dpt[1] = 1;
	dfs(1,0);
	
	for(int i = 1;i <= n;i++) ans += 1.0 / dpt[i];
	
	printf("%.10lf\n",ans);
	
	return 0;
}
