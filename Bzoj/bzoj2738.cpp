#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1000000 + 10;
static const int maxn = 3000 + 10;

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

struct Element{
	int x,y,v;
	bool operator < (const Element &E) const {
		return v < E.v;
	}
}A[maxm];

struct Query{
	int x1,y1,x2,y2,kth;
}Q[maxm];

int ans[maxm],idx[maxm],tmp[maxm],cur[maxm];
int bit[maxn][maxn];
int n,m,sz;

int lowbit(int x){
	return x & -x;
}

void Upt(int x,int y,int v){
	for(int i = x;i <= n;i += lowbit(i))
		for(int j = y;j <= n;j += lowbit(j)) bit[i][j] += v;
}

int Qry(int x,int y){
	int res = 0;
	for(int i = x;i;i -= lowbit(i))
		for(int j = y;j;j -= lowbit(j)) res += bit[i][j];
	return res;
}

int Query(int x1,int y1,int x2,int y2){
	return Qry(x2,y2) - Qry(x2,y1 - 1) - Qry(x1 - 1,y2) + Qry(x1 - 1,y1 - 1);
}

void solve(int l,int r,int ql,int qr){
	if(ql > qr) return ;
	if(l == r){
		for(int i = ql;i <= qr;i++) ans[idx[i]] = A[l].v;
		return ;
	}

	int mid = (l + r) >> 1;
	for(int i = l;i <= mid;i++) Upt(A[i].x,A[i].y,1);

	int pos1 = ql,pos2 = qr;
	
	for(int i = ql;i <= qr;i++){
		int sum = Query(Q[idx[i]].x1,Q[idx[i]].y1,Q[idx[i]].x2,Q[idx[i]].y2);
		if(sum + cur[idx[i]] >= Q[idx[i]].kth) tmp[pos1++] = idx[i];
		else cur[idx[i]] += sum,tmp[pos2--] = idx[i];
	}

	for(int i = ql;i <= qr;i++) idx[i] = tmp[i];

	for(int i = l;i <= mid;i++) Upt(A[i].x,A[i].y,-1);

	solve(l,mid,ql,pos1 - 1),solve(mid + 1,r,pos2 + 1,qr);
}

int main(){

	read(n),read(m);

	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			read(A[++sz].v),A[sz].x = i,A[sz].y = j;
		}
	}

	for(int i = 1;i <= m;i++){
		read(Q[i].x1),read(Q[i].y1);
		read(Q[i].x2),read(Q[i].y2);
		read(Q[i].kth),idx[i] = i;
	}

	std :: sort(A + 1,A + sz + 1);

	solve(1,sz,1,m);

	for(int i = 1;i <= m;i++) printf("%d\n",ans[i]);
	
	return 0;
}
