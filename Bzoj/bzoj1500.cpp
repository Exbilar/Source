#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 29;

int ftr[maxm],ch[maxm][2],v[maxm],A[maxm],st[maxm],tag[maxm],rev[maxm];
int size[maxm],lmax[maxm],rmax[maxm],smax[maxm],sum[maxm];
char opt[10];
int sz,rt,n,m,top;

int get(int x){
    return ch[ftr[x]][1] == x;
}

void newnode(int &x,int val,int fa){
    x = top ? st[top--] : ++sz;
    ftr[x] = fa,v[x] = val,size[x] = 1;
    sum[x] = v[x] = lmax[x] = rmax[x] = val;
    ch[x][0] = ch[x][1] = rev[x] = tag[x] = 0;
}

void upt(int x){
    if(!x) return;
    size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
    sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + v[x];
    lmax[x] = max(lmax[ch[x][0]],sum[ch[x][0]] + v[x] + max(lmax[ch[x][1]],0));
    rmax[x] = max(rmax[ch[x][1]],sum[ch[x][1]] + v[x] + max(rmax[ch[x][0]],0));
    smax[x] = max(max(smax[ch[x][0]],smax[ch[x][1]]),max(rmax[ch[x][0]],0) + v[x] + max(lmax[ch[x][1]],0));
}

void build(int &x,int l,int r,int fa){
    if(l > r) return;
    int mid = (l + r) >> 1;
    newnode(x,A[mid],fa);
    build(ch[x][0],l,mid - 1,x);
    build(ch[x][1],mid + 1,r,x);
    ftr[ch[x][0]] = ftr[ch[x][1]] = x;
    upt(x);
}

void pushrev(int x){
    if(!x) return;
    swap(lmax[x],rmax[x]);
    swap(ch[x][0],ch[x][1]);
    rev[x] ^= 1;
}

void pushtag(int x,int val){
    if(!x) return;
    v[x] = val,sum[x] = size[x] * val;
    lmax[x] = rmax[x] = smax[x] = max(sum[x],v[x]);
    tag[x] = 1;
}

void pushdown(int x){
    if(rev[x]){
        if(ch[x][0]) pushrev(ch[x][0]);
        if(ch[x][1]) pushrev(ch[x][1]);
        rev[x] = 0;
    }
    if(tag[x]){
        if(ch[x][0]) pushtag(ch[x][0],v[x]);
        if(ch[x][1]) pushtag(ch[x][1],v[x]);
        tag[x] = 0;
    }
}

void downbtm(int x){
    if(ftr[x]) downbtm(ftr[x]);
    pushdown(x);
}

void rotate(int x){
    int fa = ftr[x],gnd = ftr[fa],f = get(x);
    ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
    ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
    if(gnd) ch[gnd][ch[gnd][1] == fa] = x;
    upt(fa);upt(x);
}

void splay(int x,int k){
    downbtm(x);
    for(int fa = x;(fa = ftr[x]) != k;rotate(x))
        if(ftr[fa] != k) rotate(get(x) == get(fa) ? fa : x);
    if(!k) rt = x;
}

int Qorder(int rnk){
    int f = 0;
    for(int x = rt;x;x = ch[x][f]){
        pushdown(x);
        if(rnk > size[ch[x][0]] + 1) rnk -= size[ch[x][0]] + 1,f = 1;
        else if(rnk <= size[ch[x][0]]) f = 0;
        else return x;
    }
}

void insert(){
    int pos,tot;
    scanf("%d%d",&pos,&tot);
    for(int i = 0;i < tot;i++) scanf("%d",&A[i]);
    int x = Qorder(pos + 1);splay(x,0);
    int y = Qorder(pos + 2);splay(y,x);
    build(ch[ch[rt][1]][0],0,tot - 1,ch[rt][1]);
    upt(ch[rt][1]);upt(rt);
}

void deltree(int x){
    st[++top] = x;
    if(ch[x][0]) deltree(ch[x][0]);
    if(ch[x][1]) deltree(ch[x][1]);
}

void del(){
    int pos,tot;
    scanf("%d%d",&pos,&tot);
    int x = Qorder(pos);splay(x,0);
    int y = Qorder(size[ch[rt][0]] + tot + 2);splay(y,x);
    deltree(ch[ch[rt][1]][0]);
    ftr[ch[ch[rt][1]][0]] = 0,ch[ch[rt][1]][0] = 0;
    upt(ch[rt][1]);upt(rt);
}

void reverse(){
    int pos,tot;
    scanf("%d%d",&pos,&tot);
    int x = Qorder(pos);splay(x,0);
    int y = Qorder(size[ch[rt][0]] + tot + 2);splay(y,x);
    pushrev(ch[ch[rt][1]][0]);
    upt(ch[rt][1]);upt(rt);
}

void replace(){
    int pos,tot,val;
    scanf("%d%d%d",&pos,&tot,&val);
    int x = Qorder(pos);splay(x,0);
    int y = Qorder(size[ch[rt][0]] + tot + 2);splay(y,x);
    pushtag(ch[ch[rt][1]][0],val);
    upt(ch[rt][1]);upt(rt);
}

int Query(){
    int pos,tot;
    scanf("%d%d",&pos,&tot);
    splay(Qorder(pos),0);
    splay(Qorder(pos + tot + 1),rt);
    printf("%d\n",sum[ch[ch[rt][1]][0]]);
}

int main(){
	lmax[0] = rmax[0] = smax[0] = -INF;
    newnode(rt,-INF,0);newnode(ch[rt][1],-INF,rt);upt(rt);
    scanf("%d%d",&n,&m);
    for(int i = 0;i < n;i++) scanf("%d",&A[i]);
    build(ch[ch[rt][1]][0],0,n - 1,ch[rt][1]);
    upt(ch[rt][1]);upt(rt);
    
    while(m--){
        scanf("%s",opt);
        if(opt[0] == 'I') insert();
        if(opt[0] == 'D') del();
        if(opt[4] == '-') replace();
        if(opt[0] == 'R') reverse();
        if(opt[0] == 'G') Query();
        if(opt[2] == 'X') printf("%d\n",smax[rt]);
    }
    
    return 0;
}
