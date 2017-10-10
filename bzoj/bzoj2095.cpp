#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 2e5 + 10;
static const int INF = 1 << 30;

int fst[maxm],cur[maxm],nxt[maxm],to[maxm],cap[maxm];
int dpt[maxm],que[maxm],Ex[maxm],Ey[maxm],Ez1[maxm],Ez2[maxm],in[maxm],out[maxm];
int n,m,S,T,cnt = 1;

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
	int res = 0,flow = 0;
	while(bfs()){
		memcpy(cur,fst,sizeof cur);
		while(flow = dfs(S,INF)) res += flow;
	}
	return res;
}

bool chk(int x){
	memset(in,0,sizeof in);
	memset(out,0,sizeof out);
	memset(fst,0,sizeof fst),cnt = 1;

	int sum = 0;
	for(int i = 1;i <= m;i++){
		if(Ez1[i] <= x) out[Ex[i]]++,in[Ey[i]]++;
		if(Ez2[i] <= x) ins(Ey[i],Ex[i],1);
	}

	for(int i = 1;i <= n;i++)
		if(abs(in[i] - out[i]) & 1) return false;

	for(int i = 1;i <= n;i++){
		int x = (in[i] - out[i]) >> 1;
		if(x > 0) ins(S,i,x),sum += x;
		if(x < 0) ins(i,T,-x);
	}
	
	return dinic() == sum;
}

int main(){
	
	int l = INF,r = -INF,ans = 0;
	scanf("%d%d",&n,&m); S = n + 1,T = S + 1;
	for(int i = 1;i <= m;i++){
		scanf("%d%d%d%d",&Ex[i],&Ey[i],&Ez1[i],&Ez2[i]);
		if(Ez1[i] > Ez2[i]) std :: swap(Ez1[i],Ez2[i]),std :: swap(Ex[i],Ey[i]);
		l = std :: min(l,Ez1[i]),r = std :: max(r,Ez2[i]);
	}
	
	while(l <= r){
		int mid = (l + r) >> 1;
		if(chk(mid)) ans = mid,r = mid - 1;
		else l = mid + 1;
	}

	if(!ans) return puts("NIE"),0;
	printf("%d\n",ans);
	
	return 0;
}
