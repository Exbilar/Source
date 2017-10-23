#include <cstdio>

static const int maxm=1e3+10;

int map[maxm][maxm],l[maxm][maxm],r[maxm][maxm],up[maxm][maxm];
int ans;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	    scanf("%d",&map[i][j]),map[i][j]=!(map[i][j]);
    
    for(int i=1;i<=n;i++)l[0][i]=0;r[0][i]=n;

    for(int i=1;i<=n;i++){
	int x=1;
	for(int j=1;j<=n;j++){
	    if(map[i][j])l[i][j]=x;
	    else l[i][j]=0,x=j+1;
	}
	int x=n;
	for(int j=n;j>=1;j--){
	    if(map[i][j])r[i][j]=x;
	    else r[i][j]=n,x=j-1;
	}
	for(int j=1;j<=n;j++){
	    if(map[i][j]){
		up[i][j]=up[i-1][j]+1;
		l[i][j]=max(l[i][j],l[i-1][j]);
		r[i][j]=min(r[i][j],r[i-1][j]);
		ans=max(ans,(r[i][j]-l[i][j]+1)*up[i][j]);
	    }
	}
    }

    printf("%d\n",ans);
    
    return 0;
}
