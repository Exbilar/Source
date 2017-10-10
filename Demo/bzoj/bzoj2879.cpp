#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 2e6 + 10;
static const int maxn = 2e3 + 10;
static const int INF = ~(1 << 31);

int fst[maxm],nxt[maxm],to[maxm],cap[maxm],cst[maxm],dis[maxm],link[maxm];
int que[maxm],vis[maxm],inq[maxm],W[maxn][maxn],C[maxm],sum[maxm];
int cnt = 1,S,tot,T,n,m,allc,allf;

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
	for(int i = 1;i <= m * tot + n + 2;i++) dis[i] = INF,inq[i] = 0;
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
	
	return dis[T] != INF ? true : false;
}

void mcmf(){
	while(spfa()){
		int f = INF;
		for(int u = link[T];u;u = link[to[u ^ 1]]) f = std :: min(f,cap[u]);
		for(int u = link[T];u;u = link[to[u ^ 1]]) cap[u] -= f,cap[u ^ 1] += f;
		int x = (to[link[T] ^ 1] - n - 1) / tot + 1;
		int y = (x - 1) * tot + (++sum[x]) + n;
		ins(y,T,1,0); allc += dis[T] * f;
		for(int i = 1;i <= n;i++) ins(i,y,1,W[i][x] * sum[x]);
	}
}

int get(int x,int y){
	return (x - 1) * tot + y + n;
}

int main(){
	int x,y,z,w;
	read(n),read(m);
	for(int i = 1;i <= n;i++) read(C[i]),tot += C[i];
	
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) read(W[i][j]);

	S = m * tot + n + 1,T = S + 1;
	for(int i = 1;i <= n;i++) ins(S,i,C[i],0);
	for(int i = 1;i <= m;i++) ins(get(i,1),T,1,0);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) ins(i,get(j,1),1,W[i][j]);

	for(int i = 1;i <= m;i++) sum[i] = 1;
	
	mcmf();

	printf("%d\n",allc);
	
	return 0;
}
