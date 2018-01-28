#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: set;

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

struct Node{
	double x,y;

	Node(){x = 0,y = 0;}
	Node(double _,double __){x = _,y = __;}
	
	bool operator < (const Node &rhs) const {
		return x == rhs.x ? y < rhs.y : x < rhs.x;
	}

	double operator * (const Node &rhs) const {
		return x * rhs.y - rhs.x * y;
	}

	Node operator + (const Node &rhs) const {
		return Node(x + rhs.x,y + rhs.y);
	}
	
	Node operator - (const Node &rhs) const {
		return Node(x - rhs.x,y - rhs.y);
	}
	
}Pts[maxm],del[maxm],cap;

int vis[maxm],ddf[maxm];
double ans[maxm];

double cur;

int n,m,Q;

set<Node> S;

typedef set<Node> :: iterator itr;

double sqr(double x){
	return x * x;
}

double getDis(Node Nx,Node Ny){
	return sqrt(sqr(Nx.x - Ny.x) + sqr(Nx.y - Ny.y));
}

void insert(Node _ins){
	itr r = S.lower_bound(_ins),l = r; l--;
	itr tmp;
	
	if((*r - *l) * (_ins - *l) < 0) return ;
	
	cur -= getDis(*l,*r);

	while(1){
		tmp = r,r++;
		if(r == S.end()) break;
		if((*r - _ins) * (*tmp - _ins) > 0) break;
		cur -= getDis(*tmp,*r);
		S.erase(tmp);
	}

	while(l != S.begin()){
		tmp = l,l--;
		if((*tmp - _ins) * (*l - _ins) > 0) break;
		cur -= getDis(*tmp,*l);
		S.erase(tmp);
	}

	S.insert(_ins);
	l = r = S.find(_ins);
	l--,r++;
	cur += getDis(*l,_ins) + getDis(_ins,*r);
}

int main(){
	
	read(n);
	S.insert(Node(0,0)),S.insert(Node(n,0));
	
	read(cap.x),read(cap.y);
	S.insert(cap);

	cur += getDis(Node(0,0),cap),cur += getDis(cap,Node(n,0));

	read(m);

	for(int i = 1;i <= m;i++){
		read(Pts[i].x),read(Pts[i].y);
	}

	int pos1 = 0,pos2 = 0;
	
	read(Q);
	for(int i = 1;i <= Q;i++){
		int opt,x;
		read(opt);
		if(opt == 1) read(x),vis[x] = 1,del[++pos1] = Pts[x];
		if(opt == 2) ddf[++pos2] = pos1;
	}

	for(int i = 1;i <= m;i++)
		if(!vis[i]) insert(Pts[i]);

	int pos = pos1;
	for(int i = pos2;i >= 1;i--){
		while(pos > ddf[i]){
			insert(del[pos]);
			pos--;
		}
		ans[i] = cur;
	}

	for(int i = 1;i <= pos2;i++){
		printf("%.2lf\n",ans[i]);
	}
	
	return 0;
}
