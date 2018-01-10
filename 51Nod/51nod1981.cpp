#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: bitset;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e4 + 10;
static const int maxn = 65536;

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

void output(int x){
	if(x == -1) return putchar('-'),putchar('1'),void();
	if(x / 10) output(x / 10);
	putchar(x % 10 + '0');
}

bitset<maxm> sum[maxn << 1],tag[maxn << 1];
bitset<maxm> bit[maxm],f,tmp;

int n,m;

void pushup(int x){
	int lc = x << 1,rc = x << 1 | 1;
	sum[x] |= sum[lc],sum[x] |= sum[rc];
}

void modify(int x,int l,int r,int L,int R,int v){
	if(l >= L && r <= R){
		sum[x][v] = 1,tag[x][v] = 1;
		return ;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1,l,mid,L,R,v);
	if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,v);
	pushup(x);
}

bitset<maxm> Query(int x,int l,int r,int L,int R){
	if(l >= L && r <= R){
		return sum[x];
	}
	int mid = (l + r) >> 1;
	bitset<maxm> res = tag[x];
	if(L <= mid) res |= Query(x << 1,l,mid,L,R);
	if(R > mid) res |= Query(x << 1 | 1,mid + 1,r,L,R);
	return res;
}

int solve(int L,int R,int k){
	f = Query(1,1,n,L,R);
	if(f.count() < k) return -1;

	int l = 0,r = 10000;
	while(l <= r){
		int mid = (l + r) >> 1;
		tmp = f & bit[mid];
		if(tmp.count() < k) l = mid + 1;
		else r = mid - 1;
	}
	tmp = f & bit[l];
	return tmp.count() == k ? l : r;
}

int main(){

	freopen("51nod1981.in","r",stdin);
	
	read(n),read(m);
	
	bit[0][0] = 1;
	for(int i = 1;i <= 10000;i++) bit[i] = bit[i - 1],bit[i][i] = 1;

	int opt,l,r,k;
	
	while(m--){
		read(opt),read(l),read(r),read(k);
		if(opt == 1) modify(1,1,n,l,r,k);
		if(opt == 2) output(solve(l,r,k)),putchar(10);
	}
	
	return 0;
}
