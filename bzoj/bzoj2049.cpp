#include <cstdio>
#include <algorithm>

static const int maxm = 1e5 + 10;

int ch[maxm][2],ftr[maxm],rev[maxm],cnt[maxm],size[maxm],stk[maxm];
char str[10];
int n,m,top;

int get(int x){
	return ch[ftr[x]][1] == x;
}

int isrt(int x){
	return ch[ftr[x]][0] != x && ch[ftr[x]][1] != x;
}

void pushdown(int x){
	if(!rev[x]) return ;
	rev[ch[x][0]] ^= 1,rev[ch[x][1]] ^= 1;
	std :: swap(ch[x][0],ch[x][1]);
	rev[x] = 0;
}

void rotate(int x){
	int fa = ftr[x],gnd = ftr[fa],f = get(x);
	if(!isrt(fa)) ch[gnd][get(fa)] = x;
	ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
	ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
}

void pushtag(int x){
	top = 0,stk[++top] = x;
	for(int i = x;!isrt(i);i = ftr[i])
		stk[++top] = ftr[i];
	for(int i = top;i;i--) pushdown(stk[i]);
}

void splay(int x){
	pushtag(x);
	for(x;!isrt(x);rotate(x))
		if(!isrt(ftr[x])) rotate(get(x) == get(ftr[x]) ? ftr[x] : x);
}

void access(int x){
	for(int y = 0;x;x = ftr[x])
		splay(x),ch[x][1] = y,y = x;
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

void cut(int x,int y){
	makert(x),access(y),splay(y);
	ch[y][0] = ftr[x] = 0;
}

int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%s",str);
		scanf("%d%d",&x,&y);
		if(str[0] == 'C') link(x,y);
		if(str[0] == 'D') cut(x,y);
		if(str[0] == 'Q') puts(findrt(x) == findrt(y) ? "Yes" : "No");
	}

	return 0;
}
