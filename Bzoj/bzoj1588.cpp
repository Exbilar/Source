#include <cstdio>
#include <algorithm>

using std :: abs;
using std :: min;
using std :: max;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int ch[maxm][2],v[maxm],rnk[maxm],size[maxm],cnt[maxm];
int ret,rt,sz,n,ans,ret2,ret1;

int chk(int x,int y){
    return x == y ? 2333 : x > y; 
}

void upt(int x){
    size[x] = size[ch[x][0]] + size[ch[x][1]] + cnt[x];
}

void rotate(int &x,int f){
    int t = ch[x][f];
    ch[x][f] = ch[t][f ^ 1];
    ch[t][f ^ 1] = x;
    size[t] = size[x];
    upt(x);x = t;
}

void insert(int &x,int val){
    if(!x){x = ++sz;cnt[x] = size[x] = 1;rnk[x] = rand();v[x] = val;return;}
    size[x]++;
    if(v[x] == val){cnt[x]++;return;}
    int f = chk(val,v[x]);
    insert(ch[x][f],val);
    if(rnk[ch[x][f]] > rnk[x]) rotate(x,f);
}

void Qpre(int x,int val){
    if(!x) return;
    if(val >= v[x])ret1 = v[x],Qpre(ch[x][1],val);
    else Qpre(ch[x][0],val);
}

void Qnxt(int x,int val){
    if(!x)return;
    if(val <= v[x])ret2 = v[x],Qnxt(ch[x][0],val);
    else Qnxt(ch[x][1],val);
}

int main(){
    int x;
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%d",&x);
        ret1 = -INF;ret2 = INF;
        Qpre(rt,x);Qnxt(rt,x);
        if(i != 1) ans += min(x - ret1, ret2 - x);
        else ans += x;
        insert(rt,x);
    }
    
    printf("%d\n",ans);
    
    return 0;
}
