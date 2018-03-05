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
using std :: make_pair;

typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;
typedef set<int> :: iterator itr;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 2e5 + 10;

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

int ftr[maxm],ch[maxm][2];
int E[maxm << 2],add[maxm << 2];

int opt[maxm],A[maxm],tmp[maxm];

set<int> S;

int rt,m,tot;

void pushup(int x) {
	E[x] = E[x << 1] + E[x << 1 | 1];
}

void pushadd(int x, int v) {
	add[x] += v; E[x] += v;
}

void pushdown(int x) {
	pushadd(x << 1, add[x]);
	pushadd(x << 1 | 1, add[x]);
	add[x] = 0;
}

void modify(int x, int l, int r, int L, int R, int v) {
	if(l >= L && r <= R) return pushadd(x, v),void();
	pushdown(x);
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1, l, mid, L, R, v);
	if(R > mid)  modify(x << 1 | 1, mid + 1, r, L, R, v);
	pushup(x);
}

void __modify(int x, int l, int r, int pos, int v) {
	if(l == r) return E[x] = v,void();
	pushdown(x);
	int mid = (l + r) >> 1;
	if(pos <= mid) __modify(x << 1, l, mid, pos, v);
	else __modify(x << 1 | 1, mid + 1, r, pos , v);
	pushup(x);
}

int Query(int x, int l, int r, int pos) {
	if(l == r) return E[x];
	pushdown(x);
	int mid = (l + r) >> 1;
	if(pos <= mid) return Query(x << 1, l, mid, pos);
	else return Query(x << 1 | 1, mid + 1, r, pos);
}

void splayMin() {
	itr it = S.begin();
	printf("%d\n",Query(1, 1, tot, *it));
	
	if(rt == *it) return ;
	
	if(ftr[*it]) ch[ftr[*it]][0] = ch[*it][1];
	if(ch[*it][1]) ftr[ch[*it][1]] = ftr[*it];
	
	modify(1, 1, tot, ftr[*it], tot, 1); __modify(1, 1, tot, *it, 1);
	
	ftr[rt] = *it; ftr[*it] = 0;
	ch[*it][1] = rt; rt = *it;
}

void splayMax() {
	itr it = S.end(); it--;
	printf("%d\n",Query(1, 1, tot, *it));
	
	if(rt == *it) return ;
	
	if(ftr[*it]) ch[ftr[*it]][1] = ch[*it][0];
	if(ch[*it][0]) ftr[ch[*it][0]] = ftr[*it];
	
	modify(1, 1, tot, 1, ftr[*it], 1); __modify(1, 1, tot, *it, 1);
	
	ftr[rt] = *it; ftr[*it] = 0;
	ch[*it][0] = rt; rt = *it;
}

int main() {

	read(m);
	for(int i = 1;i <= m;i++) {
		read(opt[i]);
		if(opt[i] == 1) read(A[i]),tmp[++tot] = A[i];
	}

	std :: sort(tmp + 1, tmp + tot + 1);
	tot = std :: unique(tmp + 1, tmp + tot + 1) - tmp - 1;
	
	for(int i = 1;i <= m;i++) {
		if(opt[i] == 1) {
			A[i] = std :: lower_bound(tmp, tmp + tot + 1, A[i]) - tmp;
		}
	}

	for(int i = 1;i <= m;i++) {
		if(opt[i] == 1) {
			
			int dpt = 1;
			if(S.empty()) rt = A[i],__modify(1, 1, tot, A[i], 1);
			else {
				itr it = S.lower_bound(A[i]);
				if(ch[*it][0] || it == S.end()) {
					it--,ch[*it][1] = A[i],ftr[A[i]] = *it;
				} else ch[*it][0] = A[i],ftr[A[i]] = *it;
				dpt += Query(1, 1, tot, *it);
				__modify(1, 1, tot, A[i], dpt);
			}
			S.insert(A[i]);
			printf("%d\n",dpt);
			
		}
		else if(opt[i] == 2) splayMin();
		else if(opt[i] == 3) splayMax();
		else if(opt[i] == 4) {			
			splayMin();
			itr it = S.begin(); S.erase(it);
			rt = ch[*it][1]; ftr[rt] = 0;
			modify(1, 1, tot, 1, tot, -1);
			
		} else if(opt[i] == 5) {
			splayMax();
			itr it = S.end(); it--; S.erase(it);
			rt = ch[*it][0]; ftr[rt] = 0;
			modify(1, 1, tot, 1, tot, -1);
			
		}
	}

	return 0;
}
