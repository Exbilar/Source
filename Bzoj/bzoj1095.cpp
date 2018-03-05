#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 3e5 + 10;
static const int maxn = 2e6 + 10;

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

int fst[maxm],nxt[maxm],to[maxm],col[maxm],ddf[maxm],pos[maxm];
int cnt,tot,n,m;

char opt[10];

struct node{
	int l1,r1,l2,r2,c1,c2,dis;
	void init(int x){
		dis = -INF,c1 = c2 = 0;
		if(ddf[x] == -1) c2 = 1;
		if(ddf[x] == -2) c1 = 1;
		if(ddf[x] > 0 && col[ddf[x]]) l1 = l2 = r1 = r2 = 0;
		else l1 = l2 = r1 = r2 = -INF;
	}
}T[maxn];

node operator + (const node &A,const node &B){
	node res;
	
	int a = A.c1,b = A.c2,c = B.c1,d = B.c2;

	res.dis = max(A.dis,B.dis);
	res.dis = max(res.dis,max(A.r1 + B.l2,A.r2 + B.l1));

	if(b < c) res.c1 = a - b + c,res.c2 = d;
	else res.c1 = a,res.c2 = b - c + d;

	res.l1 = max(A.l1,max(B.l1 - b + a,B.l2 + b + a));
	res.l2 = max(A.l2,B.l2 + b - a);

	res.r1 = max(B.r1,max(A.r1 - c + d,A.r2 + c + d));
	res.r2 = max(B.r2,A.r2 + c - d);
	
	return res;
}

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

void build(int x,int l,int r){
	if(l == r) return T[x].init(l),void();
	int mid = (l + r) >> 1;
	build(x << 1,l,mid);
	build(x << 1 | 1,mid + 1,r);
	T[x] = T[x << 1] + T[x << 1 | 1];
}

void modify(int x,int l,int r,int pos){
	if(l == r) return T[x].init(l),void();
	int mid = (l + r) >> 1;
	if(pos <= mid) modify(x << 1,l,mid,pos);
	else modify(x << 1 | 1,mid + 1,r,pos);
	T[x] = T[x << 1] + T[x << 1 | 1];
}

void dfs(int x,int fa){
	ddf[++tot] = -1;
	ddf[++tot] = x;
	pos[x] = tot;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == fa) continue;
		dfs(v,x);
	}
	ddf[++tot] = -2;
}

int main(){

	read(n);
	int num = n,u,v;
	for(int i = 1;i <= n;i++) col[i] = 1;

	for(int i = 1;i < n;i++){
		read(u),read(v);
		ins(u,v);
	}

	dfs(1,0);
	build(1,1,tot);

	read(m);

	while(m--){
		scanf("%s",opt);
		if(opt[0] == 'C'){
			read(u);
			if(col[u]) num--;
			else num++;
			col[u] ^= 1;
			modify(1,1,tot,pos[u]);
		}
		if(opt[0] == 'G'){
			if(!num) puts("-1");
			else if(num == 1) puts("0");
			else printf("%d\n",T[1].dis);
		}
	}
	
	return 0;
}
