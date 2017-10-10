#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 29;

int ch[maxm][2],ftr[maxm],size[maxm],v[maxm],pos[maxm];
char opt[10];
int n,m,sz,rt;

int get(int x){
	return ch[ftr[x]][1] == x;
}

void upt(int x){
	size[x] = size[ch[x][1]] + size[ch[x][0]] + 1;
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

int Qorder(int x,int rnk){
	if(rnk == size[ch[x][0]] + 1) return x;
	if(rnk > size[ch[x][0]] + 1) return Qorder(ch[x][1],rnk - size[ch[x][0]] - 1);
	else return Qorder(ch[x][0],rnk);
}

int Query(int x){
	splay(x,0);
	return size[ch[x][0]];
}

void dfs(int x){
	if(ch[x][0]) printf("%d 's lson : %d\n",v[x],v[ch[x][0]]),dfs(ch[x][0]);
	if(ch[x][1]) printf("%d 's rson : %d\n",v[x],v[ch[x][1]]),dfs(ch[x][1]);
}

void insert(int k,int val){
	int x = Qorder(rt,k);splay(x,0);
	int y = Qorder(ch[x][1],1);splay(y,x);
	ftr[++sz] = y,size[sz] = 1,v[sz] = val,ch[y][0] = sz,pos[val] = sz;
	upt(x);upt(y);
	dfs(rt);
}

void del(int k){
	int x = Qorder(rt,Query(k));splay(x,0);
	int y = Qorder(ch[x][1],2);splay(y,x);
	size[ch[y][0]] = 0,ftr[ch[y][0]] = 0,ch[y][0] = 0;
	upt(x);upt(y);
}

int main(){
	int x,y;
	sz = 2,rt = 1;
	ftr[2] = 1,size[2] = 1,v[2] = INF;
	ftr[1] = 0,size[1] = 2,v[1] = -INF,ch[1][1] = 2;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%d",&x);
		insert(i,x);
	}
	while(m--){
        scanf("%s%d",opt,&x);
        if (opt[0]=='Q') printf("%d\n",v[Qorder(rt,x + 1)]);
        if (opt[0]=='A') printf("%d\n",Query(pos[x]) - 1);
        if (opt[0]=='T') del(pos[x]),insert(1,x);
        if (opt[0]=='B') del(pos[x]),insert(n,x);
        if (opt[0]=='I'){
            scanf("%d",&y);
            int num = Query(pos[x]);
            del(pos[x]);
            insert(num + y,x);
        }
    }


	return 0;
}
