#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int cap[maxm],fst[maxm],cur[maxm],nxt[maxm],to[maxm],old[maxm];
int que[maxm],dpt[maxm],Ex[maxm],Ey[maxm];
int n,m,k,S,T,cnt = 1;

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,old[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,old[cnt] = 0,fst[t] = cnt;
}

void _ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,old[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = v,old[cnt] = v,fst[t] = cnt;
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

bool chk(int x){
	memset(fst,0,sizeof fst),cnt = 1;
	ins(S,1,k);
	for(int i = 1;i <= x;i++) ins(i * n + n,T,INF);
	for(int i = 1;i <= m;i++)
		for(int j = 0;j <= x;j++) ins(j * n + Ex[i],j * n + n + Ey[i],1);
	return dinic() >= k;
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i <= m;i++) scanf("%d%d",&Ex[i],&Ey[i]);
	S = maxm - 10,T = S + 1;
	
	int l = 1,r = n,ans = -1;

	while(l <= r){
		int mid = (l + r) >> 1;
		if(chk(mid)) ans = mid,r = mid - 1;
		else l = mid + 1;
	}

	printf("%d\n",ans);
	
	return 0;
}
