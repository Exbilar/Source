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

LL sum[maxm],same[maxm],tag[maxm];
int n,m;

void pushup(int x){
	int lc = x << 1,rc = x << 1 | 1;
	sum[x] = sum[lc] + sum[rc];
	if(same[lc] != same[rc]) same[x] = -1;
	else same[x] = same[lc];
}

void pushdown(int x,int l,int r){
	int lc = x << 1,rc = x << 1 | 1,mid = (l + r) >> 1;
	sum[lc] += 1LL * tag[x] * (mid - l + 1);
	sum[rc] += 1LL * tag[x] * (r - mid);
	same[lc] = same[x],same[rc] = same[x];
	tag[lc] += tag[x],tag[rc] += tag[x];
	tag[x] = 0;
}

void build(int x,int l,int r){
	same[x] = -1;
	if(l == r) return same[x] = l,void();
	int mid = (l + r) >> 1;
	build(x << 1,l,mid);
	build(x << 1 | 1,mid + 1,r);
	pushup(x);
}

void modify(int x,int l,int r,int L,int R,int v){
	if(l >= L && r <= R && same[x] != -1){
		sum[x] += 1LL * (r - l + 1) * abs(v - same[x]);
		tag[x] += abs(v - same[x]);
		same[x] = v;
		return ;
	}
	if(tag[x]) pushdown(x,l,r);
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1,l,mid,L,R,v);
	if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,v);
	pushup(x);
}

LL Query(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return sum[x];
	int mid = (l + r) >> 1; LL res = 0;
	if(tag[x]) pushdown(x,l,r);
	if(L <= mid) res += Query(x << 1,l,mid,L,R);
	if(R > mid) res += Query(x << 1 | 1,mid + 1,r,L,R);
	return res;
}

int main(){
	
	int l,r,x,opt;
	read(n),read(m);
	build(1,1,n);

	while(m--){
		read(opt);
		if(opt == 1) read(l),read(r),read(x),modify(1,1,n,l,r,x);
		if(opt == 2) read(l),read(r),printf("%lld\n",Query(1,1,n,l,r));
	}
	
	return 0;
}
