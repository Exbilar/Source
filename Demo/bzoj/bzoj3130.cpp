#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

static const int maxm = 2e5 + 10;
static const int INF = 1 << 30;
static const double eps = 1e-6;

int fst[maxm],nxt[maxm],to[maxm],cur[maxm],que[maxm],dpt[maxm],Ex[maxm],Ey[maxm];
double cap[maxm],Ez[maxm];
int n,m,P,S,T,cnt = 1;

void ins(int f,int t,double v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,fst[t] = cnt;
}

bool bfs(){
	memset(dpt,0,sizeof dpt);
	int head = 1,tail = 0;
	que[++tail] = S;
	dpt[S] = 1;

	while(head <= tail){
		int x = que[head++];
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(!dpt[v] && fabs(cap[u]) > eps){
				dpt[que[++tail] = v] = dpt[x] + 1;
				if(v == T) return true;
			}
		}
	}
	return false;
}

double dfs(int x,double flow){
	if(x == T || fabs(flow) < eps) return flow;
	for(int &u = cur[x];u;u = nxt[u]){
		int v = to[u];
		if(dpt[v] == dpt[x] + 1 && fabs(cap[u]) > eps){
			double res = dfs(v,std :: min(cap[u],flow));
			if(fabs(res) > eps) return cap[u] -= res,cap[u ^ 1] += res,res;
		}
	}
	return 0;
}

double dinic(){
	double res = 0,flow = 0;
	while(bfs()){
		memcpy(cur,fst,sizeof cur);
		while(flow = dfs(S,INF)) res += flow;
	}
	return res;
}

double chk(double x){
	memset(fst,0,sizeof fst),cnt = 1;
	for(int i = 1;i <= m;i++) ins(Ex[i],Ey[i],std :: min(Ez[i],x));
	return dinic();
}

int main(){
	double l = 0,r = 0,ans = 0;
	
	scanf("%d%d%d",&n,&m,&P); S = 1,T = n;
	for(int i = 1;i <= m;i++)
		scanf("%d%d%lf",&Ex[i],&Ey[i],&Ez[i]),ins(Ex[i],Ey[i],Ez[i]),r = std :: max(r,Ez[i]);
	
	double flow = dinic();

	printf("%.0lf\n",flow);

	while(r - l > eps){
		double mid = (l + r) / 2.0;
		if(fabs(chk(mid) - flow) < eps) r = mid;
		else l = mid;
	}

	printf("%lf\n",l * P);
	
	return 0;
}
