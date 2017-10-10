#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

static const int maxm=1005005;

LL C[maxm][4];
LL ans,t;
int n,m;

void getc(){
    C[0][0]=1;
    for(int i=1;i<=m*n;i++){
		C[i][0]=1;
		for(int j=1;j<=3;j++){
			C[i][j]=C[i-1][j-1]+C[i-1][j];
		}
    }
}

inline int gcd(int x,int y){
    return y==0?x:gcd(y,x%y);
}

int main(){
    scanf("%d%d",&n,&m);
    n++,m++;
    getc();
    ans=C[n*m][3];
    ans-=n*C[m][3];
    ans-=m*C[n][3];

    for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			t=gcd(i,j)+1;
			if(t>2)ans-=(t-2)*2*(n-i)*(m-j);
		}
    }
    
    printf("%lld\n",ans);
    
    return 0;
}
