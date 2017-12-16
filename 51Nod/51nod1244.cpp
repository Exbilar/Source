#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: map;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 5e6 + 10;

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

int mu[maxm],prm[maxm];
bool npr[maxm];
LL M[maxm];

int cnt,num,lmt;

map<LL,LL> h;

LL getPrime(int N){
    mu[1] = 1;
    for(int i = 2;i <= N;i++){
        if(!npr[i]) prm[++num] = i,mu[i] = -1;
        for(int j = 1;j <= num && prm[j] * i <= N;j++){
            npr[prm[j] * i] = 1;
            mu[prm[j] * i] = -mu[i];
            if(i % prm[j] == 0){
                mu[prm[j] * i] = 0;
                break;
            }
        }
    }
    for(int i = 1;i <= N;i++) M[i] = M[i - 1] + mu[i];
}

LL calc(LL x){
    if(x <= lmt) return M[x];
    if(h.count(x)) return h[x];
    LL res = 1;
    for(LL l = 2,r = 0;l <= x;l = r + 1){
        r = x / (x / l);
        res -= calc(x / l) * (r - l + 1);
    }
    return h[x] = res;
}

int main(){
	
    LL l,r;
	
    read(l),read(r);
	
    getPrime(lmt = pow(r,2 / (double) 3));
	
    printf("%lld\n",calc(r) - calc(l - 1));
	
    return 0;
}
