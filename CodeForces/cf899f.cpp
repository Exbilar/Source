#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: set;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;
static const int maxn = 500 + 10;

template <class T> inline bool chkmax(T &x,T y){
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in){
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

set<int> S[maxn];

char str[maxm],sub[maxn],ans[maxm];
int bit[maxm],vis[maxm],stk[maxm];
int n,m,cnt,top;

typedef set<int> :: iterator itr;

int lowbit(int x){
    return x & -x;
}

void Upt(int k,int v){
    for(int i = k;i <= n;i += lowbit(i)) bit[i] += v;
}

int Qry(int k){
    int res = 0;
    for(int i = k;i;i -= lowbit(i)) res += bit[i];
    return res;
}

int find(int x){
    int res = n;
    int l = 1,r = n;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(Qry(mid) >= x) res = mid,r = mid - 1;
        else l = mid + 1;
    }
    return res;
}

int main(){

    read(n),read(m);

    scanf("%s",str + 1);
    for(int i = 1;i <= n;i++) S[str[i]].insert(i);
    for(int i = 1;i <= n;i++) Upt(i,1);

    while(m--){
        int l,r;
        read(l),read(r),scanf("%s",sub);
        l = find(l),r = find(r);
        itr _begin = S[sub[0]].lower_bound(l);
        itr _end = S[sub[0]].upper_bound(r);
        for(itr it = _begin;it != _end;it++){
            Upt(*it,-1);
            vis[*it] = 1;
            stk[++top] = *it;
        }
        while(top) S[sub[0]].erase(stk[top--]);
    }

    for(int i = 1;i <= n;i++)
        if(!vis[i]) ans[cnt++] = str[i];

    printf("%s\n",ans);

    return 0;
}
