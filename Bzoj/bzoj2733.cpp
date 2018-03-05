#include <cstdio>
#include <algorithm>

static const int maxm = 3e6 + 10;

int rt[maxm],v[maxm],lsn[maxm],rsn[maxm],id[maxm],ftr[maxm],A[maxm];
char opt[10];
int sz,n,m,T;

void insert(int &x,int l,int r,int val){
	if(!x) x = ++sz;
	if(l == r) return v[x] = 1,void();
	int mid = (l + r) >> 1;
	if(val <= mid) insert(lsn[x],l,mid,val);
	if(val > mid) insert(rsn[x],mid + 1,r,val);
	v[x] = v[lsn[x]] + v[rsn[x]];
}

int merge(int x,int y){
	if(!x || !y) return x ^ y;
	lsn[x] = merge(lsn[x],lsn[y]),rsn[x] = merge(rsn[x],rsn[y]);
	v[x] = v[lsn[x]] + v[rsn[x]];
	return x;
}

int Query(int x,int rnk,int l,int r){
	if(l == r) return id[l];
	int mid = (l + r) >> 1;
	if(rnk <= v[lsn[x]])return Query(lsn[x],rnk,l,mid);
	else return Query(rsn[x],rnk - v[lsn[x]],mid + 1,r);
}

int find(int x){
	return x == ftr[x] ? x : find(ftr[x]);
}

int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
		scanf("%d",&A[i]),id[A[i]] = i,ftr[i] = i,insert(rt[i],1,n,A[i]);

	for(int i = 1;i <= m;i++){
		scanf("%d%d",&x,&y);
		int dx = find(x),dy = find(y);
		if(dx == dy) continue;
		ftr[dx] = dy,rt[dy] = merge(rt[dx],rt[dy]);
	}

	scanf("%d",&T);
	while(T--){
		scanf("%s%d%d",opt,&x,&y);
		if(opt[0] == 'Q') printf("%d\n",v[rt[find(x)]] < y ? -1 : Query(rt[find(x)],y,1,n));
		if(opt[0] == 'B'){
			int dx = find(x),dy = find(y);
			if(dx == dy) continue;
			ftr[dx] = dy,rt[dy] = merge(rt[dx],rt[dy]);
		}
	}

	return 0;
}
