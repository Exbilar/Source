#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int dpt[maxm],pos[maxm],fnl[maxm],fst[maxm],nxt[maxm],to[maxm],ch[maxm][2],rev[maxm],lx[maxm];
int size[maxm],son[maxm],_ftr[maxm],ftr[maxm],smax[maxm],top[maxm],tag[maxm],stk[maxm],ddf[maxm];
int n,m,sz,cnt,tp;

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
}

namespace SMT{

	void dfs1(int x){
		size[x] = 1,pos[x] = ++sz,ddf[sz] = x;
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(v == _ftr[x]) continue;
			_ftr[v] = ftr[v] = x,dpt[v] = dpt[x] + 1;
			dfs1(v);
			size[x] += size[v];
			if(size[son[x]] < size[v]) son[x] = v;
		}
		fnl[x] = sz;
	}

	void dfs2(int x,int chain){
		top[x] = chain;
		if(son[x]) dfs2(son[x],chain);
		for(int u = fst[x];u;u = nxt[u])
			if(to[u] != son[x] && to[u] != _ftr[x]) dfs2(to[u],to[u]);
	}

	void pushup(int x){
		int lc = x << 1,rc = x << 1 | 1;
		smax[x] = std :: max(smax[lc],smax[rc]);
	}
	
	void build(int x,int l,int r){
		if(l == r) return smax[x] = dpt[ddf[l]] + 1,void();
		int mid = (l + r) >> 1;
		build(x << 1,l,mid);
		build(x << 1 | 1,mid + 1,r);
		pushup(x);
	}

	void pushdown(int x){
		int lc = x << 1,rc = x << 1 | 1;
		smax[lc] += tag[x],smax[rc] += tag[x];
		tag[lc] += tag[x],tag[rc] += tag[x],tag[x] = 0;
	}
	
	void modify(int x,int l,int r,int L,int R,int val){
		if(l >= L && r <= R) return tag[x] += val,smax[x] += val,void();
		pushdown(x);
		int mid = (l + r) >> 1;
		if(L <= mid) modify(x << 1,l,mid,L,R,val);
		if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,val);
		pushup(x);
	}

	int Qry(int x,int l,int r,int L,int R){
		if(l >= L && r <= R) return smax[x];
		pushdown(x);
		int mid = (l + r) >> 1,ret = 0;
		if(L <= mid) ret = std :: max(ret,Qry(x << 1,l,mid,L,R));
		if(R > mid) ret = std :: max(ret,Qry(x << 1 | 1,mid + 1,r,L,R));
		return ret;
	}

	int LCA(int x,int y){
		while(top[x] != top[y]){
			if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
			x = _ftr[top[x]];
		}
		return dpt[x] < dpt[y] ? x : y;
	}
	
}

namespace LCT{

	void upt(int x){
		lx[x] = x;
		if(ch[x][0]) lx[x] = lx[ch[x][0]];
	}
	
	int isrt(int x){
		return ch[ftr[x]][0] != x && ch[ftr[x]][1] != x;
	}

	int get(int x){
		return ch[ftr[x]][1] == x;
	}

	void rotate(int x){
		int fa = ftr[x],gnd = ftr[fa],f = get(x);
		if(!isrt(fa)) ch[gnd][get(fa)] = x;
		ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
		ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
		upt(fa),upt(x);
	}

	void pushdown(int x){
		if(!rev[x]) return;
		int lc = ch[x][0],rc = ch[x][1];
		rev[x] ^= 1,rev[lc] ^= 1,rev[rc] ^= 1;
		std :: swap(ch[x][0],ch[x][1]);
	}

	void pushtag(int x){
		tp = 0,stk[++tp] = x;
		for(int i = x;!isrt(i);i = ftr[i])
			stk[++tp] = ftr[i];
		while(tp) pushdown(stk[tp--]);
	}

	void splay(int x){
		pushtag(x);
		for(x;!isrt(x);rotate(x))
			if(!isrt(ftr[x])) rotate(get(x) == get(ftr[x]) ? ftr[x] : x);
	}

	void access(int x){
		for(int y = 0;x;y = x,x = ftr[x]){
			splay(x);
			if(ch[x][1]) SMT :: modify(1,1,n,pos[lx[ch[x][1]]],fnl[lx[ch[x][1]]],1);
			if(y) SMT :: modify(1,1,n,pos[lx[y]],fnl[lx[y]],-1);
			ch[x][1] = y;
		}
	}

	void makert(int x){
		access(x),splay(x),rev[x] ^= 1;
	}

	int solve(int x){
		int ret = 0;
		while(x){
			splay(x);
			x = ftr[x];
			ret++;
		}
		return ret;
	}
	
	int Qry(int x,int y){
		int lca = SMT :: LCA(x,y);
		return solve(x) + solve(y) - 2 * solve(lca) + 1;
	}
	
}

int main(){

	int opt,x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) lx[i] = i;
	for(int i = 1;i < n;i++) scanf("%d%d",&x,&y),ins(x,y),ins(y,x);
	SMT :: dfs1(1);
	SMT :: dfs2(1,1);
	SMT :: build(1,1,n);

	while(m--){
		scanf("%d",&opt);
		if(opt == 1) scanf("%d",&x),LCT :: access(x);
		if(opt == 2) scanf("%d%d",&x,&y),printf("%d\n",LCT :: Qry(x,y));
		if(opt == 3) scanf("%d",&x),printf("%d\n",SMT :: Qry(1,1,n,pos[x],fnl[x]));
	}

	return 0;
}
