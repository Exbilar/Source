#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 2e5 + 10;

template <class T> inline bool chkmax (T &x, T y) {
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin (T &x, T y) {
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in) {
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if (ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

int fst[maxm],nxt[maxm],to[maxm],stk[maxm],Nds[maxm],f[maxm];
int _fst[maxm],_nxt[maxm],_to[maxm],_val[maxm],dpt[maxm];
int gnd[maxm][20],dfn[maxm],rem[maxm],ddf[maxm],size[maxm],pos[maxm];
int cnt,_cnt,n,m,sz,K,top;

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

void _ins(int f,int t){
	int v = abs(dpt[f] - dpt[t]);
	_nxt[++_cnt] = _fst[f],_to[_cnt] = t,_val[_cnt] = v,_fst[f] = _cnt;
	_nxt[++_cnt] = _fst[t],_to[_cnt] = f,_val[_cnt] = v,_fst[t] = _cnt;
}

bool cmp(const int &x,const int &y){
	return dfn[x] < dfn[y];
}

void dfs(int x,int fa){
	size[x] = 1,dfn[x] = ++sz;
	
	for(int i = 1;i <= 18;i++){
		if(dpt[x] < (1 << i)) break;
		gnd[x][i] = gnd[gnd[x][i - 1]][i - 1];
	}
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == fa) continue;
		gnd[v][0] = x,dpt[v] = dpt[x] + 1;
		dfs(v,x);
		size[x] += size[v];
	}
}

int LCA(int x,int y){
	if(dpt[x] < dpt[y]) std :: swap(x,y);
	int d = dpt[x] - dpt[y];
	
	for(int i = 18;i >= 0;i--){
		if(d & (1 << i)) x = gnd[x][i];
	}

	for(int i = 18;i >= 0;i--){
		if(gnd[x][i] != gnd[y][i]) x = gnd[x][i],y = gnd[y][i];
	}
	
	return x == y ? x : gnd[x][0];
}

int getDis(int x,int y){
	return dpt[x] + dpt[y] - dpt[LCA(x,y)] * 2;
}

void build(){
	read(K); _cnt = 0,top = 0;
	for(int i = 1;i <= K;i++){
		read(Nds[i]),ddf[Nds[i]] = Nds[i];
	}

	std :: sort(Nds + 1,Nds + K + 1,cmp);

	if(Nds[1] != 1) stk[++top] = 1;

	for(int i = 1;i <= K;i++){
		int cur = ddf[i],lca = LCA(stk[top],cur);
		while(dpt[stk[top]] > dpt[lca] && top){
			if(dpt[stk[top - 1]] < dpt[lca]){
				_ins(lca,stk[top]),stk[top] = lca;
			}
			else _ins(stk[top],stk[top - 1]),top--;
		}
		if(cur != stk[top]) stk[++top] = cur;
	}
	while(--top) _ins(stk[top + 1],stk[top]);
}

void dfs1(int x,int fa){
	pos[++pos[0]] = x; rem[x] = size[x];
	for(int u = _fst[x];u;u = _nxt[u]){
		int v = _to[u];
		if(v == fa) continue;
		dfs1(v,x);
		if(!ddf[v]) continue;
		int dis1 = getDis(x,ddf[x]),dis2 = getDis(x,ddf[v]);
		if(dis1 == dis2 && ddf[x] > ddf[v]) ddf[x] = ddf[v];
		else if(dis1 > dis2 || !ddf[x]) ddf[x] = ddf[v];
	}
}

void dfs2(int x,int fa){
	for(int u = _fst[x];u;u = _nxt[u]){
		int v = _to[u];
		if(v == fa) continue;
		int dis1 = getDis(v,ddf[x]),dis2 = getDis(v,ddf[v]);
		if(dis1 == dis2 && ddf[x] < ddf[v]) ddf[v] = ddf[x];
		else if(dis1 < dis2 || !ddf[v]) ddf[v] = ddf[x];
		dfs2(v,x);
	}
}

void solve(int x,int y){
	
}

int main(){


	return 0;
}
