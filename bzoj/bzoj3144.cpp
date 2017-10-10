#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int maxn = 1e2 + 10;
static const int INF = 1 << 30;

int cap[maxm],nxt[maxm],fst[maxm],cur[maxm],to[maxm];
int dpt[maxm],que[maxm],mtx[maxn][maxn][maxn],idx[maxn][maxn][maxn];
int n,m,S,T,cnt = 1,P,Q,R,D,ID;

int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

template<class T> void read(T &in){
	in = 0; int f = 1; char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

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

int main(){
	read(P),read(Q),read(R),read(D);
	
	for(int z = 1;z <= R;z++)
		for(int i = 1;i <= P;i++)
			for(int j = 1;j <= Q;j++) read(mtx[i][j][z]),idx[i][j][z] = ++ID;

	S = ID + 1,T = S + 1;

	for(int i = 1;i <= P;i++)
		for(int j = 1;j <= Q;j++) ins(S,idx[i][j][1],INF),ins(idx[i][j][R + 1],T,INF);

	for(int z = 1;z <= R;z++)
		for(int i = 1;i <= P;i++)
			for(int j = 1;j <= Q;j++)
				ins(idx[i][j][z],idx[i][j][z + 1],mtx[i][j][z]);
	
	for(int z = D + 1;z <= R;z++){
		for(int i = 1;i <= P;i++){
			for(int j = 1;j <= Q;j++){
				for(int dir = 0;dir < 4;dir++){
					int nx = i + dx[dir],ny = j + dy[dir];
					if(nx < 1 || nx > P || ny < 1 || ny > Q) continue;
					ins(idx[i][j][z],idx[nx][ny][z - D],INF);
				}
			}
		}
	}

	printf("%d\n",dinic());
	
	return 0;
}
