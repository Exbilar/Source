#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 512 ;

bool mp[maxm][maxm],usable[maxm];
LL f[10][100][maxm];
int digit[maxm];
int n,m;
LL ans;

bool chk(int x,int y){
    if(x&y)return false;
    if((x>>1)&y)return false;
    if((x<<1)&y)return false;
    return true;
}

bool get_usable(int x){
    if((x<<1)&x)return false;
    if((x>>1)&x)return false;
    return true;
}

int get_digit(int x){
    int ret=0;
    while(x)
	ret+=x&1,x>>=1;
    return ret;
}

int main(){
    scanf("%d%d",&n,&m);
    
    for(int i=0;i<(1<<n);i++)
	for(int j=0;j<(1<<n);j++)
	    if(chk(i,j))mp[i][j]=1;
    
    for(int i=0;i<(1<<n);i++)digit[i]=get_digit(i);
    for(int i=0;i<(1<<n);i++)usable[i]=get_usable(i);

    f[0][0][0]=1;
    
    for(int i=1;i<=n;i++)
	for(int j=0;j<=m;j++)
	    for(int k=0;k<(1<<n);k++)
		if(usable[k]&&digit[k]<=j)
		    for(int l=0;l<(1<<n);l++)
			if(usable[l]&&mp[k][l]&&digit[k]+digit[l]<=j)
			    f[i][j][k]+=f[i-1][j-digit[k]][l];
    
    for(int i=0;i<(1<<n);i++)ans+=f[n][m][i];

    printf("%lld\n",ans);
    
    return 0;
}
