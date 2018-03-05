#include <cstdio>
#include <algorithm>

using std :: max;
using std :: min;

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

LL fst[maxm],nxt[maxm],to[maxm],val[maxm];
LL size[maxm],f[maxm],C[maxm];
LL n,cnt,ans,sum;

void ins(int f,int t,LL v){
	nxt[++cnt] = fst[f],to[cnt] = t,val[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,val[cnt] = v,fst[t] = cnt;
}

void dfs(int x,int fa){
	size[x] = C[x];
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == fa) continue;
		dfs(v,x);
		size[x] += size[v];
		f[x] += f[v] + size[v] * val[u];
	}
}

void getAns(int x,int fa){
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == fa) continue;
		ans = min(ans,ans - 2 * size[v] * val[u] + sum * val[u]);
		getAns(v,x);
	}
}

int main(){
	LL x,y,v;
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++) scanf("%lld",&C[i]),sum += C[i];
	for(int i = 1;i < n;i++) scanf("%lld%lld%lld",&x,&y,&v),ins(x,y,v);

	dfs(1,0); ans = f[1];
	getAns(1,0);
	
	printf("%lld\n",ans);
	
	return 0;
}
