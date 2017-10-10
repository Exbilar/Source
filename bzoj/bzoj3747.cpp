#include <cstdio>
#include <algorithm>

using std :: min;
using std :: max;

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int maxn = 4e6 + 10;

LL f[maxm],w[maxm],smax[maxn],tag[maxn],nxt[maxm],lst[maxm];
int n,m;

void pushdown(int x){
    int lc = x << 1,rc = x << 1 | 1;
    tag[lc] += tag[x],tag[rc] += tag[x];
    smax[lc] += tag[x],smax[rc] += tag[x];
    tag[x] = 0;
}

void modify(int x,int l,int r,int L,int R,LL val){
    if(l >= L && r <= R){
        smax[x] += val;
        tag[x] += val;
        return;
    }
    if(tag[x]) pushdown(x);
    int mid = (l + r) >> 1;
    if(L <= mid) modify(x << 1,l,mid,L,R,val);
    if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,val);
    smax[x] = max(smax[x << 1],smax[x << 1 | 1]);
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++) scanf("%lld",&f[i]);
    for(int i = 1;i <= m;i++) scanf("%lld",&w[i]);
    for(int i = n;i;i--){
        nxt[i] = lst[f[i]];
        lst[f[i]] = i;
    }

    for(int i = 1;i <= m;i++){
        if(lst[i]){
            if(nxt[lst[i]]) modify(1,1,n,lst[i],nxt[lst[i]] - 1,w[i]);
            else modify(1,1,n,lst[i],n,w[i]);
        }
    }
    
    LL ans = 0;
    
    for(int i = 1;i <= n;i++){
        ans = max(ans,smax[1]);
        int _next = nxt[i];
        if(_next){
            modify(1,1,n,i,_next - 1,-w[f[i]]);
            if(nxt[_next]) modify(1,1,n,_next,nxt[_next] - 1,w[f[i]]);
            else modify(1,1,n,_next,n,w[f[i]]);
        }else modify(1,1,n,i,n,-w[f[i]]);
    }

    printf("%lld\n",ans);
    
    return 0;
}
