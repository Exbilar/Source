#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int MOD = 201314;

struct Query{
	int num,z,idx,f;
	bool operator < (const Query &ask) const {
		return num < ask.num;
	}
}ask[maxm];

int pos[maxm],top[maxm],ftr[maxm],son[maxm],dpt[maxm],size[maxm];
int sum[maxm],tag[maxm],ans_r[maxm],ans_l[maxm];
int fst[maxm],to[maxm],nxt[maxm];
int cnt,n,m,tot,sz;

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
		dpt[v] = dpt[x] + 1;
		dfs1(v);
		size[x] += size[v];
		if(size[son[x]] < size[v]) son[x] = v;
	}
}

void dfs2(int x,int chain){
	pos[x] = ++sz,top[x] = chain;
	if(son[x]) dfs2(son[x],chain);
	for(int u = fst[x];u;u = nxt[u])
		if(to[u] != ftr[x] && to[u] != son[x]) dfs2(to[u],to[u]);
}

void pushup(int x){
	int lc = x << 1,rc = x << 1 | 1;
	sum[x] = (sum[lc] + sum[rc]) % MOD;
}

void pushdown(int x,int l,int r){
	int lc = x << 1,rc = x << 1 | 1,mid = (l + r) >> 1;
	sum[lc] = (sum[lc] + tag[x] * (mid - l + 1)) % MOD;
	sum[rc] = (sum[rc] + tag[x] * (r - mid)) % MOD;
	tag[lc] = (tag[lc] + tag[x]) % MOD;
	tag[rc] = (tag[rc] + tag[x]) % MOD;
	tag[x] = 0;
}

void modify(int x,int l,int r,int L,int R,int v){
	if(l >= L && r <= R)
		return sum[x] = (sum[x] + v * (r - l + 1)) % MOD,tag[x] = (tag[x] + v) % MOD,void();
	pushdown(x,l,r);
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1,l,mid,L,R,v);
	if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,v);
	pushup(x);
}

int Qry(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return sum[x];
	pushdown(x,l,r);
	int mid = (l + r) >> 1,res = 0;
	if(L <= mid) res = (res + Qry(x << 1,l,mid,L,R)) % MOD;
	if(R > mid) res = (res + Qry(x << 1 | 1,mid + 1,r,L,R)) % MOD;
	return res;
}

void solve_modify(int x,int y,int v){
	while(top[x] != top[y]){
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		modify(1,1,n,pos[top[x]],pos[x],v);
		x = ftr[top[x]];
	}
	if(pos[x] > pos[y]) std :: swap(x,y);
	modify(1,1,n,pos[x],pos[y],v);
}

int solve_Qry(int x,int y){
	int res = 0;
	while(top[x] != top[y]){
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		res = (res + Qry(1,1,n,pos[top[x]],pos[x])) % MOD;
		x = ftr[top[x]];
	}
	if(pos[x] > pos[y]) std :: swap(x,y);
	res = (res + Qry(1,1,n,pos[x],pos[y])) % MOD;
	return res;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 2;i <= n;i++)
		scanf("%d",&ftr[i]),ftr[i]++,ins(ftr[i],i),ins(i,ftr[i]);

	for(int i = 1;i <= m;i++){
		int l,r,x;
		scanf("%d%d%d",&l,&r,&x),l++,r++,x++;
		ask[++tot].num = l - 1,ask[tot].z = x,ask[tot].f = 1,ask[tot].idx = i;
		ask[++tot].num = r,ask[tot].z = x,ask[tot].f = 0,ask[tot].idx = i;
	}

	std :: sort(ask + 1,ask + tot + 1);

	dfs1(1),dfs2(1,1);

	int now = 0;
	for(int i = 1;i <= tot;i++){
		while(now < ask[i].num) now++,solve_modify(1,now,1);
		if(ask[i].f) ans_l[ask[i].idx] = solve_Qry(1,ask[i].z);
		else ans_r[ask[i].idx] = solve_Qry(1,ask[i].z);
	}

	for(int i = 1;i <= m;i++) printf("%d\n",(ans_r[i] - ans_l[i] + MOD) % MOD);

	return 0;
}
