#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int fst[maxm],nxt[maxm],to[maxm],cap[maxm],cst[maxm],dis[maxm],link[maxm];
int que[maxm],vis[maxm],inq[maxm],A[maxm],L[maxm],P[maxm],D[maxm],Q[maxm];
int cnt = 1,S,T,allc,allf,n,m,k,cas;

void read(int &in){
	in = 0; int f = 1; char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

void ins(int f,int t,int v,int c){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,cst[cnt] = c,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,cst[cnt] = -c,fst[t] = cnt;
}

bool spfa(){
	for(int i = 1;i <= m + n + n + 2;i++) dis[i] = INF,inq[i] = 0;
	int head = 1,tail = 0;
	dis[S] = 0,inq[S] = 1;
	que[++tail] = S;

	while(head <= tail){
		int x = que[head++]; inq[x] = 0;
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(cap[u] && dis[v] > dis[x] + cst[u]){
				dis[v] = dis[x] + cst[u];
				link[v] = u;
				if(!inq[v]) inq[que[++tail] = v] = 1;
			}
		}
	}
	
	if(dis[T] == INF) return false;
	
	int f = INF;
	for(int u = link[T];u;u = link[to[u ^ 1]]) f = std :: min(f,cap[u]);
	for(int u = link[T];u;u = link[to[u ^ 1]]) cap[u] -= f,cap[u ^ 1] += f;
	allc += dis[T] * f,allf += f;
	return true;
}

int dfs(int x,int flow){
	if(vis[x]) return 0;
	if(x == T || !flow) return allc += dis[T] * flow,flow;
	
	vis[x] = 1; int res = 0,f = 0;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(dis[v] == dis[x] + cst[u] && cap[u]){
			if(f = dfs(v,std :: min(flow,cap[u]))){
				cap[u] -= f,cap[u ^ 1] += f;
				res += f,flow -= f;
			}
		}
	}

	vis[x] = 0;
	return res;
}

int mcmf(){
	while(spfa());
	return allc;
}

int main(){
	scanf("%d",&cas); int tot = 0;
	while(cas--){
		memset(fst,0,sizeof fst),cnt = 1; int sum = 0;
		read(n),read(m),read(k); S = m + n + n + 1,T = m + n + n + 2;
		for(int i = 1;i <= n;i++) read(A[i]),sum += A[i];
		for(int i = 1;i <= m;i++) read(L[i]),read(P[i]);
		for(int i = 1;i <= k;i++) read(D[i]),read(Q[i]);
		for(int i = 1;i <= n;i++) ins(S,m + i,A[i],0),ins(m + i + n,T,A[i],0);
		for(int i = 1;i <= m;i++) ins(S,i,L[i],0);
		for(int i = 1;i <= m;i++)
			for(int j = 1;j <= n;j++) ins(i,m + j + n,INF,P[i]);
		for(int i = 1;i < n;i++) ins(m + i,m + i + 1,INF,0);
		for(int i = 1;i <= k;i++)
			for(int j = 1;j <= n;j++)
				if(j + D[i] + 1 <= n) ins(j + m,j + m + n + D[i] + 1,INF,Q[i]);
		
		mcmf();
		if(allf == sum) printf("Case %d: %d\n",++tot,allc);
		else printf("Case %d: impossible\n",++tot);
	}
	
	
	return 0;
}
