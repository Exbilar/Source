#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e4 + 10;
static const int INF = 1 << 30;

int cap[maxm],fst[maxm],nxt[maxm],to[maxm],cur[maxm];
int que[maxm],dpt[maxm],h[maxm],Ex[maxm],Ey[maxm];
int cnt = 1,n,m,k,S,T,cas;

void addedge(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
}

void ins(int f,int t,int v){
	addedge(f,t,v),addedge(t,f,0);
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
	if(x == T || !flow) return flow;
	for(int &u = cur[x];u;u = nxt[u]){
		int v = to[u];
		if(dpt[v] == dpt[x] + 1 && cap[u]){
			int res = dfs(v,std :: min(flow,cap[u]));
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
	for(int i = 1;i <= k;i++) ins(S,h[i],1);
	for(int i = 1;i <= m;i++) ins(Ex[i],Ey[i],x),ins(Ey[i],Ex[i],x);
	return dinic() >= k;
}

int main(){
	scanf("%d",&cas);
	while(cas--){
		scanf("%d%d%d",&n,&m,&k);
		S = n + 1,T = 1;
		for(int i = 1;i <= k;i++) scanf("%d",&h[i]);
		for(int i = 1;i <= m;i++) scanf("%d%d",&Ex[i],&Ey[i]);
		int l = 1,r = n,ans = 0;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(chk(mid)) ans = mid,r = mid - 1;
			else l = mid + 1;
		}
		printf("%d\n",ans);
	}

	return 0;
}
