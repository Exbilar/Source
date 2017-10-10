
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i,s,t) for(int i=s;i<=t;i++)

typedef long long LL;
typedef unsigned long long ULL;

static const int maxm=100;
static const ULL MOD=7528443412579576937;

ULL b,d,n;

struct matrix{
    ULL mtx[maxm][maxm];
};

LL tms(ULL A,ULL N){
    ULL ret=0;
    while(N){
        if(N&1)ret=(ret+A)%MOD;
        A=(A+A)%MOD;
        N>>=1;
    }
    return ret;
}

matrix mul(matrix A,matrix B){
    matrix ret;
    memset(ret.mtx,0,sizeof ret.mtx);
    REP(i,1,2)REP(j,1,2)REP(k,1,2)
        ret.mtx[i][j]=(ret.mtx[i][j]+tms(A.mtx[i][k],B.mtx[k][j]))%MOD;
    
    return ret;
}

matrix pow(matrix A,ULL n){
    matrix ret=A;n--;
    while(n){
	if(n&1)ret=mul(ret,A);
	A=mul(A,A);
	n>>=1;
    }
    return ret;
}

int main(){
    matrix st,get;
    scanf("%llu%llu%llu",&b,&d,&n);
    st.mtx[1][1]=2;st.mtx[1][2]=b;
    get.mtx[1][1]=0;get.mtx[1][2]=(d-b*b)/4;
    get.mtx[2][1]=1;get.mtx[2][2]=b;
    if(!n)return puts("1"),0;

    st=mul(st,pow(get,n));
    ULL f=0;
    if(n%2==0&&b!=d*d)f=1;
    printf("%llu\n",((st.mtx[1][1])%MOD-f+MOD)%MOD);
    
    return 0;
}
