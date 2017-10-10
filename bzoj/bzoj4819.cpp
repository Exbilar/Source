#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 2e3 + 10;
static const double eps = 1e-8;
static const int INF = 1 << 30;

int fst[maxm],nxt[maxm],to[maxm],link[maxm],inq[maxm],que[maxm];
double cap[maxm],cst[maxm],dis[maxm],A[maxn][maxn],B[maxn][maxn];
int cnt = 1,n,m,S,T;
double allf,allc;

void ins(int f,int t,double v,double c){
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

	double f = INF;
	for(int u = link[T];u;u = link[to[u ^ 1]]) f = std :: min(f,cap[u]);
	for(int u = link[T];u;u = link[to[u ^ 1]]) cap[u] -= f,cap[u ^ 1] += f;
	allc += dis[T] * f,allf += f;
	return true;
}

void mcmf(){
	while(spfa());
}

bool chk(double val){
	memset(fst,0,sizeof fst),cnt = 1,allf = 0,allc = 0;
	for(int i = 1;i <= n;i++) ins(S,i,1,0),ins(i + n,T,1,0);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++) ins(i,j + n,1,B[i][j] * val - A[i][j]);
	mcmf();
	
	return allc <= eps;
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++) scanf("%lf",&A[i][j]);

	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++) scanf("%lf",&B[i][j]);
	
	double l = 0,r = 100000,ans = 0;
	S = n + n + 1,T = n + n + 2;
	
	while(r - l > eps){
		double mid = (l + r) / 2.0;
		if(chk(mid)) ans = mid,l = mid + eps;
		else r = mid - eps;
	}

	printf("%lf\n",ans);

	return 0;
}
