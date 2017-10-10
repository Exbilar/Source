#include <cstdio>
#include <algorithm>

#define key ch[ch[rt][1]][0]

static const int maxm = 3e6 + 10;
static const int INF = 1 << 29;

int ch[maxm][2],size[maxm],ftr[maxm];
char opt[10],v[maxm],in[maxm];
int sz,rt,m,cur = 1;

void upt(int x){
	size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
}

int get(int x){
	return ch[ftr[x]][1] == x;
}

void newnode(int &x,int fa,char val){
	x = ++sz,v[x] = val,ftr[x] = fa,size[x] = 1;
}

void rotate(int x){
    int fa = ftr[x],gnd = ftr[fa],f = get(x);
    ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
    ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
    if(gnd) ch[gnd][ch[gnd][1] == fa] = x;
    upt(fa);upt(x);
}

void splay(int x,int k){
    for(int fa = x;(fa = ftr[x]) != k;rotate(x))
        if(ftr[fa] != k) rotate((get(fa) == get(x)) ? fa : x);
    if(!k) rt = x;
}

void build(int &x,int l,int r,int last){
    int mid = (l + r) >> 1;
    newnode(x,last,in[mid]);
    if(l < mid) build(ch[x][0],l,mid - 1,x);
    if(mid < r) build(ch[x][1],mid + 1,r,x);
    upt(x);
}

int Qorder(int x,int rnk){
    if(rnk == size[ch[x][0]] + 1) return x;
    if(rnk > size[ch[x][0]] + 1) return Qorder(ch[x][1],rnk - size[ch[x][0]] - 1);
    else return Qorder(ch[x][0],rnk);
}

void split(int l,int r){
	int x = Qorder(rt,l - 1);
	int y = Qorder(rt,r + 1);
	splay(x,0);splay(y,x);
}

void insword(){
	int len;
	scanf("%d",&len);
	for(int i = 1;i <= len;i++){
		in[i] = getchar();
		if(in[i] < 32 || in[i] > 126) i--;
	}
	split(cur + 1,cur);
	build(key,1,len,ch[rt][1]);
	upt(ch[rt][1]),upt(rt);
}

void delword(){
	int x;
	scanf("%d",&x);
	split(cur + 1,cur + x);
	ftr[key] = 0,key = 0;
	upt(ch[rt][1]),upt(rt);
}

void display(int x){
	if(ch[x][0]) display(ch[x][0]);
	putchar(v[x]);
	if(ch[x][1]) display(ch[x][1]);
}

void getword(){
	int x;
	scanf("%d",&x);
	split(cur + 1,cur + x);
	display(key);
	putchar(10);
}

int main(){
	int x;
	scanf("%d",&m);
	newnode(rt,0,' ');newnode(ch[rt][1],rt,' ');upt(rt);
	while(m--){
		scanf("%s",opt);
		if(opt[0] == 'M') scanf("%d",&x),cur = x + 1;
		if(opt[0] == 'I') insword();
		if(opt[0] == 'D') delword();
		if(opt[0] == 'G') getword();
		if(opt[0] == 'P') cur--;
		if(opt[0] == 'N') cur++;
	}
	return 0;
}
