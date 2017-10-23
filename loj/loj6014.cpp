#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

struct sequence{
	int l,r,rnkl,rnkr;
}seq[maxm];

int nxt[maxm],to[maxm],cap[maxm],fst[maxm],dis[maxm],cst[maxm];
int que[maxm],inq[maxm],vis[maxm],link[maxm],tmp[maxm];
int n,m,S,T,allf,allc,tot,cnt = 1;

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
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%d%d",&seq[i].l,&seq[i].r);
		if(seq[i].l > seq[i].r) std :: swap(seq[i].l,seq[i].r);
		tmp[++tot] = seq[i].l,tmp[++tot] = seq[i].r;
	}

	std :: sort(tmp + 1,tmp + tot + 1);
	tot = std :: unique(tmp + 1,tmp + tot + 1) - tmp - 1;
	
	S = n + n + 1,T = n + n + 2;
	
	for(int i = 1;i <= n;i++)
		seq[i].rnkl = std :: lower_bound(tmp + 1,tmp + tot + 1,seq[i].l) - tmp,
			seq[i].rnkr = std :: lower_bound(tmp + 1,tmp + tot + 1,seq[i].r) - tmp;

	ins(S,1,m,0),ins((n << 1),T,m,0);
	for(int i = 1;i < (n << 1);i++) ins(i,i + 1,INF,0);
	for(int i = 1;i <= n;i++) ins(seq[i].rnkl,seq[i].rnkr,1,seq[i].l - seq[i].r);

	printf("%d\n",-mcmf());
	
	return 0;
}
