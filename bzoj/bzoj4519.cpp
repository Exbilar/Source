#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 2e5 + 10;
static const int INF = 1 << 30;

int cap[maxm],cur[maxm],fst[maxm],nxt[maxm],to[maxm];
int que[maxm],vis[maxm],dpt[maxm],id[maxm],cut[maxm],tmp[maxm];
int n,m,S,T,tot,cnt = 1;

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = v,fst[t] = cnt;
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
			if(cap[u] && !dpt[v]){
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

void DFS(int x){
	vis[x] = 1;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(!vis[v] && cap[u]) DFS(v);
	}
}

void solve(int L,int R){
	if(L == R) return ;
	for(int i = 2;i <= cnt;i += 2) cap[i] = cap[i ^ 1] = (cap[i] + cap[i ^ 1]) >> 1;
	
	S = id[L],T = id[R];
	int flow = dinic();

	memset(vis,0,sizeof vis); DFS(S);

	cut[++tot] = flow;
	
	int l = L,r = R;
	for(int i = L;i <= R;i++)
		if(vis[id[i]]) tmp[l++] = id[i];
		else tmp[r--] = id[i];

	for(int i = L;i <= R;i++) id[i] = tmp[i];
	solve(L,l - 1),solve(r + 1,R);
}

int main(){
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) id[i] = i;
	for(int i = 1;i <= m;i++) scanf("%d%d%d",&x,&y,&z),ins(x,y,z);

	solve(1,n);
	std :: sort(cut + 1,cut + tot + 1);

	int ans = 1;
	for(int i = 2;i <= tot;i++)
		if(cut[i] != cut[i - 1]) ans++;
	
	printf("%d\n",ans);
	
	return 0;
}
