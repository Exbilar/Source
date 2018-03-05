#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

static const LL maxm = 1e6 + 10;
static const LL INF = 1LL << 60;

LL fst[maxm],nxt[maxm],to[maxm],cap[maxm],cst[maxm],dis[maxm];
LL que[maxm],vis[maxm],inq[maxm],link[maxm],A[maxm],B[maxm],C[maxm];
LL cnt = 1,allc,allf,n,m,S,T;

void ins(LL f,LL t,LL v,LL c){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,cst[cnt] = c,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,cst[cnt] = -c,fst[t] = cnt;
}

bool spfa(){
	for(LL i = 1;i <= n + n + 2;i++) dis[i] = -INF,inq[i] = 0;
	LL head = 1,tail = 0;
	dis[S] = 0,inq[S] = 1;
	que[++tail] = S;

	while(head <= tail){
		LL x = que[head++]; inq[x] = 0;
		for(LL u = fst[x];u;u = nxt[u]){
			LL v = to[u];
			if(dis[v] < dis[x] + cst[u] && cap[u]){
				dis[v] = dis[x] + cst[u];
				link[v] = u;
				if(!inq[v]) inq[que[++tail] = v] = 1;
			}
		}
	}

	if(allc + dis[T] < 0) return false;

	LL f = INF;
	if(dis[T] < 0) f = allc / (-dis[T]);
	for(LL u = link[T];u;u = link[to[u ^ 1]]) f = std :: min(f,cap[u]);
	for(LL u = link[T];u;u = link[to[u ^ 1]]) cap[u] -= f,cap[u ^ 1] += f;

	allc += f * dis[T];
	allf += f;
	
	return true;
}

void mcmf(){
	while(spfa());
}

bool chk(LL x){
	for(LL i = 2;i <= sqrt(x);i++)
		if(x % i == 0) return false;
	return true;
}

int main(){
	scanf("%lld",&n);
	for(LL i = 1;i <= n;i++) scanf("%lld",&A[i]);
	for(LL i = 1;i <= n;i++) scanf("%lld",&B[i]);
	for(LL i = 1;i <= n;i++) scanf("%lld",&C[i]);

	S = n + n + 1,T = n + n + 2;

	for(LL i = 1;i <= n;i++) ins(S,i,B[i],0),ins(i + n,T,B[i],0);
	for(LL i = 1;i <= n;i++)
		for(LL j = 1;j <= n;j++)
			if(A[i] % A[j] == 0 && chk(A[i] / A[j]) && i != j)
				ins(i,j + n,INF,C[i] * C[j]),ins(j,i + n,INF,C[i] * C[j]);

	mcmf();
	
	printf("%lld\n",allf / 2);
	
	return 0;
}
