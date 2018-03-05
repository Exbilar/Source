#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: map;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 4e6 + 10;

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

int prm[maxm],mu[maxm],phi[maxm];
LL M[maxm],P[maxm];
bool npr[maxm];
int cnt,lmt;

map<LL,LL> f,g;

LL getPrime(LL N){
    mu[1] = 1,phi[1] = 1;
    for(int i = 2;i <= N;i++){
        if(!npr[i]) prm[++cnt] = i,mu[i] = -1,phi[i] = i - 1;
        for(int j = 1;j <= cnt && prm[j] * i <= N;j++){
            npr[prm[j] * i] = 1;
            if(i % prm[j] == 0){
                mu[i * prm[j]] = 0;
                phi[i * prm[j]] = phi[i] * prm[j];
                break;
            }
            mu[i * prm[j]] = -mu[i];
            phi[i * prm[j]] = phi[i] * (prm[j] - 1);
        }
    }
    for(int i = 1;i <= N;i++) M[i] = M[i - 1] + mu[i];
    for(int i = 1;i <= N;i++) P[i] = P[i - 1] + phi[i];
}

LL calcMu(LL N){
    if(N <= lmt) return M[N];
    if(f[N]) return f[N];

    LL res = 1;
    for(LL l = 2,r;l <= N;l = r + 1){
        r = N / (N / l);
        res -= calcMu(N / l) * (r - l + 1);
    }
    return f[N] = res;
}

LL calcPhi(LL N){
    if(N <= lmt) return P[N];
    if(g[N]) return g[N];

    LL res = N * (N + 1) >> 1;
    for(LL l = 2,r;l <= N;l = r + 1){
        r = N / (N / l);
        res -= calcPhi(N / l) * (r - l + 1);
    }
    return g[N] = res;
}

int main(){
    int cas,N;
    read(cas);
    getPrime(lmt = 4000000);
    while(cas--){
        read(N);
        printf("%lld %lld\n",calcPhi(N),calcMu(N));
    }
    return 0;
}
