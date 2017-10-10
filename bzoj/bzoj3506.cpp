
#include <cstdio>
#include <algorithm>

using std :: swap;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 29;

int v[maxm],ftr[maxm],size[maxm],rev[maxm],st[maxm],ch[maxm][2],ans[maxm];
int n,rt,sz,top;

struct data{
    int val,id;
}A[maxm];

bool cmp1(data x,data y){
    return x.val == y.val ? x.id < y.id : x.val < y.val;
}
bool cmp2(data x,data y){
    return x.id < y.id;
}

void upt(int x){
    size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
}

int get(int x){
    return ch[ftr[x]][1] == x;
}

void pushdown(int x){
    if(!rev[x] || !x) return;
    rev[ch[x][0]] ^= 1,rev[ch[x][1]] ^= 1,rev[x] = 0,swap(ch[x][0],ch[x][1]);
}

void build(int &x,int l,int r){
    if(l > r) return ;
    int mid = (l + r) >> 1;
    x = A[mid].val;
    build(ch[x][0],l,mid - 1);
    build(ch[x][1],mid + 1,r);
    ftr[ch[x][0]] = ftr[ch[x][1]] = x;
    upt(x);
}

void rotate(int x){
    int fa = ftr[x],gnd = ftr[fa],f = get(x);
    pushdown(fa);pushdown(x);
    ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
    ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
    if(gnd) ch[gnd][ch[gnd][1] == fa] = x;
    upt(fa);upt(x);
}

void splay(int x,int k){
    top = 0;
    for(int i = x;ftr[i];i = ftr[i]) st[++top] = i;
    for(int i = top;i;i--) pushdown(st[i]);
    for(int fa = x;(fa = ftr[x]) != k;rotate(x))
        if(ftr[fa] != k) rotate(get(x) == get(fa) ? fa :x);
    if(!k) rt = x;
}

int Qorder(int rnk){
    int f = 0;
    for(int x = rt;x;x = ch[x][f]){
        pushdown(x);
        if(rnk <= size[ch[x][0]]) f = 0;
        else if(rnk > size[ch[x][0]] + 1) rnk -= size[ch[x][0]] + 1,f = 1;
        else return x;
    }
}

void rever(int k){
    splay(k,0);
    printf("%d",size[ch[rt][0]]);
    if(k != n + 1) printf(" ");
    int x = Qorder(k - 1),y = Qorder(size[ch[rt][0]] + 2);
    splay(x,0);splay(y,x);
    rev[ch[ch[rt][1]][0]] ^= 1;
}

int main(){
    scanf("%d",&n);
    for(int i = 2;i <= n + 1;i++)scanf("%d",&A[i].val),A[i].id = i;
    std :: sort(A + 2,A + n + 2,cmp1);
    for(int i = 2;i <= n + 1;i++) A[i].val = i;
    A[1].val = 1,A[n + 2].val = n + 2;
    std :: sort(A + 2,A + n + 2,cmp2);
    
    build(rt,1,n + 2);
    
    for(int i = 1;i <= n;i++) rever(i + 1);
    
    putchar(10);
    
    return 0;
}
