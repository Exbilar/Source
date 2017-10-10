#include <cstdio>
#include <algorithm>

static const int maxm = 2e6 + 10;
static const int INF = 1 << 30;

int fst[maxm],nxt[maxm],to[maxm],A[maxm],tmp[maxm];
int rt[maxm],v[maxm],lc[maxm],rc[maxm],ftr[maxm],ans[maxm];
int cnt,n,m,sz;

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

void insert(int &x,int l,int r,int val){
	if(!x) x = ++sz;
	if(l == r) return v[x] = 1,void();
	int mid = (l + r) >> 1;
	if(val <= mid) insert(lc[x],l,mid,val);
	else insert(rc[x],mid + 1,r,val);
	v[x] = v[lc[x]] + v[rc[x]];
}

int Query(int x,int l,int r,int L,int R){
	if(l >= L && r <= R) return v[x];
	int mid = (l + r) >> 1,res = 0;
	if(L <= mid) res += Query(lc[x],l,mid,L,R);
	if(R > mid) res += Query(rc[x],mid + 1,r,L,R);
	return res;
}

int merge(int x,int y){
	if(!x || !y) return x ^ y;
	lc[x] = merge(lc[x],lc[y]);
	rc[x] = merge(rc[x],rc[y]);
	v[x] = v[lc[x]] + v[rc[x]];
	return x;
}

void dfs(int x){
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == ftr[x]) continue;
		dfs(v);
		rt[x] = merge(rt[x],rt[v]);
	}
	ans[x] += Query(rt[x],1,n,A[x] + 1,n);
}

int main(){
	
	int x;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),tmp[i] = A[i];
	
	std :: sort(tmp + 1,tmp + n + 1);
	int tot = std :: unique(tmp + 1,tmp + n + 1) - tmp - 1;
	for(int i = 1;i <= n;i++)
		A[i] = std :: lower_bound(tmp + 1,tmp + n + 1,A[i]) - tmp;

	for(int i = 2;i <= n;i++)
		scanf("%d",&x),ftr[i] = x,ins(x,i);
	
	for(int i = 1;i <= n;i++) insert(rt[i],1,n,A[i]);
	dfs(1);
	
	for(int i = 1;i <= n;i++) printf("%d\n",ans[i]);
	
	return 0;
}
