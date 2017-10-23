#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int cap[maxm],cur[maxm],fst[maxm],nxt[maxm],to[maxm],dpt[maxm],que[maxm],r[maxm],c[maxm];
int cnt = 1,S,T,n,m,sum;

void addedge(int f,int t,int v){
	nxt[++cnt] = fst[f],cap[cnt] = v,to[cnt] = t,fst[f] = cnt;
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
	int flow = 0,res = 0;
	while(bfs()){
		memcpy(cur,fst,sizeof cur);
		while(flow = dfs(S,INF)) res += flow;
	}
	return res;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&r[i]),sum += r[i];
	for(int i = 1;i <= m;i++) scanf("%d",&c[i]);

	S = n + m + 1,T = n + m + 2;

	for(int i = 1;i <= n;i++) ins(S,i,r[i]);
	for(int i = 1;i <= m;i++) ins(i + n,T,c[i]);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++) ins(i,j + n,1);

	if(dinic() != sum) return puts("0"),0;
	puts("1");
	for(int i = 1;i <= n;i++){
		for(int u = fst[i];u;u = nxt[u])
			if(!cap[u]) printf("%d ",to[u] - n);
		putchar(10);
	}
	
	return 0;
}
