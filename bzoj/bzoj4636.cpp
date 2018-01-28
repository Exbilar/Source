#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1e9 + 10;
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

int smax[maxm * 20],lc[maxm * 20],rc[maxm * 20];
int rt,sz,n;
LL ans;

void insert(int &x,int l,int r,int L,int R,int v){
	if(!x) x = ++sz;
	if(l >= L && r <= R) return chkmax(smax[x],v),void();
	int mid = (l + r) >> 1;
	if(L <= mid) insert(lc[x],l,mid,L,R,v);
	if(R > mid) insert(rc[x],mid + 1,r,L,R,v);
}

void Query(int x,int l,int r,int v){
	if(!x) return ;
	chkmax(smax[x],v);
	if(!lc[x] && !rc[x]) return ans += 1LL * (r - l + 1) * smax[x],void();
	int mid = (l + r) >> 1;
	Query(lc[x],l,mid,smax[x]); Query(rc[x],mid + 1,r,smax[x]);
	if(!lc[x]) ans += 1LL * (mid - l + 1) * smax[x];
	if(!rc[x]) ans += 1LL * (r - mid) * smax[x];
}

int main(){

	freopen("bzoj4636.in","r",stdin);
	
	read(n);

	int l,r,k;
	
	while(n--){
		read(l),read(r),read(k);
		if(l >= r) continue;
		insert(rt,1,INF,l,r - 1,k);
	}

	Query(rt,1,INF,0);

	printf("%lld\n",ans);

	return 0;
}
