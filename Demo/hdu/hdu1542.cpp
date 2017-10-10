#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm = 2e1 + 10;

struct Edge{
	double l,r,h;
	int f;
	Edge(){}
	Edge(double a,double b,double c,int d){l = a,r = b,h = c,f = d;}
	bool operator < (const Edge &E) const {
		return h < E.h;
	}
}E[maxm];

double X[maxm],len[maxm];
int cnt[maxm];
int n;

void pushup(int x,int l,int r){
	if(cnt[x]) len[x] = X[r + 1] - X[l];
	else if(l == r) len[x] = 0;
	else len[x] = len[x << 1] + len[x << 1 | 1];
}

void build(int x,int l,int r){
	cnt[x] = 0,len[x] = 0;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(x << 1,l,mid);
	build(x << 1 | 1,mid + 1,r);
}

void modify(int x,int l,int r,int L,int R,int val){
	if(l >= L && r <= R)
		return cnt[x] += val,pushup(x,l,r),void();
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1,l,mid,L,R,val);
	if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,val);
	pushup(x,l,r);
}

int main(){
	int cas = 0;
	double x1,x2,y1,y2;
	while(scanf("%d",&n) != EOF && n){
		int tot = 0;double ans = 0.0;
		for(int i = 1;i <= n;i++){
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			X[++tot] = x1;
			E[tot] = Edge(x1,x2,y1,1);
			X[++tot] = x2;
			E[tot] = Edge(x1,x2,y2,-1);
		}
		std :: sort(E + 1,E + tot + 1);
		std :: sort(X + 1,X + tot + 1);

		int k = 1;
		for(int i = 2;i <= tot;i++)
			if(X[i] != X[i - 1]) X[++k] = X[i];
		
		build(1,1,k);
		for(int i = 1;i < tot;i++){
			int l = lower_bound(X + 1,X + k + 1,E[i].l) - X;
			int r = lower_bound(X + 1,X + k + 1,E[i].r) - X - 1;
			if(l <= r) modify(1,1,k,l,r,E[i].f);
			ans += (E[i + 1].h - E[i].h) * len[1];
		}
		printf("Test case #%d\n",++cas);
		printf("Total explored area: %.2lf\n",ans);
		putchar(10);
	}

	return 0;
}
