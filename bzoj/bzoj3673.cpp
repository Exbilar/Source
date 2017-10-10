#include <cstdio>
#include <algorithm>

static const int maxm = 5e6 + 10;

int dpt[maxm],ftr[maxm],lc[maxm],rc[maxm],rt[maxm];
int sz,n,m,lstans;

template<class T>
void read(T &in){
	in = 0;int f = 1;char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

void build(int &x,int l,int r){
	x = ++sz;
	if(l == r) return ftr[x] = l,dpt[x] = 1,void();
	int mid = (l + r) >> 1;
	build(lc[x],l,mid);
	build(rc[x],mid + 1,r);
}

void insert(int &x,int lst,int l,int r,int val,int fa){
	x = ++sz,lc[x] = lc[lst],rc[x] = rc[lst];
	if(l == r) return ftr[x] = fa,dpt[x] = dpt[lst],void();
	int mid = (l + r) >> 1;
	if(val <= mid) insert(lc[x],lc[lst],l,mid,val,fa);
	else insert(rc[x],rc[lst],mid + 1,r,val,fa);
}

void modify(int x,int l,int r,int val){
	if(l == r) return dpt[x]++,void();
	int mid = (l + r) >> 1;
	if(val <= mid) modify(lc[x],l,mid,val);
	else modify(rc[x],mid + 1,r,val);
}

int Qry(int x,int l,int r,int val){
	if(l == r) return x;
	int mid = (l + r) >> 1;
	if(val <= mid) return Qry(lc[x],l,mid,val);
	else return Qry(rc[x],mid + 1,r,val);
}

int find(int root,int x){
	int tmp = Qry(root,1,n,x);
	return ftr[tmp] == x ? tmp : find(root,ftr[tmp]);
}

void merge(int i,int x,int y){
	if(dpt[x] > dpt[y]) std :: swap(x,y);
	insert(rt[i],rt[i - 1],1,n,ftr[x],ftr[y]);
	if(dpt[x] == dpt[y]) modify(rt[i],1,n,ftr[y]);
}

int main(){
	int x,y,k,opt;
	read(n);read(m);
	build(rt[0],1,n);

	for(int i = 1;i <= m;i++){
		read(opt);
		rt[i] = rt[i - 1];
		if(opt == 1){
			read(x);read(y);
			x = find(rt[i],x),y = find(rt[i],y);
			if(x != y) merge(i,x,y);
		}
		if(opt == 2) read(k),rt[i] = rt[k];
		if(opt == 3){
			read(x);read(y);
			lstans = (find(rt[i],x) == find(rt[i],y));
			printf("%d\n",lstans);
		}
	}

	return 0;
}
