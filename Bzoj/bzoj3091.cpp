#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e6 + 10;

LL ch[maxm][2],L[maxm],R[maxm],H[maxm],sum[maxm],v[maxm];
LL size[maxm],ftr[maxm],rev[maxm],tag[maxm],stk[maxm];
int top,n,m;

int isrt(int x){
	return ch[ftr[x]][0] !=x && ch[ftr[x]][1] != x;
}

int get(int x){
	return ch[ftr[x]][1] == x;
}

void upt(int x){
	int lc = ch[x][0],rc = ch[x][1];
	sum[x] = sum[lc] + sum[rc] + v[x];
	size[x] = size[lc] + size[rc] + 1;
	L[x] = L[lc] + L[rc] + (v[x] + sum[rc]) * (size[lc] + 1);
	R[x] = R[lc] + R[rc] + (v[x] + sum[lc]) * (size[rc] + 1);
	H[x] = H[lc] + H[rc] + L[lc] * (size[rc] + 1) + R[rc] * (size[lc] + 1) + v[x] * (size[lc] + 1) * (size[rc] + 1);
}

void rever(int x){
	rev[x] ^= 1; std :: swap(ch[x][0],ch[x][1]); std :: swap(L[x],R[x]);
}

void ddf(int x,LL val){
	v[x] += 1LL * val;
	tag[x] += 1LL * val;
	sum[x] += 1LL * size[x] * val;
	L[x] += 1LL * size[x] * (size[x] + 1) / 2 * val;
	R[x] += 1LL * size[x] * (size[x] + 1) / 2 * val;
	H[x] += 1LL * size[x] * (size[x] + 1) * (size[x] + 2) / 6 * val;
}

void pushdown(int x){
	if(rev[x]) rever(ch[x][0]),rever(ch[x][1]),rev[x] = 0;
	if(tag[x]) ddf(ch[x][0],tag[x]),ddf(ch[x][1],tag[x]),tag[x] = 0;
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
		if(!isrt(ftr[x])) rotate(get(ftr[x]) == get(x) ? ftr[x] : x);
}

void access(int x){
	for(int y = 0;x;y = x,x = ftr[x])
		splay(x),ch[x][1] = y,upt(x);
}

void makert(int x){
	access(x),splay(x),rever(x);
}

int findrt(int x){
	access(x),splay(x);
	while(ch[x][0]) x = ch[x][0];
	return x;
}

void split(int x,int y){
	makert(x),access(y),splay(y);
}

void link(int x,int y){
	if(findrt(x) == findrt(y)) return;
	makert(x),ftr[x] = y;
}

void cut(int x,int y){
	if(findrt(x) != findrt(y)) return;
	split(x,y),ch[y][0] = ftr[x] = 0,upt(y);
}

LL Qry(int x,int y){
	split(x,y);
	return H[y];
}

int main(){
	
	int x,y,opt;LL d;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%lld",&v[i]),size[i] = 1,sum[i] = L[i] = R[i] = H[i] = v[i];

	for(int i = 1;i < n;i++) scanf("%d%d",&x,&y),link(x,y);
	
	while(m--){
		scanf("%d%d%d",&opt,&x,&y);
		if(opt == 1) cut(x,y);
		if(opt == 2) link(x,y);
		if(opt == 3){
			scanf("%lld",&d);
			if(findrt(x) != findrt(y)) continue;
			split(x,y),ddf(y,d);
		}
		if(opt == 4){
			if(findrt(x) != findrt(y)) puts("-1");
			else{
				LL up = Qry(x,y);
				LL down = size[y] * (size[y] + 1) / 2;
				LL GCD = std :: __gcd(up,down);
				printf("%lld/%lld\n",up / GCD,down / GCD);
			}
		}
	}

	return 0;
}
