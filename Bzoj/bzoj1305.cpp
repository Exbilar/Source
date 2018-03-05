#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 2e3 + 10;
static const int INF = 1 << 30;

int cap[maxm],cur[maxm],fst[maxm],to[maxm],nxt[maxm],que[maxn],dpt[maxn];
char ddf[maxn][maxn];
int cnt = 1,n,k,S,T;

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,fst[t] = cnt;
}

bool bfs(){
	memset(dpt,0,sizeof dpt);
	int head = 1,tail = 0;
	que[++tail] = S;
	dpt[S] = 1;

	while(head <= tail){
		int x = que[head++];
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(!dpt[v] && cap[u]){
				dpt[que[++tail] = v] = dpt[x] + 1;
				if(v == T) return true;
			}
		}
	}
	return false;
}

int dfs(int x,int flow){
	int res = 0;
	if(x == T || !flow) return flow;
	for(int &u = cur[x];u;u = nxt[u]){
		int v = to[u];
		if(dpt[v] == dpt[x] + 1 && cap[u]){
			res = dfs(v,std :: min(flow,cap[u]));
			if(res) return cap[u] -= res,cap[u ^ 1] += res,res;
		}
	}
	return 0;
}

int dinic(){
	int res = 0,flow = 0;
	while(bfs()){
		memcpy(cur,fst,sizeof cur);
		while(flow = dfs(S,INF)) res += flow;
	}
	return res;
}


bool chk(int x){

	memset(fst,0,sizeof fst),cnt = 1;
	
	for(int i = 1;i <= n;i++)
		ins(i,i + (n << 1),k),ins(i + n + (n << 1),i + n,k);
	
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++)
			if(ddf[i][j] == 'Y') ins(i,j + n,1);
			else ins(i + (n << 1),j + n + (n << 1),1);
	
	for(int i = 1;i <= n;i++) ins(S,i,x),ins(i + n,T,x);
	return dinic() == n * x;
}

int main(){
	scanf("%d%d",&n,&k);
	S = (n << 2) + 1,T = (n << 2) + 2;
	for(int i = 1;i <= n;i++)
		scanf("%s",ddf[i] + 1);
		
	int l = 1,r = INF,ans = 0;

	while(l <= r){
		int mid = (l + r) >> 1;
		if(chk(mid)) ans = mid,l = mid + 1;
		else r = mid - 1;
	}

	printf("%d\n",ans);
	
	return 0;
}
