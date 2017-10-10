#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 3e3 + 10;
static const int INF = 1 << 30;

int cap[maxm],cur[maxm],fst[maxm],nxt[maxm],to[maxm],dpt[maxm],que[maxm];
char str[maxm][maxm];
int cnt = 1,n,m,S,T,a1,a2,b1,b2,an,bn;

void ins(int f,int t,int v1,int v2){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v1,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = v2,fst[t] = cnt;
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
			if(cap[u] && !dpt[v]){
				dpt[que[++tail] = v] = dpt[x] + 1;
				if(v == T) return true;
			}
		}
	}
	return false;
}

int dfs(int x,int flow){
	int res = 0;
	if(x == T || !flow) return flow;
	for(int &u = cur[x];u;u = nxt[u]){
		int v = to[u];
		if(dpt[v] == dpt[x] + 1 && cap[u]){
			res = dfs(v,std :: min(flow,cap[u]));
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

void build(){
	memset(fst,0,sizeof fst);
	cnt = 1;
	for(int i = 1;i < n;i++){
		for(int j = i + 1;j <= n;j++){
			if(str[i][j] == 'O') ins(i,j,2,2);
			else if(str[i][j] == 'N') ins(i,j,INF,INF);
		}
	}
}

int main(){
	while(scanf("%d%d%d%d%d%d%d",&n,&a1,&a2,&an,&b1,&b2,&bn) != EOF){
		a1++,a2++,b1++,b2++,an <<= 1,bn <<= 1;
		for(int i = 1;i <= n;i++) scanf("%s",str[i] + 1);
		S = n + 1,T = n + 2;
		
		build();
		ins(S,a1,an,0),ins(S,b1,bn,0);
		ins(a2,T,an,0),ins(b2,T,bn,T);
		if(dinic() != an + bn){puts("No");continue;}
		
		build();
		ins(S,a1,an,0),ins(S,b2,bn,0);
		ins(a2,T,an,0),ins(b1,T,bn,T);
		if(dinic() != an + bn){puts("No");continue;}
		
		puts("Yes");
	}



	return 0;
}
