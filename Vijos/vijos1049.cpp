#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

static const int maxm=1e2+10;

#define REP(i,s,t) for(int i=s;i<=t;i++) 

typedef long long LL;

struct matrix{
    LL mtx[maxm][maxm];
}mx[16];

LL n,k,m;
LL A[maxm][maxm];

matrix mul(matrix A,matrix B){
    matrix ret;
    memset(ret.mtx,0,sizeof ret.mtx);
    REP(i,1,n)REP(j,1,n)REP(k,1,n)
		ret.mtx[i][j]=(ret.mtx[i][j]+A.mtx[i][k]*B.mtx[k][j]);
    return ret;
}

matrix pow(matrix A,LL n){
    if(!n)return A;
    matrix ret=A;n--;
    while(n){
		if(n&1)ret=mul(ret,A);
		A=mul(A,A);
		n>>=1;
    }

    return ret;
}

void display(matrix base){
    for(int i=1;i<=n;i++)printf("%lld ",base.mtx[1][i]);
    puts("");
}

int main(){
    matrix st,get,f;
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=m;i++){
    	for(int j=1;j<=n;j++){
	    	scanf("%lld",&A[i][j]);
	    	mx[i].mtx[A[i][j]][j]=1;
		}
    }
     
    for(int i=1;i<=n;i++)st.mtx[1][i]=i;
    
    get=mx[1];
    
    for(int i=2;i<=m;i++)get=mul(get,mx[i]);
    
    get=pow(get,k/m);k%=m;
    for(int i=1;i<=k;i++)get=mul(get,mx[i]);
    
    st=mul(st,get);
    
    display(st);
    
    return 0;
}
