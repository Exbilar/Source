#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: map;

typedef long long LL;

static const LL INF = 1 << 30;
static const LL oo = 1LL << 62;
static const LL maxm = 5e6 + 10;
static const LL mod = 1000000007;

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

LL prm[maxm],phi[maxm],P[maxm];
bool npr[maxm];

LL cnt,lmt,N;

map<LL,LL> f;

LL add(LL x,LL y){
	x = (x + mod) % mod;
	y = (y + mod) % mod;
    x += y; if(x >= mod) x -= mod;
    return x;
}

LL minus(LL x,LL y){
	x = (x + mod) % mod;
	y = (y + mod) % mod;
    x -= y; if(x < 0) x += mod;
    return x;
}

LL mul(LL x,LL y){
	x = (x + mod) % mod;
	y = (y + mod) % mod;
	return (x * y) % mod;
}

LL fpm(LL x,LL k){
    LL res = 1;
    while(k){
        if(k & 1) res = mul(res,x);
        x = mul(x,x);
        k >>= 1;
    }
    return res;
}

LL inv2 = fpm(2,mod - 2);

void getPrime(LL N){
	phi[1] = 1;
    for(LL i = 2;i <= N;i++){
        if(!npr[i]) prm[++cnt] = i,phi[i] = i - 1;
        for(LL j = 1;j <= cnt && prm[j] * i <= N;j++){
            npr[i * prm[j]] = 1;
            if(i % prm[j] == 0){
                phi[i * prm[j]] = mul(phi[i],prm[j]);
                break;
            }
            phi[i * prm[j]] = mul(phi[i],prm[j] - 1);
        }
    }
	
    for(LL i = 1;i <= N;i++) P[i] = add(P[i - 1],phi[i]);
}

LL calc(LL N){
    if(N <= lmt) return P[N];
    if(f[N]) return f[N];
	
    LL res = mul(inv2,mul(N,N + 1));
	
    for(LL l = 2,r = 0;l <= N;l = r + 1){
        r = N / (N / l);
        res = minus(res,mul(calc(N / l),r - l + 1));
    }
	
    return f[N] = res;
}

LL solve(LL N){
    LL res = 0;
    for(LL l = 1,r = 0;l <= N;l = r + 1){
        r = N / (N / l);
        res = add(res,mul(mul(N / l,N / l),minus(calc(r),calc(l - 1))));
    }
    return res;
}

int main(){
    read(N);
    getPrime(lmt = pow(N,2 / (double) 3));
	
    printf("%lld\n",solve(N));
	
    return 0;
}
