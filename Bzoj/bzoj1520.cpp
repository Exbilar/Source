#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int fst[maxm],nxt[maxm],to[maxm],cap[maxm],cst[maxm],dis[maxm];
int que[maxm],inq[maxm],link[maxm],A[maxm],B[maxm],C[maxm],D[maxm];
int allf,allc,n,m,S,T,cnt = 1;

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

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
		scanf("%d%d%d%d",&A[i],&B[i],&C[i],&D[i]);

	S = n + n + 1,T = n + n + 2;

	for(int i = 1;i <= n;i++) ins(S,i,1,0),ins(i + n,T,1,0);

	for(int i = 1;i <= n;i++){
		for(int j = B[i];j <= C[i];j++){
			ins(i,j + n,1,D[i] * abs(A[i] - j));
		}
	}

	mcmf();
	
	if(allf != n) puts("NIE");
	else printf("%d\n",allc);
	
	return 0;
}
