#include <cstdio>
#include <algorithm>

static const int maxm = 2e6 + 10;

int dpt[maxm],size[maxm],pos[maxm],top[maxm],ftr[maxm],son[maxm];
int fst[maxm],nxt[maxm],to[maxm],tr[maxm];
int cnt,n,m,sz;

void ins(int f,int t){
    nxt[++cnt] = fst[f];
    fst[f] = cnt;
    to[cnt] = t;
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
    pos[x] = ++sz;top[x] = chain;
    if(son[x]) dfs2(son[x],chain);
    for(int u = fst[x];u;u = nxt[u])
        if(to[u] != son[x] && dpt[to[u]] > dpt[x]) dfs2(to[u],to[u]);
}

int lowbit(int x){
    return x & -x;
}

void Upt(int k,int val){
    for(int i = k;i <= n;i += lowbit(i)) tr[i] += val;
}

int Qry(int k){
    int ret = 0;
    for(int i = k;i;i -= lowbit(i)) ret += tr[i];
    return ret;
}

void solve_modify(int x,int y){
    while(top[x] != top[y]){
        if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
        Upt(pos[top[x]],1);Upt(pos[x] + 1,-1);
        x = ftr[top[x]];
    }
    if(pos[x] > pos[y]) std :: swap(x,y);
    Upt(pos[x],1);Upt(pos[y] + 1,-1);
}

int main(){    

    int x,y;
    scanf("%d%d",&n,&m);
    for(int i = 1;i < n;i++) scanf("%d%d",&x,&y),ins(x,y),ins(y,x);
    dfs1(1);
    dfs2(1,1);
    
    for(int i = 1;i <= m;i++)
        scanf("%d%d",&x,&y),solve_modify(x,y);
    
    int ans = 0;
    for(int i = 1;i <= n;i++)
        ans = std :: max(ans,Qry(pos[i]));
    printf("%d\n",ans);
    
    return 0;
}
