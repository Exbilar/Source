#include <bits/stdc++.h>
using namespace std;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

int fst[maxm],nxt[maxm],to[maxm],cur[maxm],cap[maxm],que[maxm],dpt[maxm];
int rt[maxm],lc[maxm],rc[maxm];
int n,m,S,T,sz = 2,cnt = 1;

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,cap[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,cap[cnt] = 0,fst[t] = cnt;
}

namespace maxFlow{
	
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
				int res = dfs(v,min(cap[u],flow));
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
	
}

namespace SMT{

	void insert(int &x,int l,int r,int pos){
		x = ++sz;
		if(l == r) return ins(x,T,1),void();
		int mid = (l + r) >> 1;
		if(pos <= mid) insert(lc[x],l,mid,pos),ins(x,lc[x],INF);
		else insert(rc[x],mid + 1,r,pos),ins(x,rc[x],INF);
	}

	int merge(int x,int y,int l,int r){
		if(!x || !y) return x ^ y;
		int z = ++sz;
		if(l == r) return ins(z,x,INF),ins(z,y,INF),z;
		int mid = (l + r) >> 1;
		lc[z] = merge(lc[x],lc[y],l,mid);
		if(lc[z]) ins(z,lc[z],INF);
		rc[z] = merge(rc[x],rc[y],mid + 1,r);
		if(rc[z]) ins(z,rc[z],INF);
		return z;
	}

	void Qry(int x,int l,int r,int L,int R,int pos){
		if(!x) return ;
		if(l >= L && r <= R) return ins(pos,x,INF),void();
		int mid = (l + r) >> 1;
		if(L <= mid) Qry(lc[x],l,mid,L,R,pos);
		if(R > mid) Qry(rc[x],mid + 1,r,L,R,pos);
	}
	
}

vector<int> son[maxm];

void dfs(int x){
	for(int i = 0;i < son[x].size();i++){
		dfs(son[x][i]);
		rt[x] = SMT :: merge(rt[x],rt[son[x][i]],1,n);
	}
}

int main(){
	int x,L,R,D,T;
	scanf("%d%d",&n,&m);
	for(int i = 2;i <= n;i++) scanf("%d",&x),son[x].push_back(i);

	S = 1,T = 2;
	for(int i = 1;i <= n;i++) scanf("%d",&x),SMT :: insert(rt[i],1,n,x);

	dfs(1);
	
	for(int i = 1;i <= m;i++){
		scanf("%d%d%d%d",&L,&R,&D,&T);
		ins(S,++sz,T),SMT :: Qry(rt[D],1,n,L,R,sz);
	}

	printf("%d\n",maxFlow :: dinic());

	return 0;
}
