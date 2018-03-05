#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

typedef long long LL;

static const int maxm = 2e5 + 10;

int lst[maxm],nxt[maxm],stk[maxm],ST[maxm][20];
LL suml[maxm],sumr[maxm],A[maxm],ans[maxm];
int n,m,top,block;
LL ret;

struct Query{
	int l,r,id;
	bool operator < (const Query &Q) const {
		return l / block == Q.l / block ? r < Q.r : l / block < Q.l / block;
	}
}ask[maxm];

void pre(){
	for(int i = 1;i <= n;i++) ST[i][0] = i;
	for(int j = 1;j <= 17;j++){
		for(int i = 1;i <= n;i++){
			int pos = i + (1 << (j - 1));
			if(pos <= n && A[ST[i][j - 1]] <= A[ST[pos][j - 1]]) ST[i][j] = ST[i][j - 1];
			else ST[i][j] = ST[pos][j - 1];
		}
	}
}

int Qry(int l,int r){
	int k = 0;
	while(1 << (k + 1) <= r - l + 1) k++;
	return A[ST[l][k]] <= A[ST[r - (1 << k) + 1][k]] ? ST[l][k] : ST[r - (1 << k) + 1][k];
}

void uptl(int l,int r,int f){
	int pos = Qry(l,r);
	LL tmp = (r - pos + 1) * A[pos] + sumr[l] - sumr[pos];
	ret += f * tmp;
}

void uptr(int l,int r,int f){
	int pos = Qry(l,r);
	LL tmp = (pos - l + 1) * A[pos] + suml[r] - suml[pos];
	ret += f * tmp;
}

int main(){
	scanf("%d%d",&n,&m); block = std :: sqrt(n);
	for(int i = 1;i <= n;i++) scanf("%lld",&A[i]);
	
	for(int i = 1;i <= m;i++) scanf("%d%d",&ask[i].l,&ask[i].r),ask[i].id = i;
	
	pre();
	
	for(int i = 1;i <= n;i++){
		while(top && A[i] < A[stk[top]]) nxt[stk[top--]] = i;
		lst[i] = stk[top],stk[++top] = i;
	}

	while(top) nxt[stk[top--]] = n + 1;

	for(int i = 1;i <= n;i++) suml[i] = suml[lst[i]] + 1LL * (i - lst[i]) * A[i];
	for(int i = n;i >= 1;i--) sumr[i] = sumr[nxt[i]] + 1LL * (nxt[i] - i) * A[i];

	int L = 1,R = 0;

	std :: sort(ask + 1,ask + m + 1);

	for(int i = 1;i <= m;i++){
		while(R < ask[i].r) uptr(L,++R,1);
		while(R > ask[i].r) uptr(L,R--,-1);
		while(L < ask[i].l) uptl(L++,R,-1);
		while(L > ask[i].l) uptl(--L,R,1);
		ans[ask[i].id] = ret;
	}

	for(int i = 1;i <= m;i++) printf("%lld\n",ans[i]);
	
	return 0;
}
