#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: list;
using std :: make_pair;

typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 6e6 + 10;
static const int maxn = 1e6 + 10;

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

list<pii> tag[maxm],sum[maxm];
int xi[maxn],yi[maxn],li[maxn],tmp[maxn],f[maxn];
int tot,L,n;

void insert(int x,int l,int r,int L,int R,pii v) {
	if(l >= L && r <= R) {
		while(!tag[x].empty() && tag[x].back().py >= v.py) tag[x].pop_back();
		tag[x].push_back(v);
		return ;
	}

	while(!sum[x].empty() && sum[x].back().py >= v.py) sum[x].pop_back();
	sum[x].push_back(v);
	
	int mid = (l + r) >> 1;
	if(L <= mid) insert(x << 1,l,mid,L,R,v);
	if(R > mid) insert(x << 1 | 1,mid + 1,r,L,R,v);
}

int Query(int x,int l,int r,int L,int R,int v) {
	int res = INF;
	
	while(!tag[x].empty() && tag[x].front().px < v) {
		tag[x].pop_front();
	}
	if(!tag[x].empty()) res = tag[x].front().py;

	while(!sum[x].empty() && sum[x].front().px < v) {
		sum[x].pop_front();
	}
	
	if(l >= L && r <= R) {
		if(!sum[x].empty()) chkmin(res,sum[x].front().py);
		return res;
	}

	int mid = (l + r) >> 1;
	if(L <= mid) chkmin(res,Query(x << 1,l,mid,L,R,v));
	if(R > mid) chkmin(res,Query(x << 1 | 1,mid + 1,r,L,R,v));
	
	return res;
}

int main() {

	read(n); read(L);
	for(int i = 2;i <= n;i++) {
		read(xi[i]),read(yi[i]),read(li[i]);
		tmp[++tot] = xi[i];
		tmp[++tot] = yi[i];
	}

	std :: sort(tmp + 1,tmp + tot + 1);
	tot = std :: unique(tmp + 1,tmp + tot + 1) - tmp - 1;

	xi[1] = tmp[1],yi[1] = tmp[tot];
	for(int i = 1;i <= n;i++) {
		xi[i] = std :: lower_bound(tmp + 1,tmp + tot + 1,xi[i]) - tmp;
		yi[i] = std :: lower_bound(tmp + 1,tmp + tot + 1,yi[i]) - tmp;
	}

	for(int i = 1;i <= n;i++) f[i] = INF;
	
	insert(1,1,tot,1,tot,make_pair(L,0));

	for(int i = 2;i <= n;i++) {
		f[i] = Query(1,1,tot,xi[i],yi[i],li[i]) + 1;
		insert(1,1,tot,xi[i],yi[i],make_pair(li[i] + L,f[i]));
	}

	for(int i = 2;i <= n;i++) {
		printf("%d\n",f[i] >= INF ? -1 : f[i]);
	}
	
	return 0;
}
