#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 2e3 + 10;
static const int INF = 1 << 30;

int fst[maxm],nxt[maxm],to[maxm],cap[maxm],cst[maxm],idx[maxn][maxn];
int dis[maxm],que[maxm],vis[maxm],inq[maxm],link[maxm],ddf[maxn][maxn];
int cnt = 1,allc,allf,n,m,S,T,ID;

void ins(int f,int t,int v,int c){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,cst[cnt] = c,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,cst[cnt] = -c,fst[t] = cnt;
}

bool spfa(){
	for(int i = 1;i <= ID + ID + 2;i++) dis[i] = INF,inq[i] = 0;
	int head = 1,tail = 0;
	dis[S] = 0,inq[S] = 1;
	que[++tail] = S;

	while(head <= tail){
		int x = que[head++]; inq[x] = 0;
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(dis[v] > dis[x] + cst[u] && cap[u]){
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
	allc += dis[T] * f;
	allf += f;
	return true;
}

void mcmf(){
	while(spfa());
}

int main(){
	scanf("%d%d",&m,&n);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m + i - 1;j++)
			scanf("%d",&ddf[i][j]),idx[i][j] = ++ID;

	S = ID + ID + 1,T = ID + ID + 2;

	//-----------------------------------------------------------------------------------------------
	
	for(int i = 1;i <= ID;i++) ins(i,i + ID,1,0);
	for(int i = 1;i <= m;i++) ins(S,i,1,-ddf[1][i]);
	for(int i = 1;i <= m + n - 1;i++) ins(ID - m - n + i + 1 + ID,T,1,0);

	for(int i = 1;i < n;i++)
		for(int j = 1;j <= m + i - 1;j++)
			ins(idx[i][j] + ID,idx[i + 1][j],1,-ddf[i + 1][j]),
				ins(idx[i][j] + ID,idx[i + 1][j + 1],1,-ddf[i + 1][j + 1]);

	mcmf();

	printf("%d\n",-allc);
	
	//-----------------------------------------------------------------------------------------------
	
	memset(fst,0,sizeof fst),cnt = 1,allc = 0;

	for(int i = 1;i <= ID;i++) ins(i,i + ID,m,0);
	for(int i = 1;i <= m;i++) ins(S,i,1,-ddf[1][i]);
	for(int i = 1;i <= m + n - 1;i++) ins(ID - m - n + i + 1 + ID,T,m,0);

	for(int i = 1;i < n;i++)
		for(int j = 1;j <= m + i - 1;j++)
			ins(idx[i][j] + ID,idx[i + 1][j],1,-ddf[i + 1][j]),
				ins(idx[i][j] + ID,idx[i + 1][j + 1],1,-ddf[i + 1][j + 1]);

	mcmf();
	
	printf("%d\n",-allc);

	//------------------------------------------------------------------------------------------------
	
	memset(fst,0,sizeof fst),cnt = 1,allc = 0;

	for(int i = 1;i <= ID;i++) ins(i,i + ID,m,0);
	for(int i = 1;i <= m;i++) ins(S,i,1,-ddf[1][i]);
	for(int i = 1;i <= m + n - 1;i++) ins(ID - m - n + i + 1 + ID,T,m,0);

	for(int i = 1;i < n;i++)
		for(int j = 1;j <= m + i - 1;j++)
			ins(idx[i][j] + ID,idx[i + 1][j],m,-ddf[i + 1][j]),
				ins(idx[i][j] + ID,idx[i + 1][j + 1],m,-ddf[i + 1][j + 1]);

	mcmf();
	
	printf("%d\n",-allc);

	//------------------------------------------------------------------------------------------------
	
	return 0;
}
