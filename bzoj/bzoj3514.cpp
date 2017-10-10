#include <cstdio>
#include <algorithm>

static const int maxm = 4e6 + 10;
static const int INF = 1 << 30;

struct Edge{
	int x,y;
}E[maxm];

int ch[maxm][2],ftr[maxm],smin[maxm],rev[maxm],size[maxm],lc[maxm],rc[maxm];
int v[maxm],ddf[maxm],stk[maxm],rt[maxm];
int n,m,type,q,top,sz,cnt;

int get(int x){
	return ch[ftr[x]][1] == x;
}

int isrt(int x){
	return ch[ftr[x]][0] != x && ch[ftr[x]][1] != x;
}

void upt(int x){
	if(!x) return;
	smin[x] = x;
	if(v[smin[x]] > v[smin[ch[x][0]]]) smin[x] = smin[ch[x][0]];
	if(v[smin[x]] > v[smin[ch[x][1]]]) smin[x] = smin[ch[x][1]];
}

void rotate(int x){
	int fa = ftr[x],gnd = ftr[fa],f = get(x);
	if(!isrt(fa)) ch[gnd][get(fa)] = x;
	ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
	ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
	upt(fa),upt(x);
}

void pushdown(int x){
	if(!rev[x]) return;
	int ls = ch[x][0],rs = ch[x][1];
	rev[x] ^= 1,rev[ls] ^= 1,rev[rs] ^= 1;
	std :: swap(ch[x][0],ch[x][1]);
}

void pushtag(int x){
	top = 0,stk[++top] = x;
	for(int i = x;!isrt(i);i = ftr[i])
		stk[++top] = ftr[i];
	
	while(top) pushdown(stk[top--]);
}

void splay(int x){
	pushtag(x);
	for(x;!isrt(x);rotate(x))
		if(!isrt(ftr[x])) rotate(get(x) == get(ftr[x]) ? ftr[x] : x);
}

void access(int x){
	for(int y = 0;x;y = x,x = ftr[x])
		splay(x),ch[x][1] = y,upt(x);
}

void makert(int x){
	access(x),splay(x),rev[x] ^= 1;
}

int findrt(int x){
	access(x),splay(x);
	while(ch[x][0]) x = ch[x][0];
	return x;
}

void link(int x,int y){
	makert(x),ftr[x] = y;
}

void split(int x,int y){
	makert(x),access(y),splay(y);
}

void cut(int x,int y){
	split(x,y),ftr[x] = ch[y][0] = 0,upt(y);
}

int Query(int x,int y){
	split(x,y);
	return smin[y];
}

void insert(int &x,int lst,int l,int r,int val){
	x = ++sz,lc[x] = lc[lst],rc[x] = rc[lst],size[x] = size[lst] + 1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(val <= mid) insert(lc[x],lc[lst],l,mid,val);
	else insert(rc[x],rc[lst],mid + 1,r,val);
}

int Qry(int x,int y,int l,int r,int val){
	if(r == val) return size[y] - size[x];
	int mid = (l + r) >> 1;
	if(val <= mid) return Qry(lc[x],lc[y],l,mid,val);
	else return Qry(rc[x],rc[y],mid + 1,r,val) + size[lc[y]] - size[lc[x]];
}

int main(){
	scanf("%d%d%d%d",&n,&m,&q,&type);
	v[0] = INF;
	for(int i = 1;i <= n;i++) smin[i] = i,v[i] = INF;
	for(int i = 1;i <= m;i++) scanf("%d%d",&E[i].x,&E[i].y);

	cnt = n;
	for(int i = 1;i <= m;i++){
		int x = E[i].x,y = E[i].y;
		if(x == y) {ddf[i] = i;continue;}
		if(findrt(x) == findrt(y)){
			int t = Query(x,y);int p = v[t];
			ddf[i] = p;
			cut(E[p].x,t),cut(E[p].y,t);
		}
		v[++cnt] = i,smin[cnt] = cnt;
		link(x,cnt),link(y,cnt);
	}

	for(int i = 1;i <= m;i++) insert(rt[i],rt[i - 1],0,m,ddf[i]);
	
	int lstans = 0,l,r;
	while(q--){
		scanf("%d%d",&l,&r);
		if(type) l ^= lstans,r ^= lstans;
		printf("%d\n",lstans = n - Qry(rt[l - 1],rt[r],0,m,l - 1));
	}
	
	return 0;
}
