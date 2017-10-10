#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 2e5 + 10;
static const int maxn = 2e3 + 10;
static const int INF = ~(1 << 31);

int fst[maxm],nxt[maxm],to[maxm],cap[maxm],cst[maxm],dis[maxm],link[maxm];
int que[maxm],vis[maxm],inq[maxm],r[maxm],idx[maxn][maxn],ddf[maxn][maxn];
char str[maxn][maxn];
int cnt = 1,S,T,n,m,ID,allc,allf;

int dx[] = {0,0,-1,1};
int dy[] = {-1,1,0,0};

void ins(int f,int t,int v,int c){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,cst[cnt] = c,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,cst[cnt] = -c,fst[t] = cnt;
}

bool spfa(){
	for(int i = 1;i <= T;i++) dis[i] = INF,inq[i] = 0;
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

int mcmf(){
	while(spfa());
}

int main(){
	int x,y,z,w;
	scanf("%d%d",&n,&m);
	
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) idx[i][j] = ++ID;

	for(int i = 1;i <= n;i++) scanf("%s",str[i] + 1);

	S = ID * 2 + 1,T = ID * 2 + 2;
	
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			if(str[i][j] == 'L') ddf[i][j] = 0;
			else if(str[i][j] == 'R') ddf[i][j] = 1;
			else if(str[i][j] == 'U') ddf[i][j] = 2;
			else if(str[i][j] == 'D') ddf[i][j] = 3;
	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			for(int dir = 0;dir < 4;dir++){
				int nx = i + dx[dir],ny = j + dy[dir];
				if(nx < 1) nx = n; if(nx > n) nx = 1;
				if(ny < 1) ny = m; if(ny > m) ny = 1;
				if(ddf[i][j] == dir) ins(idx[i][j],idx[nx][ny] + ID,1,0);
				else ins(idx[i][j],idx[nx][ny] + ID,1,1);
			}
		}
	}
	
	for(int i = 1;i <= ID;i++) ins(S,i,1,0),ins(i + ID,T,1,0);
	
	mcmf();

	printf("%d\n",allc);
	
	return 0;
}
