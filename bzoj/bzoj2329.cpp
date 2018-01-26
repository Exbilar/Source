#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 2e5 + 10;

template <class T> inline bool chkmax(T &x,T y){
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
    return x > y ? x = y,true : false;
}

template <class T> inline T read (){
    T in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    return in * f;
}

int size[maxm],sum[maxm],rev[maxm],cov[maxm],inv[maxm];
int lmax[maxm],rmax[maxm],lmin[maxm],rmin[maxm],A[maxm];
int ftr[maxm],ch[maxm][2],val[maxm],stk[maxm];
int sz,rt,n,m,top;

char opt[10],str[maxm];

inline void swap(int &x,int &y){
    x ^= y ^= x ^= y;
}

inline int max(int x,int y){
	return x >= y ? x : y;
}

inline int min(int x,int y){
	return x <= y ? x : y;
}

inline int get(int x){
    return ch[ftr[x]][1] == x;
}

inline void upt(int x){
    int lc = ch[x][0],rc = ch[x][1];
    size[x] = size[lc] + size[rc] + 1;
    sum[x] = sum[lc] + sum[rc] + val[x];
    lmax[x] = max(lmax[lc],sum[lc] + val[x] + max(0,lmax[rc]));
    rmax[x] = max(rmax[rc],sum[rc] + val[x] + max(0,rmax[lc]));
    lmin[x] = min(lmin[lc],sum[lc] + val[x] + min(0,lmin[rc]));
    rmin[x] = min(rmin[rc],sum[rc] + val[x] + min(0,rmin[lc]));
}

inline void rotate(int x){
    int fa = ftr[x],gnd = ftr[fa],f = get(x);
    if(gnd) ch[gnd][get(fa)] = x;
    ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
    ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
    upt(fa),upt(x);
}

inline void pushcov(int x,int v){
    if(v == 1) lmax[x] = rmax[x] = size[x] * v,lmin[x] = rmin[x] = 0;
    else lmax[x] = rmax[x] = 0,lmin[x] = rmin[x] = size[x] * v;
    
    cov[x] = v,rev[x] = 0,inv[x] = 0;	
    sum[x] = v * size[x];
    val[x] = v;
}

inline void pushrev(int x){
    rev[x] ^= 1;
    swap(ch[x][0],ch[x][1]);
    swap(lmax[x],rmax[x]);
    swap(lmin[x],rmin[x]);
}

inline void pushinv(int x){
    swap(lmax[x],lmin[x]);
    swap(rmax[x],rmin[x]);
    
    inv[x] ^= 1,cov[x] = -cov[x];
    lmax[x] = -lmax[x],lmin[x] = -lmin[x];
    rmax[x] = -rmax[x],rmin[x] = -rmin[x];
    val[x] = -val[x],sum[x] = -sum[x];
}

inline void pushdown(int x){
    if(rev[x]){
        if(ch[x][0]) pushrev(ch[x][0]);
        if(ch[x][1]) pushrev(ch[x][1]);
        rev[x] = 0;
    }
    if(inv[x]){
        if(ch[x][0]) pushinv(ch[x][0]);
        if(ch[x][1]) pushinv(ch[x][1]);
        inv[x] = 0;
    }
    if(cov[x]){
        if(ch[x][0]) pushcov(ch[x][0],cov[x]);
        if(ch[x][1]) pushcov(ch[x][1],cov[x]);
        cov[x] = 0;
    }
}

inline void downbtm(int x){
    top = 0; stk[++top] = x;
    for(int i = x;ftr[i];i = ftr[i]) stk[++top] = ftr[i];
    while(top) pushdown(stk[top--]);
}

inline void splay(int x,int k){
    downbtm(x);
    for(int fa = x;(fa = ftr[x]) != k;rotate(x))
        if(ftr[fa] != k) rotate(get(fa) == get(x) ? fa : x);
    if(!k) rt = x;
}

inline void newnode(int &x,int fa,int v){
    x = ++sz; ftr[x] = fa; val[x] = v; sum[x] = v; size[x] = 1;
    if(v == 1) lmax[x] = rmax[x] = v,lmin[x] = rmin[x] = 0;
    else lmax[x] = rmax[x] = 0,lmin[x] = rmin[x] = v;
}

void build(int &x,int l,int r,int fa){
    if(l > r) return ;
    int mid = (l + r) >> 1;
    newnode(x,fa,A[mid]);
    build(ch[x][0],l,mid - 1,x);
    build(ch[x][1],mid + 1,r,x);
    upt(x);
}

int findkth(int x,int kth){
    pushdown(x);
    if(kth == size[ch[x][0]] + 1) return x;
    if(kth <= size[ch[x][0]]) return findkth(ch[x][0],kth);
    else return findkth(ch[x][1],kth - size[ch[x][0]] - 1);
}

inline int split(int l,int r){
    int x = findkth(rt,l),y = findkth(rt,r + 2);
    splay(x,0),splay(y,x);
    return ch[y][0];
}

inline void Replace(){
    int l = read<int>(),r = read<int>();
    scanf("%s",str);
    
    int x = split(l,r);
    if(str[0] == '(') pushcov(x,-1);
    else pushcov(x,1);
}

inline void Swap(){
    int l = read<int>(),r = read<int>();
    int x = split(l,r);
    pushrev(x);
}

inline void Invert(){
    int l = read<int>(),r = read<int>();
    int x = split(l,r);
    pushinv(x);
}

inline void Query(){
    int l = read<int>(),r = read<int>();
    int x = split(l,r);
    printf("%d\n",(lmax[x] + 1) / 2 + (-rmin[x] + 1) / 2);
}

int main(){
    
    n = read<int>(),m = read<int>();

    scanf("%s",str);
    
    for(int i = 1;i <= n;i++){
        if(str[i - 1] == '(') A[i] = -1;
        else A[i] = 1;
    }

    A[0] = 0,A[n + 1] = 0;
    build(rt,0,n + 1,0);
    
    while(m--){
        scanf("%s",opt);
        if(opt[0] == 'R') Replace();
        if(opt[0] == 'S') Swap();
        if(opt[0] == 'I') Invert();
        if(opt[0] == 'Q') Query();
    }

    return 0;
}
