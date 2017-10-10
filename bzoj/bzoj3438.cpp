#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 4e6 + 10;
static const int INF = 1 << 30;

int cur[maxm],fst[maxm],nxt[maxm],to[maxm],cap[maxm];
int que[maxm],dpt[maxm],A[maxm],B[maxm];
int cnt = 1,n,m,in,sum,S,T;

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

int main(){
	int x,y,z;
	scanf("%d",&n);
	S = maxm >> 1,T = S + 1;
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),sum += A[i],ins(S,i,A[i]);
	for(int i = 1;i <= n;i++) scanf("%d",&B[i]),sum += B[i],ins(i,T,B[i]);
	scanf("%d",&m);
	
	for(int i = 1;i <= m;i++){
		scanf("%d%d%d",&in,&x,&y);
		for(int j = 1;j <= in;j++) scanf("%d",&z),ins(i + n,z,INF),ins(z,i + (n << 1),INF);
		ins(S,i + n,x),ins(i + (n << 1),T,y);
		sum += x + y;
	}

	printf("%d\n",sum - dinic());
	
	return 0;
}
