#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int ch[maxm][2],v[maxm],size[maxm],cnt[maxm],ftr[maxm];
char opt[maxm];
int rt,sz,delta,minx,ans,tot;

int chk(int x,int y){
    return x == y ? 2333 : x > y;
}

int get(int x){
    return ch[ftr[x]][1] == x;
}

void upt(int x){
    size[x] = size[ch[x][0]] + size[ch[x][1]] + cnt[x];
}

int lft(int x){
    return size[ch[x][0]] + cnt[x];
}

void rotate(int x){
    int fa = ftr[x],gnd = ftr[fa],f = get(x);
    ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
    ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
    if(gnd) ch[gnd][ch[gnd][1] == fa] = x;
    upt(fa);upt(x);
}

void splay(int x){
    for(int fa = x;fa = ftr[x];rotate(x))
        if(ftr[fa]) rotate((get(fa) == get(x)) ? fa : x);
    rt = x;
}

void insert(int &x,int val,int fa){
    if(!x){x = ++sz;v[x] = val;ftr[x] = fa;size[x] = cnt[x] = 1;splay(x);return;}
    size[x]++;
    if(v[x] == val){cnt[x]++;splay(x);return;}
    int f = chk(val,v[x]);
    insert(ch[x][f],val,x);
}

int Qorder(int rank){
    int f = 0;
    for(int x = rt;x;x = ch[x][f]){
        if(rank <= size[ch[x][0]]) f = 0;
        else if(rank > lft(x)) f = 1,rank -= lft(x);
        else return x;
    }
}

void del(){
    int x1 = rt,x2 = rt;
    while(x1){
        if(v[x1] < minx - delta) x1 = ch[x1][1];
        else x2 = x1,x1 = ch[x1][0];
    }
    if(v[x2] < minx - delta){rt = 0; return;}
    splay(x2),ch[x2][0] = 0;
    upt(rt);
}

int main(){
    int x,m;
    scanf("%d%d",&m,&minx);
    while(m--){
        scanf("%s%d",opt,&x);
        if(opt[0] == 'I' && x >= minx) tot++,insert(rt,x - delta,0);
        if(opt[0] == 'A') delta += x;
        if(opt[0] == 'S') delta -= x,del();
        if(opt[0] == 'F')
            if(x > size[rt]) puts("-1");
            else printf("%d\n",v[Qorder(size[rt] - x + 1)] + delta);
    }
    
    printf("%d\n",tot - size[rt]);
    return 0;
}
