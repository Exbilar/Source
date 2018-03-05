#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: vector;

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

int top,n,m,T;

struct Edge{
	int x,y,l,r;
	Edge(){}
	Edge(int _,int __,int ___,int ____){x = _,y = __,l = ___,r = ____;}
	bool operator < (const Edge &rhs) const {
		return l == rhs.l ? r < rhs.r : l < rhs.l;
	}
};

vector<Edge> vec;

namespace Ufs{

	struct Node{
		int ftr,val,rnk;
	}A[maxm];

	struct Asd{
		Node x,y; int u,v;
		Asd(){}
		Asd(Node _,Node __,int ___,int ____){x = _,y = __,u = ___,v = ____;}
	}stk[maxm];

	void init(){
		for(int i = 1;i <= n;i++) A[i].ftr = i,A[i].rnk = 1,A[i].val = 0;
	}
	
	int find(int x){
		return A[x].ftr == x ? x : find(A[x].ftr);
	}

	int dis(int x){
		int res = 0;
		while(x != A[x].ftr) res ^= A[x].val,x = A[x].ftr;
		return res;
	}
	
	void merge(int x,int y){
		int V = dis(x) ^ dis(y) ^ 1;
		x = find(x),y = find(y);
		stk[++top] = Asd(A[x],A[y],x,y);
		if(A[x].rnk > A[y].rnk) std :: swap(x,y);
		A[x].ftr = y,A[x].val = V,A[y].rnk += A[x].rnk;
	}

	void back(int btm){
		while(top != btm){
			Asd &tmp = stk[top--];
			A[tmp.u] = tmp.x,A[tmp.v] = tmp.y;
		}
	}
	
}

using Ufs :: find;
using Ufs :: merge;
using Ufs :: back;
using Ufs :: dis;

void solve(int l,int r,vector<Edge> &A){
	int mid = (l + r) >> 1,btm = top;
	vector<Edge> B,C;
	for(int i = 0;i < (int)A.size();i++){
		Edge &cur = A[i];
		if(cur.l == l && cur.r == r){
			int u = find(cur.x),v = find(cur.y);
			if(u == v){
				int V = dis(cur.x) ^ dis(cur.y) ^ 1;
				if(V != 0){
					for(int i = l;i <= r;i++) puts("No");
					return back(btm),void();
				}
			}
			else merge(cur.x,cur.y);
		}
		else if(cur.r <= mid) B.push_back(cur);
		else if(cur.l > mid) C.push_back(cur);
		else B.push_back(Edge(cur.x,cur.y,cur.l,mid)),
				 C.push_back(Edge(cur.x,cur.y,mid + 1,cur.r));
	}
	if(l == r) puts("Yes");
	else solve(l,mid,B),solve(mid + 1,r,C);
	back(btm);
}

int main(){
	
	read(n),read(m),read(T);

	int u,v,l,r;
	for(int i = 1;i <= m;i++){
		read(u),read(v),read(l),read(r);
		l += 1;
		if(l > r) continue;
		vec.push_back(Edge(u,v,l,r));
	}

	Ufs :: init();
	solve(1,T,vec);

	return 0;
}
