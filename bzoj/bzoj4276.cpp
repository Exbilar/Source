#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int cst[maxm],cap[maxm],fst[maxm],nxt[maxm],to[maxm];
int que[maxm],inq[maxm],link[maxm],dis[maxm];
int lc[maxm],rc[maxm],A[maxm],B[maxm],C[maxm];
int allc,allf,n,m,S,T,rt,sz = 2,cnt = 1;

void ins(int f,int t,int v,int c){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,cst[cnt] = c,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,cst[cnt] = -c,fst[t] = cnt;
}

bool spfa(){
	for(int i = 1;i <= 30000;i++) dis[i] = INF,inq[i] = 0;
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
	return allc;
}

void build(int &x,int l,int r){
	x = ++sz;
	if(l == r) return ins(x,T,1,0),void();
	int mid = (l + r) >> 1;
	build(lc[x],l,mid);
	if(lc[x]) ins(x,lc[x],INF,0);
	build(rc[x],mid + 1,r);
	if(rc[x]) ins(x,rc[x],INF,0);
}

void Qry(int x,int l,int r,int L,int R,int pos){
	if(l >= L && r <= R) return ins(pos,x,1,0),void();
	int mid = (l + r) >> 1;
	if(L <= mid) Qry(lc[x],l,mid,L,R,pos);
	if(R > mid) Qry(rc[x],mid + 1,r,L,R,pos);
}

int main(){
	int lmin = INF,rmax = 0;
	scanf("%d",&n);

	for(int i = 1;i <= n;i++)
		scanf("%d%d%d",&A[i],&B[i],&C[i]),lmin = std :: min(lmin,A[i]),rmax = std :: max(rmax,B[i]);

	S = 1,T = 2;

	build(rt,lmin,rmax);
	
	for(int i = 1;i <= n;i++)
		ins(S,++sz,1,-C[i]),Qry(rt,lmin,rmax,A[i],B[i] - 1,sz);

	printf("%d\n",-mcmf());
	
	return 0;
}
