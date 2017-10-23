#include <cstdio>
#include <algorithm>

using std :: max;
using std :: min;

static const int maxm = 1e6 + 10;

int lmax[maxm],rmax[maxm],smax[maxm],smin[maxm],lmin[maxm],rmin[maxm],A[maxm],sum[maxm];
int n,m;

void pushup(int x){
    int l = x << 1;
    int r = x << 1 | 1;
    sum[x] = sum[l] + sum[r];
    smax[x] = max(max(smax[l],smax[r]),lmax[r] + rmax[l]);
    smin[x] = min(min(smin[l],smin[r]),lmin[r] + rmin[l]);
    lmax[x] = max(lmax[l],sum[l] + lmax[r]);
    rmax[x] = max(rmax[r],sum[r] + rmax[l]);
    lmin[x] = min(lmin[l],sum[l] + lmin[r]);
    rmin[x] = min(rmin[r],sum[r] + rmin[l]);
}

void build(int x,int l,int r){
    if(l == r) return sum[x] = A[l],smax[x] = lmax[x] = rmax[x] = smin[x] = lmin[x] = rmin[x] = sum[x],void();
    int mid = (l + r) >> 1;
    build(x << 1,l,mid);
    build(x << 1 | 1,mid + 1,r);
    pushup(x);
}

void upt(int x,int l,int r,int pos,int val){
    if(l == r) return sum[x] = val,smax[x] = lmax[x] = rmax[x] = smin[x] = lmin[x] = rmin[x] = sum[x],void();
    int mid = (l + r) >> 1;
    if(pos <= mid) upt(x << 1,l,mid,pos,val);
    if(pos > mid) upt(x << 1 | 1,mid + 1,r,pos,val);
    pushup(x);
}

int main(){
    int x,y,opt,ans;

    while(scanf("%d",&n) != EOF){
        for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
        build(1,1,n);

        scanf("%d",&m);

        while(m--){
            scanf("%d%d",&x,&y);
            upt(1,1,n,x,y);
            if(sum[1] == smax[1]) ans = sum[1] - smin[1];
            else ans = max(sum[1] - smin[1],smax[1]);
            printf("%d\n",ans);
        }
    }

    return 0;
}