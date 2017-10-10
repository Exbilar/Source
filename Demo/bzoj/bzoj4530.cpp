#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e6 + 10;

int sum[maxm],size[maxm],ch[maxm][2],ftr[maxm],v[maxm],rev[maxm],stk[maxm];
char opt[10];
int n,m,top;

void upt(int x){
	sum[x] = size[x] + sum[ch[x][0]] + sum[ch[x][1]] + v[x];
}

int isrt(int x){
	return ch[ftr[x]][0] != x && ch[ftr[x]][1] != x;
}

int get(int x){
	return ch[ftr[x]][1] == x;
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

void splay(int x){
	pushtag(x);
	for(x;!isrt(x);rotate(x))
		if(!isrt(ftr[x])) rotate(get(ftr[x]) == get(x) ? ftr[x] : x);
}

void access(int x){
	for(int y = 0;x;y = x,x = ftr[x]){
		splay(x);
		size[x] += sum[ch[x][1]] - sum[y];
		ch[x][1] = y;
		upt(x);
	}
}

void makert(int x){
	access(x),splay(x),rev[x] ^= 1;
}

void split(int x,int y){
	makert(x),makert(y);
}

void link(int x,int y){
	makert(x),makert(y);
	size[y] += sum[x],ftr[x] = y;
	upt(y);
}

int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) v[i] = 1;
	while(m--){
		scanf("%s",opt);
		scanf("%d%d",&x,&y);
		if(opt[0] == 'A') link(x,y);
		if(opt[0] == 'Q') split(x,y),printf("%lld\n",std :: abs(1LL * sum[x] * (sum[y] - sum[x])));
	}

	return 0;
}
