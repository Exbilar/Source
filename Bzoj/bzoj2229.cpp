#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e5 + 10;
static const int maxn = 2e2 + 10;
static const int INF = 1 << 30;

int cap[maxm],fst[maxm],nxt[maxm],to[maxm],cur[maxm];
int que[maxm],dpt[maxm],vis[maxm],tmp[maxm],id[maxm],ans[maxn][maxn];
int n,m,S,T,cas,tot,cnt = 1;

void read(int &in){
	in = 0; int f = 1; char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch =='-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = v,fst[t] = cnt;
}

bool bfs(){
	for(int i = 1;i <= n;i++) dpt[i] = 0;
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
		for(int i = 1;i <= n;i++) cur[i] = fst[i];
		while(flow = dfs(S,INF)) res += flow;
	}
	return res;
}

void Dfs(int x){
	vis[x] = 1;
	for(int u = fst[x];u;u = nxt[u])
		if(cap[u] && !vis[to[u]]) Dfs(to[u]);
}

void solve(int L,int R){
	if(L == R) return ;
	for(int i = 2;i <= cnt;i += 2) cap[i] = cap[i ^ 1] = (cap[i] + cap[i ^ 1]) >> 1;
	S = id[L],T = id[R];
	int flow = dinic();

	for(int i = 1;i <= n;i++) vis[i] = 0;
	Dfs(S);

	for(int i = 1;i <= n;i++)
		if(vis[i]) for(int j = 1;j <= n;j++)
				if(!vis[j]) ans[j][i] = ans[i][j] = std :: min(ans[i][j],flow); 

	int l = L,r = R;
	for(int i = L;i <= R;i++)
		if(vis[id[i]]) tmp[l++] = id[i];
		else tmp[r--] = id[i];

	for(int i = L;i <= R;i++) id[i] = tmp[i];
	solve(L,l - 1),solve(r + 1,R);
}

int main(){
	int x,y,z,q,cas;

	read(cas);
	
	while(cas--){
		memset(fst,0,sizeof fst),cnt = 1;
		
		read(n),read(m);
		for(int i = 1;i <= m;i++) read(x),read(y),read(z),ins(x,y,z);
		
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= n;j++) ans[i][j] = INF;
		
		for(int i = 1;i <= n;i++) id[i] = i;
		
		solve(1,n);
		read(q);
		
		while(q--){
			int tot = 0;
			read(x);
			for(int i = 1;i < n;i++)
				for(int j = i + 1;j <= n;j++)
					if(ans[i][j] <= x) tot++;
			printf("%d\n",tot);
		}
		putchar(10);
	}
	
	return 0;
}
