#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 2e5 + 10;

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

int size[maxm],ch[maxm][2],tag[maxm],A1[maxm],D[maxm];
int val[maxm],sum[maxm],ftr[maxm];
int fst[maxm],nxt[maxm],to[maxm],stk[maxm];
int cnt,n,m,top,ans;

char opt[10];

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

void clear(int x){
	size[x] = 1;
	ftr[x] = ch[x][0] = ch[x][1] = 0;
	val[x] = tag[x] = A1[x] = D[x] = sum[x] = 0;
}

int get(int x){
	return ch[ftr[x]][1] == x;
}

int isrt(int x){
	return ch[ftr[x]][0] != x && ch[ftr[x]][1] != x;
}

void upt(int x){
	size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
}

void pushtag1(int x,int v){
	val[x] += v,tag[x] += v;
}

void pushtag2(int x,int a1,int d){
	A1[x] += a1; D[x] += d;
	sum[x] += a1 + size[ch[x][1]] * d;
}

void pushdown(int x){
	if(tag[x]){
		if(ch[x][0]) pushtag1(ch[x][0],tag[x]);
		if(ch[x][1]) pushtag1(ch[x][1],tag[x]);
	}
	if(D[x]){
		if(ch[x][0]) pushtag2(ch[x][0],A1[x] + (size[ch[x][1]] + 1) * D[x],D[x]);
		if(ch[x][1]) pushtag2(ch[x][1],A1[x],D[x]);
	}
	tag[x] = 0,A1[x] = 0,D[x] = 0;
}

void pushbtm(int x){
	top = 0; stk[++top] = x;
	for(int i = x;!isrt(i);i = ftr[i]){
		if(!i) assert(0);
		stk[++top] = ftr[i];
	}
	while(top) pushdown(stk[top--]);
}

void rotate(int x){
	int fa = ftr[x],gnd = ftr[fa],f = get(x);
	if(!isrt(fa)) ch[gnd][get(fa)] = x;
	ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
	ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
	upt(fa),upt(x);
}

void splay(int x){
	pushbtm(x);
	for(x;!isrt(x);rotate(x))
		if(!isrt(ftr[x])) rotate(get(x) == get(ftr[x]) ? ftr[x] : x);
}

void access(int x){
	for(int y = 0;x;y = x,x = ftr[x]){
		splay(x); ch[x][1] = y; upt(x);
	}
}

int getroot(int x){
	access(x); splay(x);
	while(ch[x][0]) x = ch[x][0];
	return x;
}

void modify(int x,int y){
	clear(x),ftr[x] = y;
	y = getroot(y); access(x); splay(y); // make x y in the same splay
	pushtag1(y,1),pushtag2(y,0,1);

	x = ch[y][1];
	while(ch[x][0]) x = ch[x][0];
	splay(x);  // find y's son in the real tree

	// consider to change the root
	int v1 = val[y],v2 = val[x];
	if((v2 << 1) > v1){
		val[x] = v1,val[y] -= v2;
		sum[y] -= sum[x] + v2; sum[x] += sum[y] + v1 - v2;
		access(x); splay(y); ch[y][0] = x,ch[y][1] = 0;
	}
}

void dfs(int x,int fa){
	modify(x,fa);
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == fa) continue;
		dfs(v,x);
	}
}

void link(int x,int y){
	int rtx = getroot(x),rty = getroot(y);
	ans -= sum[rtx] + sum[rty];
	if(val[rtx] < val[rty]) std :: swap(x,y);
	dfs(y,x); ins(x,y);
	ans += sum[getroot(x)];
}

int main(){
	
	read(n),read(m);
	for(int i = 1;i <= n;i++) val[i] = size[i] = 1;

	int x,y;
	while(m--){
		scanf("%s",opt);
		if(opt[0] == 'A') read(x),read(y),link(x,y);
		if(opt[0] == 'Q') printf("%d\n",ans);
	}

	return 0;
}
