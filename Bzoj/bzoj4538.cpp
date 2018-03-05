#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 3e5 + 10;
static const int maxn = 19;

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

int fst[maxm],nxt[maxm],to[maxm],ftr[maxm],dpt[maxm];
int posl[maxm],posr[maxm],ans[maxm],ddf[maxm];
int cnt,n,m,sz;

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

struct Query{
	int opt,x,y,v,k,id;

	bool operator < (const Query &Q) const {
		return id < Q.id;
	}
	
}Q[maxm],tmpl[maxm],tmpr[maxm];

struct BIT{
	int bit[maxm],asdf[maxm];
	int T;
	
	void clear(){
		T++;
	}
	
	int lowbit(int x){
		return x & -x;
	}

	void Upt(int k,int v){
		if(!k) return ;
		for(int i = k;i <= n;i += lowbit(i))
			if(asdf[i] == T) bit[i] += v;
			else bit[i] = v,asdf[i] = T;
	}

	int Qry(int k){
		int res = 0;
		for(int i = k;i;i -= lowbit(i))
			if(asdf[i] == T) res += bit[i];
		return res;
	}
	
}Bit;

namespace RMQ{

	int RMQ[maxm][maxn],idx[maxm],pos[maxm],LOG[maxm];
	int sz;
	
	void dfs(int x){
		idx[++sz] = x,pos[x] = sz;
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(v == ftr[x]) continue;
			ftr[v] = x,dpt[v] = dpt[x] + 1;
			dfs(v);
			idx[++sz] = x;
		}
	}

	void getRMQ(){
		for(int i = 1;i <= sz;i++) RMQ[i][0] = idx[i];
		for(int j = 1;j <= 18;j++){
			for(int i = 1;i <= sz - (1 << (j - 1));i++){
				if(dpt[RMQ[i][j - 1]] <= dpt[RMQ[i + (1 << (j - 1))][j - 1]])
					RMQ[i][j] = RMQ[i][j - 1];
				else RMQ[i][j] = RMQ[i + (1 << (j - 1))][j - 1];
			}
		}
		
		LOG[1] = 0;
		for(int i = 2;i <= sz;i++) LOG[i] = LOG[i >> 1] + 1;
	}

	int LCA(int x,int y){
		int L = pos[x],R = pos[y];
		if(L > R) std :: swap(L,R);
		int k = LOG[R - L + 1];
		if(dpt[RMQ[L][k]] <= dpt[RMQ[R - (1 << k) + 1][k]]) return RMQ[L][k];
		return RMQ[R - (1 << k) + 1][k];
	}
	
}

int Query(int l,int r){
	return Bit.Qry(r) - Bit.Qry(l - 1);
}

void modify(int x,int y,int v){
	int lca = RMQ :: LCA(x,y);
	Bit.Upt(posl[x],v),Bit.Upt(posl[y],v);
	Bit.Upt(posl[lca],-v);
	if(ftr[lca]) Bit.Upt(posl[ftr[lca]],-v);
}

void _dfs(int x){
	posl[x] = ++sz;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == ftr[x]) continue;
		_dfs(v);
	}
	posr[x] = sz;
}

void solve(int l,int r,int ql,int qr){
	if(l == r){
		for(int i = ql;i <= qr;i++){
			if(Q[i].opt == 3) ans[Q[i].id] = l;
		}
		return ;
	}

	int mid = (l + r) >> 1;
	
	int head = 0,tail = 0;
	int num = 0;

	Bit.clear();
	
	for(int i = ql;i <= qr;i++){
		if(Q[i].opt == 1 && Q[i].v > ddf[mid]){
			modify(Q[i].x,Q[i].y,1);
			tmpr[++tail] = Q[i];
			num++;
		}
		else if(Q[i].opt == 1) tmpl[++head] = Q[i];
		
		if(Q[i].opt == 2 && Q[i].v > ddf[mid]){
			modify(Q[i].x,Q[i].y,-1);
			tmpr[++tail] = Q[i];
			num--;
		}
		else if(Q[i].opt == 2) tmpl[++head] = Q[i];
		
		if(Q[i].opt == 3){
			int asd = Query(posl[Q[i].k],posr[Q[i].k]);
			if(asd < num) tmpr[++tail] = Q[i];
			else tmpl[++head] = Q[i];
		}
	}

	for(int i = 1;i <= head;i++) Q[ql + i - 1] = tmpl[i];
	for(int i = 1;i <= tail;i++) Q[ql + head + i - 1] = tmpr[i];
	
	solve(l,mid,ql,ql + head - 1);
	solve(mid + 1,r,ql + head,qr);
}

int main(){

	read(n),read(m);

	int u,v;
	for(int i = 1;i < n;i++) read(u),read(v),ins(u,v);

	RMQ :: dfs(1);
	RMQ :: getRMQ();
	_dfs(1);
	
	for(int i = 1;i <= m;i++){
		read(Q[i].opt); Q[i].opt++;
		if(Q[i].opt == 1){
			read(Q[i].x),read(Q[i].y),read(Q[i].v);
			ddf[++ddf[0]] = Q[i].v;
		}
		if(Q[i].opt == 2){
			read(Q[i].k),Q[i].v = Q[Q[i].k].v;
			Q[i].x = Q[Q[i].k].x;
			Q[i].y = Q[Q[i].k].y;
		}
		if(Q[i].opt == 3) read(Q[i].k);
		Q[i].id = i;
	}

	std :: sort(ddf + 1,ddf + ddf[0] + 1);
	ddf[0] = std :: unique(ddf + 1,ddf + ddf[0] + 1) - ddf - 1;

	solve(0,ddf[0],1,m);

	std :: sort(Q + 1,Q + m + 1);
	
	for(int i = 1;i <= m;i++){
		if(Q[i].opt == 3) printf("%d\n",ans[i] ? ddf[ans[i]] : -1);
	}
	
	return 0;
}
