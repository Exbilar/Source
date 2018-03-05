#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i,s,t) for(int i=s;i<=t;i++)

typedef long long LL;

static const int maxm=100;

long long MOD,G,a,c,n,x0;

struct matrix{
    LL mtx[maxm][maxm];
};

LL tms(LL A,LL N){
    LL ret=0;
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

matrix pow(matrix A,LL n){
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

    scanf("%lld%lld%lld%lld%lld%lld",&MOD,&a,&c,&x0,&n,&G);
    
    st.mtx[1][1]=x0;st.mtx[1][2]=c;
    get.mtx[1][1]=a;get.mtx[1][2]=0;
    get.mtx[2][1]=1;get.mtx[2][2]=1;

    get=pow(get,n);
    st=mul(st,get);
    printf("%lld\n",(st.mtx[1][1])%G);
    
    return 0;
}
