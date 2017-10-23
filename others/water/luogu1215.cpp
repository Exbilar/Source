#include <cstdio>
#include <algorithm>

using std :: max;
using std :: min;

static const int maxm = 1e2 + 10;

int vis[maxm][maxm][maxm],ans[maxm];
int cnt,xl,yl,zl;

void dfs(int x,int y,int z){
	if(vis[x][y][z]) return ;
	if(!x) ans[++cnt] = z;
	vis[x][y][z] = 1;
	
	if(x){
		if(y < yl) dfs(x - min(x,yl - y),y + min(x,yl - y),z);
		if(z < zl) dfs(x - min(x,zl - z),y,z + min(x,zl - z));
	}

	if(y){
		if(x < xl) dfs(x + min(y,xl - x),y - min(y,xl - x),z);
		if(z < zl) dfs(x,y - min(y,zl - z),z + min(y,zl - z));
	}

	if(z){
		if(x < xl) dfs(x + min(z,xl - x),y,z - min(z,xl - x));
		if(y < yl) dfs(x,y + min(yl - y,z),z - min(z,yl - y));
	}
	
}

int main(){
	scanf("%d%d%d",&xl,&yl,&zl);

	dfs(0,0,zl);

	std :: sort(ans + 1,ans + cnt + 1);
	
	for(int i = 1;i <= cnt;i++) printf("%d ",ans[i]);
	putchar(10);
	
	return 0;
}
