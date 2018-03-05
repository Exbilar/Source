#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: set;
using std :: pair;
using std :: swap;
using std :: stack;
using std :: queue;
using std :: make_pair;

typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;
typedef set<int> :: iterator itr;
typedef set<int> :: reverse_iterator ritr;

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

int lc[maxm * 20],rc[maxm * 20],size[maxm * 20],rt[maxm];

stack<int> rub;

int sz;

int newnode() {
	int new_one;
	if(rub.empty()) new_one = ++sz;
	else new_one = rub.top(),rub.pop();
	lc[new_one] = rc[new_one] = size[new_one] = 0;
	return new_one;
}

void erase(int x) {
	rub.push(x);
}

void build(int &x,int l,int r,int pos) {
	x = ++sz; size[x] = 1;
	if(l == r) return ;
	int mid = (l + r) >> 1;
	if(pos <= mid) build(lc[x],l,mid,pos);
	else build(rc[x],mid + 1,r,pos);
}

int merge(int x,int y) {
	if(!x || !y) return x ^ y;
	size[x] += size[y];
	lc[x] = merge(lc[x],lc[y]);
	rc[x] = merge(rc[x],rc[y]);
	return erase(y),x;
}

void splitR(int x,int &y,int k) {
	y = newnode();
	size[y] = size[x] - k; size[x] = k;
	if(size[lc[x]] < k) splitR(rc[x],rc[y],k - size[lc[x]]);
	else swap(rc[x],rc[y]);
	if(size[lc[x]] > k) splitR(lc[x],lc[y],k);
}

void splitL(int x,int &y,int k) {
	y = newnode();
	size[y] = size[x] - k; size[x] = k;
	if(size[rc[x]] < k) splitL(lc[x],lc[y],k - size[rc[x]]);
	else swap(lc[x],lc[y]);
	if(size[rc[x]] > k) splitL(rc[x],rc[y],k);
}

int Query(int x,int l,int r,int pos) {
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(pos <= size[lc[x]]) return Query(lc[x],l,mid,pos);
	else return Query(rc[x],mid + 1,r,pos - size[lc[x]]);
}

set<int> ddf;

int typ[maxm],A[maxm],boy[maxm];

// boy[x] is x's next ♂ door's pos

int n,m;

// y is boy next ♂ door

void boyMerge(int x,int y) {
	if(x == y) return ;
	ddf.erase(y);
	rt[x] = merge(rt[x],rt[y]);
	boy[x] = boy[y];
}

int findpos(int x,int k) {
	k -= x - 1;
	if(!typ[x]) return Query(rt[x],1,n,k);
	else return Query(rt[x],1,n,boy[x] - (x - 1) - (k - 1));
}

void boySplit(int L,int R) {
	if(L > R || R >= boy[L]) return ;
	if(!typ[L]) splitR(rt[L],rt[R + 1],R - L + 1);
	else splitL(rt[L],rt[R + 1],R - L + 1);
	boy[R + 1] = boy[L]; boy[L] = R;
	ddf.insert(R + 1); typ[R + 1] = typ[L];
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("bzoj4552.in","r",stdin);
#endif
	
	read(n); read(m);
	for(int i = 1;i <= n;i++) {
		read(A[i]); build(rt[i],1,n,A[i]);
		ddf.insert(i); boy[i] = i;
	}

	int opt,l,r;
	while(m--) {
		read(opt); read(l); read(r);
		itr it1 = ddf.upper_bound(l);
		boySplit(*(--it1),l - 1);
		itr it2 = ddf.upper_bound(r);
		boySplit(*(--it2),r);

		itr end = ddf.upper_bound(r);
		queue<int> asd;
		itr it = ddf.lower_bound(l); int boyNextDoor = *it;

		if(it != end) {
			++it;
			while(it != end) {
				asd.push(*it);
				it++;
			}
			while(!asd.empty()) {
				boyMerge(boyNextDoor,asd.front());
				asd.pop();
			}
		}
		typ[boyNextDoor] = opt;
	}

	int pos;
	read(pos);

	itr aslkdjaskldsjadklasjdl = ddf.upper_bound(pos);
	aslkdjaskldsjadklasjdl--;

	printf("%d\n",findpos(*(aslkdjaskldsjadklasjdl),pos));

	return 0;
}
