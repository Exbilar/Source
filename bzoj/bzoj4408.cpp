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

int A[maxm],lc[maxm],rc[maxm],tmp[maxm],sum[maxm],rt[maxm];
int n,m,sz;

void insert(int &x,int lst,int l,int r,int pos,int v){
	x = ++sz; sum[x] = sum[lst] + v; lc[x] = lc[lst],rc[x] = rc[lst];
	if(l == r) return ;
	int mid = (l + r) >> 1;
	if(pos <= mid) insert(lc[x],lc[lst],l,mid,pos,v);
	else insert(rc[x],rc[lst],mid + 1,r,pos,v);
}

int Query(int x,int lst,int l,int r,int pos){
	if(l == r) return sum[x] - sum[lst];
	int mid = (l + r) >> 1;
	if(pos <= mid) return Query(lc[x],lc[lst],l,mid,pos);
	else return Query(rc[x],rc[lst],mid + 1,r,pos) + sum[lc[x]] - sum[lc[lst]];
}

int main(){
	
	read(n);

	for(int i = 1;i <= n;i++) read(A[i]),tmp[i] = A[i];

	std :: sort(tmp + 1,tmp + n + 1);
	int tot = std :: unique(tmp + 1,tmp + n + 1) - tmp - 1;

	for(int i = 1;i <= n;i++){
		A[i] = std :: lower_bound(tmp + 1,tmp + tot + 1,A[i]) - tmp;
	}

	for(int i = 1;i <= n;i++){
		insert(rt[i],rt[i - 1],1,tot,A[i],tmp[A[i]]);
	}

	int l,r;
	
	read(m);
	while(m--){
		scanf("%d%d",&l,&r);
		int ans = 1;
		while(1){
			int asd = std :: upper_bound(tmp + 1,tmp + tot + 1,ans) - tmp - 1;
			int res = Query(rt[r],rt[l - 1],1,tot,asd);
			if(ans > res) break;
			ans = res + 1;
		}
		printf("%d\n",ans);
	}

	return 0;
}
