#include <cstdio>
#include <algorithm>

using std :: sort;
using std :: unique;
using std :: lower_bound;
using std :: max;
using std :: min;

typedef long long LL;

static const LL maxm = 50000 * 16 * 16 + 25;
static const LL maxn = 50000 + 25;

struct object{
    LL x,y,k,f;
}Q[maxn];

LL tr[maxm],tag[maxm],A[maxn];
LL rt[maxn << 2],lc[maxm],rc[maxm];
LL sz,n,m,cnt,tot;

template <typename Tp> void in(Tp &x) {
	char ch = getchar(), f = 1; x = 0;
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	if (ch == '-') f = -1, ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= f;
}

namespace seg_segment_tree{  // L R : pos in sequence

    void insert(LL &x,LL l,LL r,LL L,LL R){
        if(!x) x = ++sz;
        if(l >= L && r <= R)
            return tr[x] += r - l + 1,tag[x]++,void();
        LL mid = (l + r) >> 1;
        if(L <= mid) insert(lc[x],l,mid,L,R);
        if(R > mid) insert(rc[x],mid + 1,r,L,R);
        tr[x] = tr[lc[x]] + tr[rc[x]] + tag[x] * (r - l + 1);
    }

    LL Qry(LL x,LL l,LL r,LL L,LL R){
        if(l >= L && r <= R) return tr[x];
        LL mid = (l + r) >> 1;LL ret = 0;
        if(L <= mid) ret += Qry(lc[x],l,mid,L,R);
        if(R > mid) ret += Qry(rc[x],mid + 1,r,L,R);
        return ret + tag[x] * (min(R,r) - max(L,l) + 1);
    }
    
}

namespace val_segment_tree{  // L R : val in sequence
    
    using namespace seg_segment_tree;

    void modify(LL x,LL l,LL r,LL L,LL R,LL val){
        insert(rt[x],1,n,L,R);
        if(l == r) return;
        LL mid = (l + r) >> 1;
        if(val <= mid) modify(x << 1,l,mid,L,R,val);
        if(val > mid) modify(x << 1 | 1,mid + 1,r,L,R,val);
    }

    LL Get(LL x,LL l,LL r,LL L,LL R,LL k){
        if(l == r) return l;
        LL mid_size = Qry(rt[x << 1],1,n,L,R);
        LL mid = (l + r) >> 1;
        if(k <= mid_size) return Get(x << 1,l,mid,L,R,k);
        if(k > mid_size) return Get(x << 1 | 1,mid + 1,r,L,R,k - mid_size);
    }
    
}

using namespace val_segment_tree;

int main(){
    
    in(n); in(m);
    for(LL i = 1;i <= m;i++){
		in(Q[i].f);in(Q[i].x); in(Q[i].y); in(Q[i].k);
        if(Q[i].f == 1) A[++cnt] = Q[i].k;
    }

    sort(A + 1,A + cnt + 1);
    tot = unique(A + 1,A + cnt + 1) - A - 1;

    for(LL i = 1;i <= m;i++)
        if(Q[i].f == 1) Q[i].k = lower_bound(A + 1,A + tot + 1,Q[i].k) - A;

    for(LL i = 1;i <= m;i++){
        if(Q[i].f == 1) modify(1,1,tot,Q[i].x,Q[i].y,tot - Q[i].k + 1);
        if(Q[i].f == 2) printf("%lld\n",A[tot - Get(1,1,tot,Q[i].x,Q[i].y,Q[i].k) + 1]);
    }
    
    return 0;
}
