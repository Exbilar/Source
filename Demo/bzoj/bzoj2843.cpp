#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int ch[maxm][2],size[maxm],cnt[maxm],sum[maxm],v[maxm],ftr[maxm],rev[maxm],stk[maxm];
char str[10];
int top,n,m;

void upt(int x){
	size[x] = size[ch[x][0]] + size[ch[x][1]] + cnt[x];
	sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + v[x];
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
	rev[ch[x][0]] ^= 1,rev[ch[x][1]] ^= 1,rev[x] ^= 1;
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

int Qry(int x,int y){
	split(x,y);
	return sum[y];
}

int main(){
	int x,y;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&v[i]);
	scanf("%d",&m);

	while(m--){
		scanf("%s",str);
		if(str[0] == 'b'){
			scanf("%d%d",&x,&y);
			if(findrt(x) == findrt(y)) puts("no");
			else puts("yes"),link(x,y);
		}
		if(str[0] == 'p') scanf("%d%d",&x,&y),splay(x),v[x] = y,upt(x);
		if(str[0] == 'e'){
			scanf("%d%d",&x,&y);
			if(findrt(x) != findrt(y)) puts("impossible");
			else printf("%d\n",Qry(x,y));
		}
	}


	return 0;
}
