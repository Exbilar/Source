#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)

using std :: max;
using std :: min;
using std :: set;
using std :: pair;
using std :: make_pair;
using std :: vector;
using std :: queue;
using std :: multiset;
using std :: priority_queue;

typedef long long LL;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const int maxm = 1e6 + 10;
static const int MOD = 10007;

template <class T> void read(T &in){
	in = 0; int f = 1 ;char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

template <class T> inline bool chkmax(T &x,T y){
	return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
	return x > y ? x = y,true : false;
}

int fst[maxm],nxt[maxm],to[maxm],val[maxm];
int n,cnt,_sum,_max;

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

void dfs(int x){
	int snd = 0,smax = 0,sum = 0;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(val[v] > smax) snd = smax,smax = val[v];
		else if(val[v] > snd) snd = val[v];
		_sum = (_sum + sum * val[v]) % MOD;
		sum = (sum + val[v]) % MOD;
	}
	_max = max(_max,snd * smax);
}

int main(){
	int u,v,w;
	read(n);
	for(int i = 1;i < n;i++) read(u),read(v),ins(u,v);
	for(int i = 1;i <= n;i++) read(val[i]);

	for(int i = 1;i <= n;i++) dfs(i);

	printf("%d %d\n",_max,(_sum << 1) % MOD);

	return 0;
}
