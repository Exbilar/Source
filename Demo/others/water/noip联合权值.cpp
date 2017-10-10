#include <cstdio>
#include <algorithm>

#define chkmax(a,b) (a>b?a:b)
#define chkmin(a,b) (a<b?a:b)

static const int maxm=1e6+10;
static const int MOD=10007;

int nxt[maxm],to[maxm],fst[maxm],val[maxm],f[maxm];
int cnt,n,ans_max,ans_sum;

void ins(int f,int t){
	nxt[++cnt]=fst[f];
	to[cnt]=t;
	fst[f]=cnt;
}

void dfs(int x){
	int sum=0,max=0,snd=0;
	for(int u=fst[x];u;u=nxt[u]){
		int v=to[u];
		if(val[v]>max)snd=max,max=val[v];
		else if(val[v]>snd)snd=val[v];
		ans_sum=(ans_sum+sum*val[v])%MOD;
		sum=(sum+val[v])%MOD;
	}
	ans_max=chkmax(ans_max,max*snd);
}

int main(){
	int u,v;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
		scanf("%d%d",&u,&v),ins(u,v),ins(v,u);
	
	for(int i=1;i<=n;i++)scanf("%d",&val[i]);
	
	for(int i=1;i<=n;i++)dfs(i);
	
	printf("%d %d\n",ans_max,(ans_sum<<1)%MOD);
	
	return 0;
}
