#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int cur[maxm],fst[maxm],to[maxm],nxt[maxm],cap[maxm];
int que[maxm],dpt[maxm],A[maxm],B[maxm];
int cnt = 1,n,m,S,T,sum;

void addedge(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
}

void ins(int f,int t,int v){
	addedge(f,t,v),addedge(t,f,0);
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
			if(!dpt[v] && cap[u]){
				dpt[que[++tail] = v] = dpt[x] + 1;
				if(v == T) return true;
			}
		}
	}
	return false;
}

int dfs(int x,int flow){
	if(x == T || !flow) return flow;
	for(int &u = cur[x];u;u = nxt[u]){
		int v = to[u];
		if(dpt[v] == dpt[x] + 1 && cap[u]){
			int res = dfs(v,std :: min(flow,cap[u]));
			if(res) return cap[u] -= res,cap[u ^ 1] += res,res;
		}
	}
	return 0;
}

int dinic(){
	int res = 0,flow = 0;
	while(bfs()){
		memcpy(cur,fst,sizeof cur);
		while(flow = dfs(S,INF)) res += flow;
	}
	return res;
}

bool chk(int x,int y){
	int sum = x * x + y * y;
	int sqr = sqrt(sum);
	return sqr * sqr == sum || std :: __gcd(x,y) == 1;
}

int main(){
	scanf("%d",&n);
	S = n + 1,T = n + 2;
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	for(int i = 1;i <= n;i++) scanf("%d",&B[i]),sum += B[i];

	for(int i = 1;i <= n;i++)
		if(i & 1) ins(S,i,B[i]);
		else ins(i,T,B[i]);
	
	for(int i = 1;i < n;i++)
		for(int j = 1;j <= n;j++)
			if(chk(A[i],A[j]) && (A[i] & 1) && !(A[j] & 1)) ins(i,j,INF);

	printf("%d\n",sum - dinic());
	
	return 0;
}
