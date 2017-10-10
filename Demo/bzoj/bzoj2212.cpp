#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 4e6 + 10;

int v[maxm],lc[maxm],rc[maxm],lft[maxm],rht[maxm],size[maxm],rt[maxm];
int sz,num,n;
LL ans;

void read(int x){
	scanf("%d",&v[x]);
	if(!v[x]){
		lft[x] = ++num;
		read(lft[x]);
		rht[x] = ++num;
		read(rht[x]);
	}
}

void insert(int &x,int l,int r,int val){
	if(!x) x = ++sz;
	if(l == r) return size[x] = 1,void();
	int mid = (l + r) >> 1;
	if(val <= mid) insert(lc[x],l,mid,val);
	else insert(rc[x],mid + 1,r,val);
	size[x] = size[lc[x]] + size[rc[x]];
}

int merge(int x,int y,LL &ret1,LL &ret2){
	if(!(x * y)) return x ^ y;
	ret1 += 1LL * size[rc[x]] * size[lc[y]];
	ret2 += 1LL * size[lc[x]] * size[rc[y]];
	lc[x] = merge(lc[x],lc[y],ret1,ret2);
	rc[x] = merge(rc[x],rc[y],ret1,ret2);
	size[x] = size[lc[x]] + size[rc[x]];
	return x;
}

void dfs(int x){
	if(!x) return;
	dfs(lft[x]),dfs(rht[x]);
	if(!v[x]){
		LL ret1 = 0,ret2 = 0;
		rt[x] = merge(rt[lft[x]],rt[rht[x]],ret1,ret2);
		ans += std :: min(ret1,ret2);
	}
}

int main(){
	scanf("%d",&n);num++;
	read(1);
	for(int i = 1;i <= num;i++)
		if(v[i]) insert(rt[i],1,n,v[i]);
	
	dfs(1);
	printf("%lld\n",ans);
		
	return 0;
}
