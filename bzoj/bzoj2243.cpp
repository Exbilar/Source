#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int dpt[maxm],size[maxm],ftr[maxm],pos[maxm],top[maxm],fnl[maxm],son[maxm],A[maxm];
int fst[maxm],nxt[maxm << 1],to[maxm << 1];
int lcol[maxm << 2],rcol[maxm << 2],scol[maxm << 2],tag[maxm << 2];
char opt[10];
int n,m,cnt,sz;

void ins(int f,int t){
    nxt[++cnt] = fst[f];
    to[cnt] = t;
    fst[f] = cnt;
}

void dfs1(int x){
    size[x] = 1;
    for(int u = fst[x];u;u = nxt[u]){
        int v = to[u];
        if(v == ftr[x]) continue;
        dpt[v] = dpt[x] + 1,ftr[v] = x;
        dfs1(v);
        size[x] += size[v];
        if(size[v] > size[son[x]]) son[x] = v;
    }
}

void dfs2(int x,int chain){
    pos[x] = ++sz,top[x] = chain;
    if(son[x]) dfs2(son[x],chain);
    for(int u = fst[x];u;u = nxt[u]){
        int v = to[u];
        if(dpt[v] > dpt[x] && v != son[x]) dfs2(v,v);
    }
    fnl[x] = sz;
}

void pushup(int x){
    int lc = x << 1,rc = x << 1 | 1;
    lcol[x] = lcol[lc],rcol[x] = rcol[rc];
    scol[x] = scol[lc] + scol[rc] - (rcol[lc] == lcol[rc]);
}

void pushdown(int x){
    if(!tag[x]) return;
    int lc = x << 1,rc = x << 1 | 1;
    lcol[lc] = rcol[lc] = tag[x];
    lcol[rc] = rcol[rc] = tag[x];
    scol[lc] = scol[rc] = 1;
    tag[lc] = tag[x],tag[rc] = tag[x],tag[x] = 0;
}

void modify(int x,int l,int r,int L,int R,int col){
    if(l >= L && r <= R){
        lcol[x] = rcol[x] = col;
        tag[x] = col,scol[x] = 1;
        return;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    if(L <= mid) modify(x << 1,l,mid,L,R,col);
    if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,col);
    pushup(x);
}

int Qry(int x,int l,int r,int L,int R){
    if(l >= L && r <= R) return scol[x];
    pushdown(x);
    int mid = (l + r) >> 1,ret = 0;
    if(L <= mid) ret += Qry(x << 1,l,mid,L,R);
    if(R > mid) ret += Qry(x << 1 | 1,mid + 1,r,L,R);
    if(L <= mid && R > mid && rcol[x << 1] == lcol[x << 1 | 1]) ret--;
    return ret;
}

int Qcol(int x,int l,int r,int pos){
    if(l == r) return lcol[x];
    pushdown(x);
    int mid = (l + r) >> 1;
    if(pos <= mid) return Qcol(x << 1,l,mid,pos);
    else return Qcol(x << 1 | 1,mid + 1,r,pos);
}

void solve_modify(int x,int y,int col){
    while(top[x] != top[y]){
        if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
        modify(1,1,n,pos[top[x]],pos[x],col);
        x = ftr[top[x]];
    }
    if(pos[x] > pos[y]) std :: swap(x,y);
    modify(1,1,n,pos[x],pos[y],col);
}

int solve_Qry(int x,int y){
    int ret = 0;
    while(top[x] != top[y]){
        if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
        ret += Qry(1,1,n,pos[top[x]],pos[x]);
        ret -= Qcol(1,1,n,pos[top[x]]) == Qcol(1,1,n,pos[ftr[top[x]]]);
        x = ftr[top[x]];
    }
    if(pos[x] > pos[y]) std :: swap(x,y);
    ret += Qry(1,1,n,pos[x],pos[y]);
    return ret;
}

int main(){

    int x,y,c;
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
    for(int i = 1;i < n;i++) scanf("%d%d",&x,&y),ins(x,y),ins(y,x);

    dfs1(1);
    dfs2(1,1);

    for(int i = 1;i <= n;i++) solve_modify(i,i,A[i]);
    
    while(m--){
        scanf("%s",opt);
        if(opt[0] == 'C') scanf("%d%d%d",&x,&y,&c),solve_modify(x,y,c);
        if(opt[0] == 'Q') scanf("%d%d",&x,&y),printf("%d\n",solve_Qry(x,y));
    }


    return 0;
}
