#include <cstdio>
#include <algorithm>

static const int maxm = 2e6 + 10;

int dpt[maxm],size[maxm],ftr[maxm],son[maxm],top[maxm],pos[maxm],A[maxm],fnl[maxm];
int fst[maxm],to[maxm],nxt[maxm];
int sum[maxm],tag[maxm];
int cnt,sz,n;

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
}

void dfs1(int x){
	size[x] = 1;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == ftr[x]) continue;
		dpt[v] = dpt[x] + 1,ftr[v] = x;
		dfs1(v);
		size[x] += size[v];
		if(size[v] > size[son[x]]) son[x] = v;
	}
}

void dfs2(int x,int chain){
	pos[x] = ++sz,top[x] = chain;
	if(son[x]) dfs2(son[x],chain);
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v != son[x] && dpt[v] > dpt[x]) dfs2(v,v);
	}
	fnl[x] = sz;
}

void pushup(int x){
	int lc = x << 1,rc = x << 1 | 1;
	sum[x] = sum[lc] + sum[rc];
}

void pushdown(int x,int l,int r){
	int lc = x << 1,rc = x << 1 | 1,mid = (l + r) >> 1;
	sum[lc] += tag[x] * (mid - l + 1);
	sum[rc] += tag[x] * (r - mid);
	tag[lc] += tag[x],tag[rc] += tag[x];
	tag[x] = 0;
}

void modify(int x,int l,int r,int L,int R,int v){
	if(l >= L && r <= R){
		sum[x] += (r - l + 1) * v;
		tag[x] += v;
		return;
	}
	pushdown(x,l,r);
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1,l,mid,L,R,v);
	if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,v);
	pushup(x);
}

int Qry(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return sum[x];
	pushdown(x,l,r);
	int mid = (l + r) >> 1,ret = 0;
	if(L <= mid) ret += Qry(x << 1,l,mid,L,R);
	if(R > mid) ret += Qry(x << 1 | 1,mid + 1,r,L,R);
	return ret;
}

void solve(int x,int y,int v){
	while(top[x] != top[y]){
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		modify(1,1,n,pos[top[x]],pos[x],v);
		x = ftr[top[x]];
	}
	if(pos[x] > pos[y]) std :: swap(x,y);
	modify(1,1,n,pos[x],pos[y],v);
}

int main(){
	int x,y;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	for(int i = 1;i < n;i++) scanf("%d%d",&x,&y),ins(x,y),ins(y,x);

	dfs1(1);
	dfs2(1,1);
	
	for(int i = 1;i < n;i++){
		solve(A[i],A[i + 1],1);
		if(i != 1) solve(A[i],A[i],-1);
		if(i == n - 1) solve(A[i + 1],A[i + 1],-1);
	}
	
	for(int i = 1;i <= n;i++) printf("%d\n",Qry(1,1,n,pos[i],pos[i]));
	
	
	return 0;
}
