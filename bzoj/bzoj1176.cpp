#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 3e6 + 10;

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

struct Query{
	int x,y,val,pos,id,opt;
	bool operator < (const Query &Q) const {
		if(x == Q.x && y == Q.y) return opt < Q.opt;
		return x == Q.x ? y < Q.y : x < Q.x;
	}
}Q[maxm],tmp[maxm];

int ans[maxm],bit[maxm];
int H,W,m,cnt;

void addQuery(){
	int x1,x2,y1,y2;
	read(x1),read(y1),read(x2),read(y2);
	
	int cur = ++cnt;
	
	Q[++m].pos = cur,Q[m].id = m,Q[m].x = x1 - 1;
	Q[m].y = y1 - 1,Q[m].val = 1,Q[m].opt = 1;

	Q[++m].pos = cur,Q[m].id = m,Q[m].x = x2;
	Q[m].y = y2,Q[m].val = 1,Q[m].opt = 1;

	Q[++m].pos = cur,Q[m].id = m,Q[m].x = x1 - 1;
	Q[m].y = y2,Q[m].val = -1,Q[m].opt = 1;

	Q[++m].pos = cur,Q[m].id = m,Q[m].x = x2;
	Q[m].y = y1 - 1,Q[m].val = -1,Q[m].opt = 1;
}

int lowbit(int x){
	return x & -x;
}

void Upt(int k,int v){
	for(int i = k;i <= W;i += lowbit(i)) bit[i] += v;
}

int Qry(int k){
	int res = 0;
	for(int i = k;i;i -= lowbit(i)) res += bit[i];
	return res;
}

void CDQ(int l,int r){
	if(l == r) return ;
	int mid = (l + r) >> 1;
	for(int i = l;i <= r;i++){
		if(Q[i].id <= mid && !Q[i].opt) Upt(Q[i].y,Q[i].val);
		if(Q[i].id > mid && Q[i].opt) ans[Q[i].pos] += Q[i].val * Qry(Q[i].y);
	}
	for(int i = l;i <= r;i++)
		if(Q[i].id <= mid && !Q[i].opt) Upt(Q[i].y,-Q[i].val);

	int head = l,tail = mid + 1;
	for(int i = l;i <= r;i++)
		if(Q[i].id <= mid) tmp[head++] = Q[i];
		else tmp[tail++] = Q[i];
	
	for(int i = l;i <= r;i++) Q[i] = tmp[i];
	
	CDQ(l,mid); CDQ(mid + 1,r);
}

int main(){

	freopen("bzoj1176.in","r",stdin);
	
	read(H),read(W);

	int opt;
	while(1){
		read(opt);
		if(opt == 1){
			read(Q[++m].x),read(Q[m].y),read(Q[m].val);
			Q[m].id = m;
		}
		if(opt == 2) addQuery();
		if(opt == 3) break;
	}

	std :: sort(Q + 1,Q + m + 1);

	CDQ(1,m);

	for(int i = 1;i <= cnt;i++){
		printf("%d\n",ans[i]);
	}

	return 0;
}
