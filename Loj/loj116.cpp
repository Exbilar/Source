#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 2e5 + 10;
static const int INF = 1 << 30;

int fst[maxm],nxt[maxm],to[maxm],cap[maxm],cur[maxm];
int que[maxm],dpt[maxm];
int n,m,S,T,SS,TT,cnt = 1;

void ins(int f,int t,int v){
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
	int x,y,up,down,s,t,tot = 0;;
	scanf("%d%d%d%d",&n,&m,&s,&t); S = n + 1,T = n + 2;
	for(int i = 1;i <= m;i++){
		scanf("%d%d%d%d",&x,&y,&down,&up);
		ins(x,y,up - down);
		ins(S,y,down); ins(x,T,down);
		tot += down;
	}

	ins(t,s,INF);
	int sum = dinic();
	
	if(sum != tot) return puts("please go home to sleep"),0;
	
	S = s,T = t;

	printf("%d\n",dinic());
	
	return 0;
}
