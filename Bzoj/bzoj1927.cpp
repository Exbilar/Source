#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 2e5 + 10;
static const int INF = ~(1 << 31);

int fst[maxm],nxt[maxm],to[maxm],cap[maxm],cst[maxm],dis[maxm],link[maxm];
int que[maxm],vis[maxm],inq[maxm],r[maxm];
int cnt = 1,S,T,n,m,allc,allf;

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
	allc += dis[T] * f,allf += f;
	return true;
}

int mcmf(){
	while(spfa());
}

int main(){
	int x,y,z;
	scanf("%d%d",&n,&m); S = n + n + 1,T = n + n + 2;
	for(int i = 1;i <= n;i++) ins(S,i,1,0),ins(i + n,T,1,0);
	for(int i = 1;i <= n;i++) scanf("%d",&x),ins(S,i + n,1,x);
	for(int i = 1;i <= m;i++){
		scanf("%d%d%d",&x,&y,&z);
		if(x > y) std :: swap(x,y);
		ins(x,y + n,1,z);
	}
	
	mcmf();
	
	printf("%d\n",allc);
	
	return 0;
}
