#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e5+10;

int to[maxm<<2],nxt[maxm<<2],fst[maxm<<2],f[maxm][25],val[maxm],ftr[maxm];
int cnt,n,k;

void ins(int f,int t){
	nxt[++cnt]=fst[f];
	fst[f]=cnt;
	to[cnt]=t;
}

void dfs(int x,int father){
	ftr[x]=father;f[x][0]=val[x];
	for(int u=fst[x];u;u=nxt[u]){
		int v=to[u];
		if(v==father)continue;
		dfs(v,x);
		for(int j=1;j<=k;j++)
			f[x][j]+=f[v][j-1];
	}
}

void calc(int x){
	int m=k;int ans=f[x][m];
	while(x!=1&&m){
		ans+=f[ftr[x]][--m];
		if(m)ans-=f[x][m-1];
		x=ftr[x];	
	}
	printf("%d\n",ans);
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		ins(u,v);ins(v,u);
	}
	
	for(int i=1;i<=n;i++)scanf("%d",&val[i]);
	dfs(1,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=k;j++)
			f[i][j]+=f[i][j-1];
	
	for(int i=1;i<=n;i++)calc(i);
	
	return 0;
}
