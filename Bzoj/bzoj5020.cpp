#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

using std :: max;
using std :: min;
using std :: swap;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 3e5 + 10;
static const int Rn_MAX = 11;

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

int rev[maxm],ftr[maxm],ch[maxm][2];
double sum[maxm][21],val[maxm][21];
int n,m;

char typ[10];

void upt(int x) {
	for(int i = 0;i <= Rn_MAX;i++) {
		sum[x][i] = sum[ch[x][0]][i] + sum[ch[x][1]][i] + val[x][i];
	}
}

int get(int x) {
	return ch[ftr[x]][1] == x;
}

int isrt(int x) {
	return ch[ftr[x]][0] != x && ch[ftr[x]][1] != x;
}

void rotate(int x) {
	int fa = ftr[x],gnd = ftr[fa],f = get(x);
	if(!isrt(fa)) ch[gnd][get(fa)] = x;
	ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
	ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
	upt(fa),upt(x);
}

void pushrev(int x) {
	swap(ch[x][0],ch[x][1]);
	rev[x] ^= 1;
}

void pushdown(int x) {
	if(rev[x]) {
		if(ch[x][0]) pushrev(ch[x][0]);
		if(ch[x][1]) pushrev(ch[x][1]);
		rev[x] = 0;
	}
}

void pushbtm(int x) {
	if(!isrt(x)) pushbtm(ftr[x]);
	pushdown(x);
}

void splay(int x) {
	pushbtm(x);
	for(int fa = x;!isrt(x);rotate(x)) {
		if(!isrt(fa = ftr[x])) rotate(get(x) == get(fa) ? fa : x);
	}
}

void access(int x) {
	for(int y = 0;x;y = x,x = ftr[x]) {
		splay(x),ch[x][1] = y,upt(x);
	}
}

void makert(int x) {
	access(x),splay(x);
	pushrev(x);
}

int findrt(int x) {
	access(x),splay(x);
	while(ch[x][0]) x = ch[x][0];
	return x;
}

void link(int x,int y) {
	makert(x),ftr[x] = y;
}

void cut(int x,int y) {
	makert(x),access(y),splay(y);
	ch[y][0] = ftr[x] = 0;
	upt(y);
}

void modify(int x,double a,double b,int f) {
	double expN = a,SINB = sin(b),COSB = cos(b);
	memset(val[x],0,sizeof val[x]);
	
#define opt(i) val[x][i] = val[x][i - 1] * a / i
#define OPT(i) val[x][i] = val[x][i - 4] * expN / (i - 3) / (i - 2) / (i - 1) / i
	
	if(f == 1) {
		val[x][0] = SINB;
		val[x][1] = COSB * expN; expN *= a;
		val[x][2] = -(SINB * expN) / 2.0; expN *= a;
		val[x][3] = -(COSB * expN) / 6.0; expN *= a;
		val[x][4] = (SINB * expN) / 24.0;
		for(int i = 5;i <= Rn_MAX;i++) val[x][i] = val[x][i - 4] * expN / (i - 3) / (i - 2) / (i - 1) / i;
	}
	else if(f == 2) {
		val[x][0] = exp(b);
		for(int i = 1;i <= Rn_MAX;i++) val[x][i] = val[x][i - 1] * a / i;
	}
	else if(f == 3) {
		val[x][0] = b,val[x][1] = a;
	}
	else puts("hi");
	
	upt(x);
	
#undef OPT
#undef opt
}

void Query(int x,int y,double v) {
	if(findrt(x) != findrt(y)) return puts("unreachable"),void();
	makert(x); access(y); splay(y);
	double res = 0.0,expN = 1.0;
	for(int i = 0;i <= Rn_MAX;i++) {
		res += sum[y][i] * expN;
		expN *= v;
	}
	printf("%.8le\n",res);
}

int main() {
	
	read(n),read(m);
	scanf("%s",typ);

	double a,b;
	int x,y,f;
	
	for(int i = 1;i <= n;i++) {
		scanf("%d%lf%lf",&f,&a,&b);
		modify(i,a,b,f);
	}
	
	while(m--) {
		scanf("%s",typ);
		if(typ[0] == 'a') {
			read(x),read(y);
			link(++x,++y);
		}
		if(typ[0] == 'd') {
			read(x),read(y);
			cut(++x,++y);
		}
		if(typ[0] == 'm') {
			scanf("%d%d%lf%lf",&x,&f,&a,&b);
			splay(++x); modify(x,a,b,f);
		}
		if(typ[0] == 't') {
			scanf("%d%d%lf",&x,&y,&a);
			Query(++x,++y,a);
		}
	}
	
	return 0;
}
