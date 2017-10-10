#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

static const int maxm = 3e3 + 10;
static const int maxn = 2e4 + 10;
static const LL INF = 1LL << 50;

int que[maxm],dpt[maxm],fst[maxn],idx[50][50];
int cur[maxn],to[maxn],nxt[maxn],col[50][50];
LL val[50][50],cap[maxn];
LL cnt = 1,n,m,S,T,WS,WN,BS,BN,ID,cas;

void ins(int f,int t,LL v1,LL v2){
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

LL dfs(int x,LL flow){
	LL res = 0;
	if(x == T || !flow) return flow;
	
	for(int &u = cur[x];u;u = nxt[u]){
		int v = to[u];
		if(cap[u] && dpt[v] == dpt[x] + 1){
			res = dfs(v,std :: min(flow,cap[u]));
			if(res) return cap[u] -= res,cap[u ^ 1] += res,res;
		}
	}

	return 0;
	
}

LL dinic(){
	LL res = 0,flow = 0;
	while(bfs()){
		memcpy(cur,fst,sizeof cur);
		while(flow = dfs(S,INF)) res += flow;
	}
	return res;
}

bool OK(int i,int j){
	return (i >= 1 && i <= n) && (j >= 1 && j <= m);
}

LL build(LL X){
	LL res = 0;
	S = n * m + 1,T = n * m + 2;
	memset(fst,0,sizeof fst),cnt = 1;
	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(col[i][j]){
				ins(S,idx[i][j],X - val[i][j],0);
				res += X - val[i][j];
				if(OK(i + 1,j)) ins(idx[i][j],idx[i + 1][j],INF,0);
				if(OK(i - 1,j)) ins(idx[i][j],idx[i - 1][j],INF,0);
				if(OK(i,j + 1)) ins(idx[i][j],idx[i][j + 1],INF,0);
				if(OK(i,j - 1)) ins(idx[i][j],idx[i][j - 1],INF,0);
			}
			else ins(idx[i][j],T,X - val[i][j],0);
		}
	}

	return res;
}

bool chk(LL X){
	LL tot = build(X);
	return dinic() == tot;
}

LL solve(){
	LL res = 0,smax = 0;
	WS = 0,WN = 0,BS = 0,BN = 0,ID = 0;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			col[i][j] = (i + j) & 1;
			smax = std :: max(smax,val[i][j]);
			if(col[i][j]) BN++,BS += val[i][j];
			else WN++,WS += val[i][j];
			idx[i][j] = ++ID;
		}
	}

	if(WN != BN){
		res = (BS - WS) / (BN - WN);
		if(res < smax) return -1;
		return chk(res) ? res * WN - WS : -1;
	}
	
	if(WS != BS) return -1;

	LL l = smax,r = INF;

	while(l <= r){
		LL mid = (l + r) >> 1;
		if(chk(mid)) res = mid,r = mid - 1;
		else l = mid + 1;
	}
	res = res * WN - WS;
	
	return res;
}

int main(){
	scanf("%lld",&cas);
	
	while(cas--){
		scanf("%lld%lld",&n,&m);
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= m;j++)
				scanf("%lld",&val[i][j]);
		printf("%lld\n",solve());
	}
	

	return 0;
}
