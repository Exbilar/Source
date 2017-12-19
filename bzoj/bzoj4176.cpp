#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: map;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const LL mod = 1000000007;
static const int maxm = 6e6 + 10;

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

LL mu[maxm],M[maxm],prm[maxm];
bool npr[maxm];
LL cnt,lmt;

map<LL,LL> f;

LL add(LL x,LL y){
    x += y; if(x >= mod) x -= mod;
    return x;
}

LL minus(LL x,LL y){
    x -= y; if(x < 0) x += mod;
    return x;
}

LL mul(LL x,LL y){
    x = (x + mod) % mod;
    y = (y + mod) % mod;
    return (x * y) % mod;
}

void getPrime(int N){
    mu[1] = 1;
    for(int i = 2;i <= N;i++){
        if(!npr[i]) prm[++cnt] = i,mu[i] = -1;
        for(int j = 1;j <= cnt && prm[j] * i <= N;j++){
            npr[prm[j] * i] = 1;
            if(i % prm[j] == 0){
                mu[i * prm[j]] = 0;
                break;
            }
            mu[i * prm[j]] = -mu[i];
        }
    }
    for(int i = 1;i <= N;i++) M[i] = add(M[i - 1],mu[i]);
}

LL calcF(LL N){
    LL res = 0;
    for(LL l = 1,r = 0;l <= N;l = r + 1){
        r = N / (N / l);
        LL tmp = add(minus(r,l),1);
        res = add(res,mul(tmp,N / l));
    }
    return mul(res,res);
}

LL calcMu(LL N){
    if(N <= lmt) return M[N];
    if(f[N]) return f[N];
    LL res = 1;
    for(LL l = 2,r = 0;l <= N;l = r + 1){
        r = N / (N / l);
        LL tmp = add(minus(r,l),1);
        res = minus(res,mul(tmp,calcMu(N / l)));
    }
    return f[N] = res;
}

LL solve(LL N){
    LL res = 0;
    for(LL l = 1,r = 0;l <= N;l = r + 1){
        r = N / (N / l);
        LL tmpr = calcMu(r);
        LL tmpl = calcMu(l - 1);
        LL tmp = minus(tmpr,tmpl);
        res = add(res,mul(tmp,calcF(N / l)));
    }
    return res;
}

int main(){
    LL N;
    read(N);

    getPrime(lmt = pow(N,3 / (double) 4));

    printf("%lld\n",solve(N));

    return 0;
}
