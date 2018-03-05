#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: max;
using std :: min;
using std :: swap;

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

template <typename T> inline void read (T &in){
	in = 0; char ch = getchar(); T f = 1;
	for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
	for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

int size[maxm],rev[maxm],ftr[maxm],ch[maxm][2],stk[maxm],dsu[maxm];
int top,n,m;

int isrt(int x){
	return ch[ftr[x]][0] != x && ch[ftr[x]][1] != x;
}

int get(int x){
	return ch[ftr[x]][1] == x;
}

void upt(int x){
	size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
}

void rotate(int x){
	int fa = ftr[x],gnd = ftr[fa],f = get(x);
	if(!isrt(fa)) ch[gnd][get(fa)] = x;
	ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
	ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
	upt(fa),upt(x);
}

void pushrev(int x){
	swap(ch[x][0],ch[x][1]);
	rev[x] ^= 1;
}

void pushdown(int x){
	if(rev[x]){
		if(ch[x][0]) pushrev(ch[x][0]);
		if(ch[x][1]) pushrev(ch[x][1]);
		rev[x] ^= 1;
	}
}

void downbtm(int x){
	if(!isrt(x)) downbtm(ftr[x]);
	pushdown(x);
}

void splay(int x){
	downbtm(x);
	for(int fa = ftr[x];!isrt(x);rotate(x),fa = ftr[x])
		if(!isrt(fa)) rotate(get(fa) == get(x) ? fa : x);
}

void access(int x){
	for(int y = 0;x;y = x,x = ftr[x])
		splay(x),ch[x][1] = y,upt(x);
}

void makert(int x){
	access(x),splay(x),pushrev(x);
}

void link(int x,int y){
	makert(x),ftr[x] = y;
}

void split(int x,int y){
	makert(x),access(y),splay(y);
}

void cut(int x,int y){
	split(x,y),ch[y][0] = ftr[x] = 0,upt(y);
}

int dis(int x,int y){
	split(x,y);
	return size[y] - 1;
}

struct diameter{
	int x[2];
	diameter(int _x = 0,int _y = 0){x[0] = _x,x[1] = _y;}
}dia[maxm];

diameter operator + (const diameter &u,const diameter &v){
	diameter res = u;
	int d0 = dis(u.x[0],u.x[1]),d1 = dis(v.x[0],v.x[1]);
	int maxd = d0;
	if(d0 < d1) maxd = d1,res = v;
	for(int i = 0;i < 2;i++)
		for(int j = 0;j < 2;j++)
			if(chkmax(maxd,dis(u.x[i],v.x[j]))) res.x[0] = u.x[i],res.x[1] = v.x[j];
	
	return res;
}

int find(int x){
	return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
}

bool merge(int x,int y){
	x = find(x),y = find(y);
	if(x != y) return dsu[x] = y,dia[y] = dia[y] + dia[x],true;
	return false;
}

int Query(int x){
	int y = find(x),res = 0;
	for(int i = 0;i < 2;i++) chkmax(res,dis(x,dia[y].x[i]));
	return res;
}

int main(){
	
	int type = 0;
	
	read(type);
	read(n),read(m);
	
	int lstans = 0,opt = 0,u = 0,v = 0;
	
	for(int i = 1;i <= n;i++) dia[i] = diameter(i,i),dsu[i] = i,size[i] = 1;
	
	while(m--){
		read(opt);
		if(opt == 1){
			read(u),read(v);
			u ^= (type * lstans),v ^= (type * lstans);
			link(u,v),merge(u,v);
		}
		if(opt == 2)
			read(u),u ^= (type * lstans),printf("%d\n",lstans = Query(u));
	}
	
	return 0;
}
