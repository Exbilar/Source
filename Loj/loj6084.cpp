#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int get[maxm],nxt[maxm][2],vis[maxm];
char ans[maxm];
int n;

void dfs(int x){
	vis[x] = 1;
	if(x == n) return get[x] = 1,void();
	for(int i = 0;i < 2;i++){
		int v = x + nxt[x][i];
		if(v < 1 || v > n) continue;
		if(!vis[v]) dfs(v);
		get[x] |= get[v];
	}
}

void getAns(int x,int st){
	if(x == n){
		puts(ans + 1);
		exit(0);
	}
	
	if(st >= 100000){
		puts("Infinity!");
		exit(0);
	}
	
	for(int i = 0;i < 2;i++){
		int v = x + nxt[x][i];
		if(v < 1 || v > n || !get[v]) continue;
		ans[st] = i + 'a';
		getAns(v,st + 1);
	}
}

int main(){
	
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&nxt[i][0]);
	for(int i = 1;i <= n;i++) scanf("%d",&nxt[i][1]);
	
	dfs(1);
	
	if(!get[1]) return puts("No solution!"),0;
	
	memset(vis,0,sizeof vis);
	
	getAns(1,1);

	return 0;
}
