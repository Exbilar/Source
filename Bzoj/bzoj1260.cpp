#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

static const int maxm=1e3+10;

int f[maxm][maxm];
char s[maxm];

int main(){
    memset(f,127/3,sizeof f);
    scanf("%s",s+1);
    int n=strlen(s+1);

    for(int i=1;i<=n;i++)f[i][i]=1;

    for(int l=1;l<=n-1;l++){
	for(int i=1;i<=n-l;i++){  
	    int j=i+l;   
	    if(s[i]==s[j]) f[i][j]=min(f[i][j-1],f[i+1][j]);  
	    else for(int k=i;k<=j;k++) f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);  
	}  
    }
    
    printf("%d\n",f[1][n]);
    
    return 0;
}
