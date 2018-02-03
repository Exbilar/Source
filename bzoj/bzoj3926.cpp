#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 2e5 + 10;

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

int fst[maxm],nxt[maxm],to[maxm],col[maxm],deg[maxm];
int n,m,cnt;

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

struct Suffix_Automaton{
	int len[maxm * 20],size[maxm * 20],fail[maxm * 20],ch[maxm * 20][15];
	int lst,rt,sz;

	Suffix_Automaton(){
		sz = 0; lst = rt = ++sz;
		len[rt] = fail[rt] = 0;
	}

	int insert(int v,int lst){
		int x = ++sz,cur = lst;
		len[x] = len[lst] + 1; size[x] = 1;

		while(cur && !ch[cur][v]) ch[cur][v] = x,cur = fail[cur];
		if(!cur) return fail[x] = rt,x;

		int pos = ch[cur][v];
		if(len[pos] == len[cur] + 1) return fail[x] = pos,x;

		int clone = ++sz;
		fail[clone] = fail[pos];
		len[clone] = len[cur] + 1;
		memcpy(ch[clone],ch[pos],sizeof ch[pos]);

		fail[x] = fail[pos] = clone;
		while(cur && ch[cur][v] == pos) ch[cur][v] = clone,cur = fail[cur];

		return x;
	}

	void solve(){
		LL res = 0;
		for(int i = 1;i <= sz;i++) res += len[i] - len[fail[i]];
		printf("%lld\n",res);
	}
	
}SAM;

void dfs(int x,int fa,int lst){
	int np = SAM.insert(col[x],lst);
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == fa) continue;
		dfs(v,x,np);
	}
}

int main(){

//	freopen("bzoj3926.in","r",stdin);
	
	read(n),read(m);
	for(int i = 1;i <= n;i++) read(col[i]);

	int u,v;
	for(int i = 1;i < n;i++){
		read(u); read(v); ins(u,v);
		deg[u]++,deg[v]++;
	}

	for(int i = 1;i <= n;i++){
		if(deg[i] != 1) continue;
		dfs(i,0,SAM.rt);
	}

	SAM.solve();
	
	return 0;
}
