#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

static const int maxm=3e2+10;
static const int maxn=1e2+10;

int n,m,k,opt;
int v[maxm][maxm];

struct BIT{
	int tr[maxm][maxm];
	BIT(){memset(tr,0,sizeof tr);}
	
	int lowbit(int x){
		return x&-x;
	}
	
	int add(int x,int y,int val){
		for(int i=x;i<=n;i+=lowbit(i))
			for(int j=y;j<=m;j+=lowbit(j))
				tr[i][j]+=val;
	}
	
	int Query(int x,int y){
		int ret=0;
		for(int i=x;i;i-=lowbit(i))
			for(int j=y;j;j-=lowbit(j))
				ret+=tr[i][j];
		return ret;
	}
	
	int solve(int x1,int y1,int x2,int y2){
		return Query(x2,y2)-Query(x2,y1-1)-Query(x1-1,y2)+Query(x1-1,y1-1);
	}
	
}bit[maxn];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&v[i][j]),bit[v[i][j]].add(i,j,1);
	
	scanf("%d",&k);
	
	while(k--){
		int x,y,c,x1,y1,x2,y2;
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d%d%d",&x,&y,&c);
			bit[v[x][y]].add(x,y,-1);
			v[x][y]=c;
			bit[v[x][y]].add(x,y,1);
		}else{
			scanf("%d%d%d%d%d",&x1,&x2,&y1,&y2,&c);
			printf("%d\n",bit[c].solve(x1,y1,x2,y2));
		}
	}

	return 0;
}
