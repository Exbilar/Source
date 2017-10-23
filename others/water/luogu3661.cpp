#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)

using std :: max;
using std :: min;
using std :: set;
using std :: pair;
using std :: make_pair;
using std :: vector;
using std :: queue;
using std :: multiset;
using std :: priority_queue;

typedef long long LL;
typedef pair<int,int> pii;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

template <class T> void read(T &in){
	in = 0; int f = 1 ;char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

template <class T> inline bool chkmax(T &x,T y){
	return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
	return x > y ? x = y,true : false;
}

struct Segment{
	int l,r;
	bool operator < (const Segment &Seg) const {
		return r == Seg.r ? l < Seg.l : r < Seg.r;
	}
}seg[maxm];

int T[maxm];
int N,C;

multiset<int> S;

typedef multiset<int> :: iterator itr;

int main(){
	read(C),read(N);
	for(int i = 1;i <= C;i++) read(T[i]),S.insert(T[i]);
	for(int i = 1;i <= N;i++) read(seg[i].l),read(seg[i].r);
	
	std :: sort(seg + 1,seg + N + 1);
	
	int ans = 0;
	for(int i = 1;i <= N;i++){
		itr it = S.lower_bound(seg[i].l);
		if(*it <= seg[i].r && it != S.end()){
			ans++;
			S.erase(it);
		}
	}
	
	printf("%d\n",ans);
	
	return 0;
}
