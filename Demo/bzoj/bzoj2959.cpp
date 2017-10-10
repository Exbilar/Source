#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int ch[maxm][2],rev[maxm],v[maxm],sum[maxm],ftr[maxm];
int	father[maxm],belong[maxm],Q[maxm],A[maxm],stk[maxm];
int top,n,m,opt;

int find_set(int x){
	return x == father[x] ? x : father[x] = find_set(father[x]);
}

int find_cre(int x){
	return x == belong[x] ? x : belong[x] = find_cre(belong[x]);
}

void upt(int x){
	sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + v[x];
}

int get(int x){
	return ch[ftr[x]][1] == x;
}

int isrt(int x){
	return ch[ftr[x]][0] != x && ch[ftr[x]][1] != x;
}

void pushdown(int x){
	if(!rev[x]) return;
	int lc = ch[x][0],rc = ch[x][1];
	rev[lc] ^= 1,rev[rc] ^= 1,rev[x] ^= 1;
	std :: swap(ch[x][0],ch[x][1]);
}

void pushtag(int x){
	top = 0,stk[++top] = x;
	for(int i = x;!isrt(i);i = ftr[i])
		stk[++top] = ftr[i];
	while(top) pushdown(stk[top--]);
}

void rotate(int x){
	int fa = ftr[x],gnd = ftr[fa],f = get(x);
	if(!isrt(fa)) ch[gnd][get(fa)] = x;
	ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
	ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
	upt(fa),upt(x);
}

void splay(int x){
	pushtag(x);
	for(x;!isrt(x);rotate(x))
		if(!isrt(ftr[x])) rotate(get(x) == get(ftr[x]) ? ftr[x] : x);
}

void access(int x){
	for(int y = 0;x;y = x,x = find_cre(ftr[x]))
		splay(x),ch[x][1] = y,ftr[y] = x,upt(x);
}

void makert(int x){
	access(x),splay(x),rev[x] ^= 1;
}

void split(int x,int y){
	makert(x),access(y),splay(y);
}

void link(int x,int y){
	makert(x),ftr[x] = y;
}

void rebuild(int x,int y){
	split(x,y);
	int head = 1,tail = 1;
	Q[tail++] = y;
	while(head != tail){
		int x = Q[head++];
		belong[x] = y;
		if(ch[x][0]) Q[tail++] = ch[x][0];
		if(ch[x][1]) Q[tail++] = ch[x][1];
		ch[x][0] = ch[x][1] = 0;
	}
	v[y] = sum[y];
}

void Link(int x,int y){
	x = find_cre(x),y = find_cre(y);
	if(x == y) return;
	int r1 = find_set(x),r2 = find_set(y);
	if(r1 != r2) link(x,y),father[r1] = r2;
	else rebuild(x,y);
}

void Add(int x,int y){
	x = find_cre(x);
	v[x] += y,splay(x);
}

int Qry(int x,int y){
	if(find_set(x) != find_set(y)) return -1;
	x = find_cre(x),y = find_cre(y);
	if(x == y) return v[x];
	split(x,y);
	return sum[y];
}

int main(){
	
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) belong[i] = i,father[i] = i;
	for(int i = 1;i <= n;i++) scanf("%d",&v[i]),A[i] = v[i];

	while(m--){
		scanf("%d%d%d",&opt,&x,&y);
		if(opt == 1) Link(x,y);
		if(opt == 2) Add(x,y - A[x]),A[x] = y;
		if(opt == 3) printf("%d\n",Qry(x,y));
	}
	
	return 0;
}
