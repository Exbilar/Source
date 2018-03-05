#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 2e5 + 10;
static const int maxn = 1e6 + 10;
static const int INF = 1 << 30;

int lc[maxn],rc[maxn],rt[maxn],dpt[maxm],que[maxm],A[maxm],B[maxm],W[maxm];
int fst[maxm],cur[maxn],nxt[maxn],to[maxn],cap[maxn],_l[maxm],_r[maxm],p[maxm],tmp[maxm];
int sz,ans,cnt = 1,n,m,S,T;

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
			int res = dfs(v,std :: min(cap[u],flow));
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

void insert(int &x,int lst,int l,int r,int pos,int id){
	x = ++sz,lc[x] = lc[lst],rc[x] = rc[lst];
	if(l == r){
		ins((n << 1) + x,id,INF);
		if(lst) ins((n << 1) + x,(n << 1) + lst,INF);
		return ;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) insert(lc[x],lc[lst],l,mid,pos,id);
	else insert(rc[x],rc[lst],mid + 1,r,pos,id);
	if(lc[x]) ins((n << 1) + x,(n << 1) + lc[x],INF);
	if(rc[x]) ins((n << 1) + x,(n << 1) + rc[x],INF);
}

void Qry(int x,int l,int r,int L,int R,int id){
	if(!x) return ;
	if(l >= L && r <= R) return ins(id,(n << 1) + x,INF),void();
	int mid = (l + r) >> 1;
	if(L <= mid) Qry(lc[x],l,mid,L,R,id);
	if(R > mid) Qry(rc[x],mid + 1,r,L,R,id);
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) 
		scanf("%d%d%d%d%d%d",&A[i],&B[i],&W[i],&_l[i],&_r[i],&p[i]),ans += W[i] + B[i];

	int tot = 0;
	for(int i = 1;i <= n;i++)
		tmp[++tot] = A[i],tmp[++tot] = _l[i],tmp[++tot] = _r[i];

	std :: sort(tmp + 1,tmp + tot + 1);
	tot = std :: unique(tmp + 1,tmp + tot + 1) - tmp - 1;

	for(int i = 1;i <= n;i++)
		A[i] = std :: lower_bound(tmp + 1,tmp + tot + 1,A[i]) - tmp,
			_l[i] = std :: lower_bound(tmp + 1,tmp + tot + 1,_l[i]) - tmp,
			_r[i] = std :: lower_bound(tmp + 1,tmp + tot + 1,_r[i]) - tmp;

	for(int i = 1;i <= n;i++){
		insert(rt[i],rt[i - 1],1,tot,A[i],i);
		Qry(rt[i - 1],1,tot,_l[i],_r[i],i + n);
	}

	S = (n << 1) + sz + 1,T = S + 1;

	for(int i = 1;i <= n;i++) ins(S,i,B[i]),ins(i,T,W[i]),ins(i,i + n,p[i]);

	printf("%d\n",ans - dinic());
	
	return 0;
}
