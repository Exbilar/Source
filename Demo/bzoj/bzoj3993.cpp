#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 2e3 + 10;
static const int INF = 1 << 30;
static const double eps = 1e-8;

int fst[maxm],cur[maxm],to[maxm],nxt[maxm],que[maxm],dpt[maxm],ddf[maxn][maxn];
double cap[maxm],A[maxm],B[maxm];
int cnt = 1,n,m,S,T;
double sum,ans;

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
            double res = dfs(v,std :: min(flow,cap[u]));
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

bool chk(double x){
	memset(fst,0,sizeof fst),cnt = 1;

	for(int i = 1;i <= m;i++) ins(S,i,x * B[i]);
	for(int i = m + 1;i <= n + m;i++) ins(i,T,A[i]);
	for(int i = 1;i <= m;i++)
		for(int j = 1;j <= n;j++)
			if(ddf[i][j]) ins(i,j + m,INF);

	return std :: fabs(dinic() - sum) < eps ? true : false;
}

int main(){
	int x;
	scanf("%d%d",&n,&m);
	for(int i = m + 1;i <= n + m;i++) scanf("%lf",&A[i]),sum += A[i];
	for(int i = 1;i <= m;i++) scanf("%lf",&B[i]);

	for(int i = 1;i <= m;i++)
		for(int j = 1;j <= n;j++)
			scanf("%d",&ddf[i][j]);
	
	double l = 0.0,r = (double) INF;

	S = n + m + 1,T = n + m + 2;
	
	while(r - l > eps){
		double mid = (l + r) / 2;
		if(chk(mid)) ans = mid,r = mid;
		else l = mid;
	}

	printf("%.6lf\n",ans);
	
	return 0;
}
