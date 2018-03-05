#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 1e2 + 10;
static const int INF = 1 << 30;

int cap[maxm],fst[maxm],nxt[maxm],to[maxm],cst[maxm],dis[maxm],usd[maxn][maxn];
int que[maxm],inq[maxm],link[maxm],idx[maxn][maxn],ddf[maxn][maxn],_ddf[maxn][maxn];
int allf,allc,n,m,S,T,ID,cnt = 1;

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
	allf += f,allc += dis[T] * f;

	return true;
}

int mcmf(){
	while(spfa());
	return allc;
}

int dx[] = {0,0,1,-1,1,1,-1,-1};
int dy[] = {1,-1,0,0,1,-1,1,-1};

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) scanf("%1d",&ddf[i][j]);

	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) scanf("%1d",&_ddf[i][j]);

	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) scanf("%1d",&usd[i][j]);
	
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) idx[i][j] = ++ID;
	
	S = ID + ID + ID + 1,T = S + 1; int sumb = 0,sumw = 0;
	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(ddf[i][j] == _ddf[i][j])
				ins(idx[i][j],idx[i][j] + ID,usd[i][j] >> 1,0),
					ins(idx[i][j] + ID,idx[i][j] + ID + ID,usd[i][j] >> 1,0);
			
			if(!ddf[i][j] && _ddf[i][j])
				ins(idx[i][j],idx[i][j] + ID,(usd[i][j] + 1) >> 1,0),sumb++,
					ins(idx[i][j] + ID,idx[i][j] + ID + ID,usd[i][j] >> 1,0),
					ins(idx[i][j] + ID,T,1,0);

			if(ddf[i][j] && !_ddf[i][j])
				ins(idx[i][j],idx[i][j] + ID,usd[i][j] >> 1,0),sumw++,
					ins(idx[i][j] + ID,idx[i][j] + ID + ID,(usd[i][j] + 1) >> 1,0),
					ins(S,idx[i][j] + ID,1,0);
		}
	}
	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			for(int dir = 0;dir < 8;dir++){
				int nx = i + dx[dir],ny = j + dy[dir];
				if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
				ins(idx[i][j] + ID + ID,idx[nx][ny],INF,1);
			}
		}
	}

	mcmf();
	if(sumb != sumw) return puts("-1"),0;
	printf("%d\n",allf == sumb ? allc : -1);
	
	return 0;
}
