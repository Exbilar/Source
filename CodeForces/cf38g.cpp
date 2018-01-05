#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;

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

int ftr[maxm],ch[maxm][2],idx[maxm],size[maxm],smax[maxm],v[maxm];
int sz,rt;

void upt(int x){
    size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
    smax[x] = max(v[x],max(smax[ch[x][0]],smax[ch[x][1]]));
}

int get(int x){
    return ch[ftr[x]][1] == x;
}

int chk(int x,int y){
    return x == y ? 233 : x > y;
}

void newnode(int &x,int fa,int val,int id){
    x = ++sz,ftr[x] = fa,size[x] = 1,smax[x] = v[x] = val,idx[x] = id;
}

void rotate(int x){
    int fa = ftr[x],gnd = ftr[fa],f = get(x);
    if(gnd) ch[gnd][get(fa)] = x;
    ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
    ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
    upt(fa),upt(x);
}

void splay(int x,int k){
    for(int fa = x;(fa = ftr[x]) != k;rotate(x))
        if(ftr[fa] != k) rotate(get(x) == get(fa) ? fa : x);
    if(!k) rt = x;
}

int Query(int val,int f){
    int x = rt,k = 0;
    for(x = rt;x;x = ch[x][k]){
        if(val < v[x] && ch[x][0]) k = 0;
        else if(val > v[x] && ch[x][1]) k = 1;
        else break;
    }
    while(chk(val,v[x]) == f) x = ftr[x];
    return x;
}

int Qorder(int x,int kth){
    if(!x) return 0;
    if(kth <= size[ch[x][0]]) return Qorder(ch[x][0],kth);
    else if(kth > size[ch[x][0]] + 1) return Qorder(ch[x][1],kth - size[ch[x][0]] - 1);
    else return x;
}

int getmax(int kth){
    int x = Qorder(rt,kth + 1);
    splay(x,0);
    return max(v[x],smax[ch[x][1]]);
}

void insert(int pos,int val,int id){
    int x = Qorder(rt,pos),y = Qorder(rt,pos + 1);
    splay(x,0),splay(y,x);
	newnode(ch[y][0],y,val,id);
	upt(y);
}

void dfs(int x){
    if(ch[x][0]) dfs(ch[x][0]);
    if(idx[x] != INF && idx[x] != -INF) printf("%d ",idx[x]);
    if(ch[x][1]) dfs(ch[x][1]);
}

int main(){
	int n;
	
	newnode(rt,0,0,-INF);
	newnode(ch[rt][1],rt,0,INF);
	
    read(n);

    for(int i = 1;i <= n;i++){
        int u,v;
        read(u),read(v);
        int l = 1,r = i + 1;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(getmax(mid) > u) l = mid + 1;
            else r = mid - 1;
        }
        if(i - l > v) l = i - v;
        insert(l,u,i);
    }

    dfs(rt);

	putchar(10);
	
    return 0;
}

