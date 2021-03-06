#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 2e5 + 10;
static const int INF = 1 << 30;

int fst[maxm],nxt[maxm],to[maxm],cap[maxm],cst[maxm],dis[maxm],link[maxm];
int que[maxm],vis[maxm],inq[maxm],r[maxm];
int cnt = 1,S,T,allc,n,_P,_M,_F,_N,_S;

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
	for(int i = 1;i <= n + n + 2;i++) dis[i] = INF,inq[i] = 0;
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
	allc += dis[T] * f;
	return true;
}

int mcmf(){
	while(spfa());
}

int main(){
	scanf("%d%d%d%d%d%d",&n,&_P,&_M,&_F,&_N,&_S);
	S = n + n + 1,T = n + n + 2;
	for(int i = 1;i <= n;i++){
		if(i + 1 <= n) ins(i,i + 1,INF,0);
		if(i + _M <= n) ins(i,i + n + _M,INF,_F);
		if(i + _N <= n) ins(i,i + n + _N,INF,_S);
		ins(S,i + n,INF,_P);
	}

	for(int i = 1;i <= n;i++) read(r[i]),ins(S,i,r[i],0),ins(i + n,T,r[i],0);
	
	mcmf();
	
	printf("%d\n",allc);
	
	return 0;
}
