#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

static const int maxm=5e5+10;

int nxt[maxm<<1],to[maxm<<1],fst[maxm<<1];
LL f[maxm],val[maxm<<1];
LL ans;
int cnt,rt,n;

void ins(int f,int t,int v){
	nxt[++cnt]=fst[f];
	fst[f]=cnt;
	to[cnt]=t;
	val[cnt]=v;
}

void dfs(int x,int ftr){
	for(int u=fst[x];u;u=nxt[u]){
		int v=to[u];
		if(v==ftr)continue;
		dfs(v,x);
		f[x]=max(f[x],f[v]+val[u]);
	}
	for(int u=fst[x];u;u=nxt[u])
		if(to[u]!=ftr)
			ans+=f[x]-f[to[u]]-val[u];
}

int main(){
	int u,v;LL w;
	scanf("%d%d",&n,&rt);
	for(int i=1;i<n;i++)scanf("%d%d%lld",&u,&v,&w),ins(u,v,w),ins(v,u,w);
	
	dfs(rt,0);
	
	printf("%lld\n",ans);
	
	return 0;
}
