#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 29;

int ch[maxm][2],ftr[maxm],v[maxm],sum[maxm],stk[maxm];
int smax[maxm],smin[maxm],rev[maxm],tag[maxm],pt[maxm];
char str[10];
int n,m,cnt,top;

int get(int x){
	return ch[ftr[x]][1] == x;
}

int isrt(int x){
	return ch[ftr[x]][0] != x && ch[ftr[x]][1] != x;
}

void upt(int x){
	int lc = ch[x][0],rc = ch[x][1];
	sum[x] = sum[lc] + sum[rc] + v[x];
	smax[x] = std :: max(smax[lc],smax[rc]);
	smin[x] = std :: min(smin[lc],smin[rc]);
	if(x > n) smax[x] = std :: max(smax[x],v[x]);
	if(x > n) smin[x] = std :: min(smin[x],v[x]);
}

void rotate(int x){
	int fa = ftr[x],gnd = ftr[fa],f = get(x);
	if(!isrt(fa)) ch[gnd][get(fa)] = x;
	ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
	ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
	upt(fa),upt(x);
}

void rever_tag(int x){
	sum[x] = -sum[x],v[x] = -v[x];
	std :: swap(smax[x],smin[x]);
	smax[x] = -smax[x],smin[x] = -smin[x];
	tag[x] ^= 1;
}

void pushdown(int x){
	int lc = ch[x][0],rc = ch[x][1];
	if(tag[x]){
		if(lc) rever_tag(lc);
		if(rc) rever_tag(rc);
		tag[x] = 0;
	}
	if(rev[x]){
		rev[lc] ^= 1,rev[rc] ^= 1,rev[x] ^= 1;
		std :: swap(ch[x][0],ch[x][1]);
	}
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

void split(int x,int y){
	makert(x),access(y),splay(y);
}

void link(int x,int y){
	makert(x),ftr[x] = y;
}

int findrt(int x){
	access(x),splay(x);
	while(ch[x][0]) x = ch[x][0];
	return x;
}

int main(){
	int x,y,val;
	scanf("%d",&n); cnt = n;
	for(int i = 0;i <= n;i++) smax[x] = -INF,smin[x] = INF;
	for(int i = 1;i < n;i++){
		scanf("%d%d%d",&x,&y,&val);
		pt[i] = ++cnt;
		link(x + 1,cnt),link(y + 1,cnt);
		v[cnt] = sum[cnt] = smax[cnt] = smin[cnt] = val;
	}

	scanf("%d",&m);
	
	
	while(m--){
		scanf("%s",str);
		if(str[0] == 'N')
			scanf("%d%d",&x,&y),split(x + 1,y + 1),rever_tag(y + 1);
		if(str[0] == 'S')
			scanf("%d%d",&x,&y),split(x + 1,y + 1),printf("%d\n",sum[y + 1]);
		if(str[0] == 'C')
			scanf("%d%d",&x,&val),splay(pt[x]),v[pt[x]] = val,upt(pt[x]);
		if(str[0] == 'M' && str[1] == 'A')
			scanf("%d%d",&x,&y),split(x + 1,y + 1),printf("%d\n",smax[y + 1]);
		if(str[0] == 'M' && str[1] == 'I')
			scanf("%d%d",&x,&y),split(x + 1,y + 1),printf("%d\n",smin[y + 1]);
	}
	
	
	return 0;
}
