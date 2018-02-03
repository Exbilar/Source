#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;

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

int ftr[maxm],size[maxm],ch[maxm][2];
int v[maxm],smax[maxm],tag[maxm],tagv[maxm];
int rt,sz,n;

int get(int x){
	return ch[ftr[x]][1] == x;
}

int chk(int x,int y){
	return x == y ? 233 : x > y;
}

void upt(int x){
	int lc = ch[x][0],rc = ch[x][1];
	size[x] = size[lc] + size[rc] + 1;
	smax[x] = max(v[x],max(smax[lc],smax[rc]));
}

void pushtag(int x,int val){
	if(!val || !x) return ;
	smax[x] += val,v[x] += val,tag[x] += val;
}

void pushtagv(int x,int val){
	if(!val || !x) return ;
	smax[x] = val,v[x] = val,tagv[x] = val;
}

void pushdown(int x){
	if(tagv[x]){
		if(ch[x][0]) pushtagv(ch[x][0],tagv[x]);
		if(ch[x][1]) pushtagv(ch[x][1],tagv[x]);
	}
	else if(tag[x]){
		if(ch[x][0]) pushtag(ch[x][0],tag[x]);
		if(ch[x][1]) pushtag(ch[x][1],tag[x]);
	}
	tag[x] = 0,tagv[x] = 0;
}

void downbtm(int x){
	if(ftr[x]) downbtm(ftr[x]);
	pushdown(x);
}

void rotate(int x){
	int fa = ftr[x],gnd = ftr[fa],f = get(x);
	if(gnd) ch[gnd][get(fa)] = x;
	ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
	ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
	upt(fa),upt(x);
}

void splay(int x,int k){
	downbtm(x);
	for(int fa = x;(fa = ftr[x]) != k;rotate(x))
		if(ftr[fa] != k) rotate(get(fa) == get(x) ? fa : x);
	if(!k) rt = x;
}

int Query(int x,int kth){
	pushdown(x);
	if(!x) return 0;
	if(kth <= size[ch[x][0]]) return Query(ch[x][0],kth);
	else if(kth > size[ch[x][0]] + 1) return Query(ch[x][1],kth - size[ch[x][0]] - 1);
	else return x;
}

void newnode(int &x,int fa,int val){
	x = ++sz,ftr[x] = fa,size[x] = 1,smax[x] = v[x] = val;
}

void insert(int l,int r){
	int x = Query(rt,r),y = Query(rt,r + 2);
	splay(x,0),splay(y,x);
	ch[y][0] = 0;
	upt(y);

	x = Query(rt,l),y = Query(rt,l + 1);
	splay(x,0),splay(y,x);
	newnode(ch[y][0],y,v[Query(rt,l)]);
	upt(y),upt(x);
}

void dfs(int x,int val){
	pushdown(x);
	if(!x) return ;
	if(v[x] < val) v[x] = smax[x] = val;
	if(smax[ch[x][0]] < val) pushtagv(ch[x][0],val),dfs(ch[x][1],val);
	else dfs(ch[x][0],val);
}

void __DFS__(int x){
	pushdown(x);
	if(ch[x][0]) __DFS__(ch[x][0]);
	if(ch[x][1]) __DFS__(ch[x][1]);
}

int leftward(int x){
	if(ch[x][0]) return leftward(ch[x][0]);
	return x;
}

void modify(int l,int r){
	int x = Query(rt,l),y = Query(rt,r + 2);
	splay(x,0),splay(y,x);
	pushtag(ch[y][0],1);

	int xx = Query(rt,1),yy = Query(rt,r + 2);
	splay(xx,0),splay(yy,xx);
	int val = smax[ch[yy][0]];

	x = Query(rt,r + 1),y = Query(rt,n + 2);
	splay(x,0),splay(y,x);
	dfs(ch[y][0],val);
}

void build(int &x,int l,int r,int fa){
	if(l > r) return ;
	int mid = (l + r) >> 1;
	newnode(x,fa,0);
	build(ch[x][0],l,mid - 1,x);
	build(ch[x][1],mid + 1,r,x);
	upt(x);
}

int main(){

	freopen("51nod1816.in","r",stdin);

	read(n);

	build(rt,0,n + 1,0);

	int l,r;
	for(int i = 1;i <= n;i++){
		read(l),read(r);
		insert(l,r);
		modify(l,r);
		//for(int i = 2;i <= n + 1;i++) printf("%d ",v[Query(rt,i)]);
		//puts("");
		//__DFS__(rt);
	}

	printf("%d\n",smax[rt]);

	return 0;
}
