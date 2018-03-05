#include <cstdio>
#include <algorithm>

using std :: max;
using std :: min;

typedef long long LL;

static const LL maxm = 4e6 + 10;
static const LL maxn = 1e7 + 10;

LL phi[maxn],sum[maxm],smax[maxm],smin[maxm],A[maxm],tag[maxm];
LL n,m,T,opt;

void init(){
    for(LL i = 1;i < maxn;i++) phi[i] = i;
    for(LL i = 2;i < maxn;i++)
        if(phi[i] == i)
            for(LL j = i;j < maxn;j += i)
                phi[j] = phi[j] / i * (i - 1);
}

void pushup(LL x){
    LL lc = x << 1,rc = x << 1 | 1;
    sum[x] = sum[lc] + sum[rc];
    smax[x] = max(smax[lc],smax[rc]);
    smin[x] = min(smin[lc],smin[rc]);
}

void build(LL x,LL l,LL r){
    tag[x] = -1;
    if(l == r) return sum[x] = smin[x] = smax[x] = A[l],void();
    LL mid = (l + r) >> 1;
    build(x << 1,l,mid);
    build(x << 1 | 1,mid + 1,r);
    pushup(x);
}

void pushdown(LL x,LL l,LL r){
    LL lc = x << 1,rc = x << 1 | 1;
    LL mid = (l + r) >> 1;
    sum[lc] = (mid - l + 1) * tag[x];
    sum[rc] = (r - mid) * tag[x];
    smax[lc] = smin[lc] = smax[rc] = smin[rc] = tag[x];
    tag[lc] = tag[rc] = tag[x];tag[x] = -1;
}

void make_phi(LL x,LL l,LL r,LL L,LL R){
    if(l >= L && r <= R){
        if(smax[x] == smin[x]){
            LL val = phi[smax[x]];
            sum[x] = (r - l + 1) * val;
            smax[x] = smin[x] = val;
            tag[x] = val;
            return;
        }
    }
    if(tag[x] != -1) pushdown(x,l,r);
    LL mid = (l + r) >> 1;
    if(L <= mid) make_phi(x << 1,l,mid,L,R);
    if(R > mid) make_phi(x << 1 | 1,mid + 1,r,L,R);
    pushup(x);
}

void modify(LL x,LL l,LL r,LL L,LL R,LL val){
    if(l >= L && r <= R){
        sum[x] = (r - l + 1) * val;
        smax[x] = smin[x] = val;
        tag[x] = val;
        return;
    }
    if(tag[x] != -1) pushdown(x,l,r);
    LL mid = (l + r) >> 1;
    if(L <= mid) modify(x << 1,l,mid,L,R,val);
    if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,val);
    pushup(x); 
}

LL Qry(LL x,LL l,LL r,LL L,LL R){
    if(l >= L && r <= R) return sum[x];
    if(tag[x] != -1) pushdown(x,l,r);
    LL mid = (l + r) >> 1;LL ret = 0;
    if(L <= mid) ret += Qry(x << 1,l,mid,L,R);
    if(R > mid) ret += Qry(x << 1 | 1,mid + 1,r,L,R);
    return ret;
}

int main(){
    init();
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&n,&m);
        for(LL i = 1;i <= n;i++) scanf("%lld",&A[i]);
        build(1,1,n);
        while(m--){
            LL x,y,z;
            scanf("%lld",&opt);
            if(opt == 1) scanf("%lld%lld",&x,&y),make_phi(1,1,n,x,y);
            if(opt == 2) scanf("%lld%lld%lld",&x,&y,&z),modify(1,1,n,x,y,z);
            if(opt == 3) scanf("%lld%lld",&x,&y),printf("%lld\n",Qry(1,1,n,x,y));
        }
    }
    
    return 0;
}
