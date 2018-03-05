#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int cap[maxm],nxt[maxm],fst[maxm],to[maxm],cst[maxm],dis[maxm];
int que[maxm],link[maxm],inq[maxm],A[maxm];
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
	allc += dis[T] * f,allf += f;

	return true;
}

int mcmf(){
	while(spfa());
	return allc;
}

int main(){
	int x,y,z;
	
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);

	S = n + 2,T = n + 3;
	
	for(int i = 1;i <= n + 1;i++){
		if(A[i] > A[i - 1]) ins(S,i,A[i] - A[i - 1],0);
		if(A[i] < A[i - 1]) ins(i,T,A[i - 1] - A[i],0);
	}

	for(int i = 1;i <= m;i++){
		scanf("%d%d%d",&x,&y,&z);
		ins(x,y + 1,INF,-z);
	}

	for(int i = 1;i <= n;i++) ins(i,i + 1,INF,0);

	printf("%d\n",-mcmf());
	
	return 0;
}
