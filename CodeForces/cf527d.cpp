#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

struct node{
	int l,r;
	bool operator < (const node &N) const {
		return r == N.r ? l < N.l : r < N.r;
	}
}A[maxm];

int n;

int main(){
	int x,w;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d%d",&x,&w),A[i].l = x - w,A[i].r = x + w;

	std :: sort(A + 1,A + n + 1);

	int cur = -INF,ans = 0;

	for(int i = 1;i <= n;i++){
		if(A[i].l >= cur) ans++,cur = A[i].r;
	}

	printf("%d\n",ans);
	
	return 0;
}
