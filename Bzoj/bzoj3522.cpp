#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

static const int maxm=1e5+10;

int nxt[maxm],fst[maxm],to[maxm],num[maxm],f[maxm],g[maxm],son[maxm];
int cnt,n;
LL ans;

void ins(int f,int t){
	nxt[++cnt]=fst[f];
	to[cnt]=t;
	fst[f]=cnt;
	son[f]++;
}

void dfs(int x,int ftr,int dpt){
	num[dpt]++;
	for(int u=fst[x];u;u=nxt[u])
		if(to[u]!=ftr)
			dfs(to[u],x,dpt+1);
}

int main(){
	int u,v;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
		scanf("%d%d",&u,&v),ins(u,v),ins(v,u);
	
	for(int x=1;x<=n;x++){
		if(son[x]<3)continue;
		memset(f,0,sizeof f);
		memset(g,0,sizeof g);
		for(int u=fst[x];u;u=nxt[u]){
			memset(num,0,sizeof num);
			int v=to[u];
			dfs(v,x,1);
			for(int i=1;i<=n;i++){
				ans+=(LL)g[i]*num[i];
				g[i]+=f[i]*num[i];
				f[i]+=num[i];
			}
		}
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
