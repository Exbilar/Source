#include <map>
#include <cstdio>
#include <algorithm>

using std :: map;

static const int maxm = 1e6 + 10;

struct DDF{
	int x,y,val;
}ddf[maxm];

map<int,int> E[maxm];

int ftr[maxm],rev[maxm],ch[maxm][2],tag[maxm],v[maxm],stk[maxm];
int n,m,top,type,no_use,cnt,now,tot;

int get(int x){
	return ch[ftr[x]][1] == x;
}

int isrt(int x){
	return ch[ftr[x]][0] != x && ch[ftr[x]][1] != x;
}

void pushdown(int x){
	int lc = ch[x][0],rc = ch[x][1];
	if(rev[x]){
		rev[lc] ^= 1,rev[rc] ^= 1;
		std :: swap(ch[x][0],ch[x][1]);
		rev[x] = 0;
	}
	if(tag[x]){
		v[lc] ^= tag[x],v[rc] ^= tag[x];
		tag[lc] ^= tag[x],tag[rc] ^= tag[x];
		tag[x] = 0;
	}
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
}

void splay(int x){
	pushtag(x);
	for(x;!isrt(x);rotate(x))
		if(!isrt(ftr[x])) rotate(get(x) == get(ftr[x]) ? ftr[x] : x);
}

void access(int x){
	for(int y = 0;x;y = x,x = ftr[x])
		splay(x),ch[x][1] = y;
}

void makert(int x){
	access(x),splay(x),rev[x] ^= 1;
}

void link(int x,int y){
	makert(x),ftr[x] = y;
}

void split(int x,int y){
	makert(x),access(y),splay(y);
}

void cut(int x,int y){
	split(x,y);
	ftr[x] = ch[y][0] = 0;
}

int Rand(){
	return rand() + 1;
}

void replace(){
	int x,y;
	scanf("%d%d",&x,&y);
	if(x > y) std :: swap(x,y);
	int id = E[x][y];
	pushtag(id);
	int val = v[id];
	cut(id,x),cut(id,y);
	int _x = x,_y = y;
	
	scanf("%d%d",&x,&y);
	if(x > y) std :: swap(x,y);
	E[x][y] = ++tot;
	link(tot,x),link(tot,y);
	split(_x,_y);
	tag[_y] ^= val,v[_y] ^= val;
}

void ins(int x,int y){
	ddf[++cnt] = (DDF){x,y,Rand()};
	split(x,y);
	tag[y] ^= ddf[cnt].val,v[y] ^= ddf[cnt].val;
	now ^= ddf[cnt].val;
}

void del(int num){
	int _x = ddf[num].x,_y = ddf[num].y;
	split(_x,_y);
	tag[_y] ^= ddf[num].val,v[_y] ^= ddf[num].val;
	now ^= ddf[num].val;
}

int Qry(int x,int y){
	if(x > y) std :: swap(x,y);
	int id = E[x][y];
	pushtag(id);
	puts(v[id] == now ? "YES" : "NO");
}

int main(){
	int x,y;
	scanf("%d",&no_use);
	scanf("%d%d",&n,&m);
	tot = n;
	for(int i = 1;i < n;i++){
		scanf("%d%d",&x,&y);
		if(x > y) std :: swap(x,y);
		E[x][y] = ++tot;
		link(tot,x),link(tot,y);
	}

	for(int i = 1;i <= m;i++){
		scanf("%d",&type);
		if(type == 1) replace();
		if(type == 2) scanf("%d%d",&x,&y),ins(x,y);
		if(type == 3) scanf("%d",&x),del(x);
		if(type == 4) scanf("%d%d",&x,&y),Qry(x,y);
	}
	
	return 0;
}
