c#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 2e2 + 10;
static const int maxx = 1e4 + 10;
static const int INF = 1 << 30;

int cap[maxm],nxt[maxm],fst[maxm],to[maxm],dis[maxm],cst[maxm];
int que[maxm],inq[maxm],link[maxm],ddf[maxn][maxn],E[maxx][maxn];
int allc,allf,n,m,S,T,cnt = 1;

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

int idx(int i,int j){
	return n + (i - 1) * n + j;
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++) scanf("%d",&ddf[i][j]);
	
	S = n * n + n + 1,T = S + 1;
	
	for(int i = 1;i < n;i++){
		for(int j = i + 1;j <= n;j++){
			ins(S,idx(i,j),1,0);
			if(ddf[i][j] == 1) ins(idx(i,j),i,1,0);
			if(ddf[i][j] == 0) ins(idx(i,j),j,1,0);
			if(ddf[i][j] == 2)
				ins(idx(i,j),i,1,0),E[idx(i,j)][i] = cnt - 1,
					ins(idx(i,j),j,1,0),E[idx(i,j)][j] = cnt - 1;
		}
	}
	
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++) ins(i,T,1,j - 1);

	printf("%d\n",n * (n - 2) * (n - 1) / 6 - mcmf());
	
	for(int i = 1;i < n;i++){
		for(int j = 1;j <= n;j++){
			if(ddf[i][j] == 2){
				ddf[i][j] = (cap[E[idx(i,j)][i]] == 0);
				ddf[j][i] = ddf[i][j] ^ 1;
			}
		}
	}

	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			printf("%d ",ddf[i][j]);
		}
		putchar(10);
	}
	
	return 0;
}
