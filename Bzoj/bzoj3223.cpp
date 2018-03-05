#include <cstdio>
#include <algorithm>

using std :: swap;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 29;

int ch[maxm][2],size[maxm],rev[maxm],v[maxm],ftr[maxm];
int rt,sz,n,m,L,R;

void upt(int x){
	size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
}

int get(int x){
	return ch[ftr[x]][1] == x;
}

void pushdown(int x){
	if(!x || !rev[x]) return ;
	rev[ch[x][0]] ^= 1,rev[ch[x][1]] ^= 1,rev[x] = 0,swap(ch[x][0],ch[x][1]);
}

void rotate(int x){
	int fa = ftr[x],gnd = ftr[fa],f = get(x);
	pushdown(fa),pushdown(x);
	ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
	ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
	if(gnd) ch[gnd][ch[gnd][1] == fa] = x;
	upt(fa),upt(x);
}

void splay(int x,int k){
	for(int fa = x;(fa = ftr[x]) != k;rotate(x))
		if(ftr[fa] != k) rotate(get(x) == get(fa) ? fa : x);
	if(!k) rt = x;
}

void build(int &x,int l,int r){
	if(l > r) return;
	int mid = (l + r) >> 1;
	x = ++sz,v[x] = mid;
	build(ch[x][0],l,mid - 1);
	build(ch[x][1],mid + 1,r);
	ftr[ch[x][0]] = ftr[ch[x][1]] = x;
	upt(x);
}

int Qorder(int rnk){
	int f = 0;
    for(int x = rt;x;x = ch[x][f]){
        pushdown(x);
        if(size[ch[x][0]] >= rnk) f = 0;
        else if(size[ch[x][0]] + 1 == rnk) return x;
        else rnk -= (1 + size[ch[x][0]]),f = 1;
    }
}

void dfs(int x){
	pushdown(x);
	if(ch[x][0]) dfs(ch[x][0]);
	if(v[x] >= 1 && v[x] <= n) printf("%d ",v[x]);
	if(ch[x][1]) dfs(ch[x][1]);
}

int main(){
	scanf("%d%d",&n,&m);
	v[0] = -INF,v[n + 1] = INF;
	build(rt,0,n + 1);
	while(m--){
		scanf("%d%d",&L,&R);
		int x1 = Qorder(L),x2 = Qorder(R + 2);
		splay(x1,0),splay(x2,x1);
		rev[ch[ch[rt][1]][0]] ^= 1;
	}
	dfs(rt);
	return 0;
}

