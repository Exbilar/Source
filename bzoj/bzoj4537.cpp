#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: make_pair;

typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 1e5 + 10;

template <class T> inline bool chkmax(T &x, T y) {
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x, T y) {
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in) {
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if (ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

struct Edge {
	int u,v,a,b,id;

	Edge(int u = 0, int v = 0, int a = 0, int b = 0, int id = 0) :
		u(u), v(v), a(a), b(b), id(id) {}
	
}E[maxm],ask[maxm];

struct Node {
	int x,y,sizey,ay,by;

	Node(int x = 0, int y = 0, int sizey = 0, int ay = 0, int by = 0) :
		x(x), y(y), sizey(sizey), ay(ay), by(by) {}
	
}stk[maxm];

int A[maxm],B[maxm],ftr[maxm],size[maxm],pq[maxm],ans[maxm];
int n,m,Q,Bsize,top;

bool cmpA(const Edge &x,const Edge &y) {
	return x.a == y.a ? x.b < y.b : x.a < y.a;
}

bool cmpB(const Edge &x,const Edge &y) {
	return x.b == y.b ? x.a < y.a : x.b < y.b;
}

int find(int x) {
	return x == ftr[x] ? x : find(ftr[x]);
}

void merge(int x, int y, int a, int b) {
	int fx = find(x),fy = find(y);
	if(size[fx] > size[fy]) std :: swap(fx, fy);
	stk[++top] = Node(fx, fy, size[fy], A[fy], B[fy]);
	if(fx == fy) return chkmax(A[fx], a),chkmax(B[fx], b),void();
	ftr[fx] = fy; size[fy] += size[fx];
	chkmax(A[fy], max(a, A[fx])); chkmax(B[fy], max(b, B[fx]));
}

void back() {
	while(top) {
		Node tp = stk[top--];
		ftr[tp.x] = tp.x; size[tp.y] = tp.sizey;
		A[tp.y] = tp.ay; B[tp.y] = tp.by;
	}
}

int main() {

	read(n); read(m); Bsize = sqrt(m * log2(m));
	for(int i = 1;i <= m;i++) {
		read(E[i].u); read(E[i].v); read(E[i].a); read(E[i].b);
	}
	
	read(Q);
	for(int i = 1;i <= Q;i++) {
		read(ask[i].u); read(ask[i].v); read(ask[i].a); read(ask[i].b);
		ask[i].id = i;
	}

	std :: sort(E + 1, E + m + 1, cmpA);
	std :: sort(ask + 1, ask + Q + 1, cmpB);

	for(int i = 1;i <= m;i += Bsize) {
		int tot = 0;
		for(int j = 1;j <= Q;j++) {
			if(ask[j].a >= E[i].a && (i + Bsize > m || ask[j].a < E[i + Bsize].a)) {
				pq[++tot] = j;
			}
		}
		std :: sort(E + 1,E + i + 1,cmpB);
		for(int j = 1;j <= n;j++) ftr[j] = j,size[j] = 1,A[j] = -1,B[j] = -1;
		for(int j = 1,pos = 1;j <= tot;j++) {
			while(pos < i && (ask[pq[j]].b >= E[pos].b)) {
				merge(E[pos].u, E[pos].v, E[pos].a, E[pos].b),pos++;
			}
			top = 0;
			for(int k = i;k < i + Bsize && k <= m;k++) {
				if((ask[pq[j]].b >= E[k].b) && (ask[pq[j]].a >= E[k].a)) {
					merge(E[k].u, E[k].v, E[k].a ,E[k].b);
				}
			}
			int fx = find(ask[pq[j]].u),fy = find(ask[pq[j]].v);
			if(fx == fy && A[fx] == ask[pq[j]].a && B[fx] == ask[pq[j]].b) ans[ask[pq[j]].id] = 1;
			back();
		}
	}

	for(int i = 1;i <= Q;i++) {
		puts(ans[i] ? "Yes" : "No");
	}

	return 0;
}
