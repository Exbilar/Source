#include <bits/stdc++.h>

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int fst[maxm << 3],nxt[maxm << 3],to[maxm << 3],cap[maxm << 3];
int dpt[maxm << 3],cur[maxm],que[maxm * 10];
int cnt = 1,s,t,n,m,head,tail;

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,fst[t] = cnt;
}

bool bfs(){
	memset(dpt,0,sizeof dpt);
	dpt[s] = 1;
	head = 1,tail = 0;
	que[++tail] = s;

	while(head <= tail){
		int x = que[head++];
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(!dpt[v] && cap[u]){
				dpt[que[++tail] = v] = dpt[x] + 1;
				if(v == t) return true;
			}
		}
	}
	return false;
}

int dfs(int x,int flw){
	int res = 0;
	if(x == t || !flw) return flw;
	for(int &u = cur[x];u;u = nxt[u]){
		int v = to[u];
		if(dpt[v] == dpt[x] + 1 && cap[u]){
			res = dfs(v,std :: min(flw,cap[u]));
			if(res) return cap[u] -= res,cap[u ^ 1] += res,res;
		}
	}
	return 0;
}

LL dinic(){
	LL res = 0,flow = 0;
	while(bfs()){
		memcpy(cur,fst,sizeof cur);
		while(flow = dfs(s,INF)) res += flow;
	}
	return res;
}

int main(){
	int x,y,z;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i = 1;i <= m;i++) scanf("%d%d%d",&x,&y,&z),ins(x,y,z);

	printf("%lld\n",dinic());

	return 0;
}
