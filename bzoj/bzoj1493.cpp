#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: swap;
using std :: stack;

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

template <class T> inline T read(){
    T in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    return in * f;
}

int size[maxm],ftr[maxm],ch[maxm][2],stk[maxm],A[maxm];
int val[maxm],rev[maxm],sum[maxm],lcol[maxm],rcol[maxm],cov[maxm];
int sz,rt,top,n,m,C;

char opt[10];

int get(int x){
	return ch[ftr[x]][1] == x;
}

void upt(int x){
	int lc = ch[x][0],rc = ch[x][1];
	
	size[x] = size[lc] + size[rc] + 1;
	sum[x] = sum[lc] + sum[rc] + 1;
	lcol[x] = val[x],rcol[x] = val[x];
	
	if(ch[x][0]) lcol[x] = lcol[lc],sum[x] -= (rcol[lc] == val[x]);
	if(ch[x][1]) rcol[x] = rcol[rc],sum[x] -= (lcol[rc] == val[x]);
}

void nodeswap(int &x,int &y){
	swap(val[x],val[y]);
	upt(x),upt(y);
}

void rotate(int x){
	int fa = ftr[x],gnd = ftr[fa],f = get(x);
	if(gnd) ch[gnd][get(fa)] = x;
	ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
	ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
	upt(fa),upt(x);
}

void pushrev(int x){
	swap(ch[x][0],ch[x][1]);
	swap(lcol[x],rcol[x]);
	rev[x] ^= 1;
}

void pushcov(int x,int v){
	lcol[x] = rcol[x] = val[x] = v;
	cov[x] = v,rev[x] = 0;
	sum[x] = 1;
}

void pushdown(int x){
	if(rev[x]){
		if(ch[x][0]) pushrev(ch[x][0]);
		if(ch[x][1]) pushrev(ch[x][1]);
		rev[x] = 0;
	}
	if(cov[x]){
		if(ch[x][0]) pushcov(ch[x][0],cov[x]);
		if(ch[x][1]) pushcov(ch[x][1],cov[x]);
		cov[x] = 0;
	}
}

void pushbtm(int x){
	top = 0; stk[++top] = x;
	for(int i = x;ftr[i];i = ftr[i]) stk[++top] = ftr[i];
	while(top) pushdown(stk[top--]);
}

void downbtm(int x){
	pushdown(x);
	if(ch[x][0]) downbtm(ch[x][0]);
	if(ch[x][1]) downbtm(ch[x][1]);
}

void splay(int x,int k){
	pushbtm(x);
	for(int fa = x;(fa = ftr[x]) != k;rotate(x))
		if(ftr[fa] != k) rotate(get(x) == get(fa) ? fa : x);
	if(!k) rt = x;
}

void newnode(int &x,int fa,int v){
	x = ++sz;
	lcol[x] = rcol[x] = val[x] = v;
	size[x] = 1,sum[x] = 1,ftr[x] = fa;
}

void build(int &x,int l,int r,int fa){
	if(l > r) return ;
	int mid = (l + r) >> 1;
	newnode(x,fa,A[mid]);
	build(ch[x][0],l,mid - 1,x);
	build(ch[x][1],mid + 1,r,x);
	upt(x);
}

int Query(int x,int kth){
	pushdown(x);
	if(kth == size[ch[x][0]] + 1) return x;
	if(kth <= size[ch[x][0]]) return Query(ch[x][0],kth);
	else return Query(ch[x][1],kth - size[ch[x][0]] - 1);
}

void solve_R(){
	int k = read<int>();
	int x = Query(rt,n - k + 1),y = Query(rt,n + 2);
	if(!k) return ;
	
	splay(x,0),splay(y,x);
	
	int tmp = ch[y][0];
	ch[y][0] = 0,ftr[tmp] = 0;
	upt(y),upt(x);

	x = Query(rt,1),y = Query(rt,3);
	splay(x,0),splay(y,x);
	downbtm(ch[y][0]);
	
	ch[ch[y][0]][0] = tmp,ftr[tmp] = ch[y][0];
	upt(ch[y][0]),upt(y),upt(x);
}

void solve_F(){
	int x = Query(rt,2),y = Query(rt,n + 2);
	splay(x,0),splay(y,x);
	pushrev(ch[y][0]);
}

void solve_P(){
	int l = read<int>(),r = read<int>(),v = read<int>();
	if(l <= r){
		int x = Query(rt,l),y = Query(rt,r + 2);
		splay(x,0),splay(y,x);
		pushcov(ch[y][0],v);
	}
	else{
		int x = Query(rt,l),y = Query(rt,n + 2);
		splay(x,0),splay(y,x);
		pushcov(ch[y][0],v);

		x = Query(rt,1),y = Query(rt,r + 2);
		splay(x,0),splay(y,x);
		pushcov(ch[y][0],v);
	}
}

void _solve_P(int l,int r,int v){
	int x = Query(rt,l),y = Query(rt,r + 2);
	splay(x,0),splay(y,x);
	pushcov(ch[y][0],v);
}

void solve_S(){
	int pos1 = read<int>(),pos2 = read<int>();
	int vx = val[Query(rt,pos1 + 1)],vy = val[Query(rt,pos2 + 1)];
	_solve_P(pos1,pos1,vy),_solve_P(pos2,pos2,vx);
}

void solve_C(){
	int x = Query(rt,1),y = Query(rt,n + 2);
	splay(x,0),splay(y,x);

	int res = sum[ch[y][0]];
	x = Query(rt,2),y = Query(rt,n + 1);
	res -= (val[x] == val[y]);
	if(!res) res = 1;
	printf("%d\n",res);
}

void solve_CS(){
	int l = read<int>(),r = read<int>();
	int res = 0;
	
	if(l <= r){
		int x = Query(rt,l),y = Query(rt,r + 2);
		splay(x,0),splay(y,x);
		res += sum[ch[y][0]];
		printf("%d\n",res);
	}
	else{
		int x = Query(rt,l),y = Query(rt,n + 2);
		splay(x,0),splay(y,x);
		res += sum[ch[y][0]];
		
		x = Query(rt,1),y = Query(rt,r + 2);
		splay(x,0),splay(y,x);
		res += sum[ch[y][0]];

		x = Query(rt,2),y = Query(rt,n + 1);
		res -= (val[x] == val[y]);
		if(!res) res = 1;
		printf("%d\n",res);
	}
}

int main(){

	n = read<int>(); C = read<int>();
	for(int i = 1;i <= n;i++) A[i] = read<int>();

	A[0] = -INF,A[n + 1] = INF;
	build(rt,0,n + 1,0);

	m = read<int>();

	while(m--){
		scanf("%s",opt);
		if(opt[0] == 'R') solve_R();
		if(opt[0] == 'F') solve_F();
		if(opt[0] == 'P') solve_P();
		if(opt[0] == 'S') solve_S();
		if(opt[0] == 'C' && opt[1] != 'S') solve_C();
		if(opt[0] == 'C' && opt[1] == 'S') solve_CS();
	}

	return 0;
}
