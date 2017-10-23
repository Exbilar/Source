#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)

using std :: max;
using std :: min;
using std :: set;
using std :: pair;
using std :: make_pair;
using std :: vector;
using std :: queue;
using std :: multiset;
using std :: priority_queue;

typedef long long LL;
typedef pair<int,int> pii;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

template <class T> void read(T &in){
	in = 0; int f = 1 ;char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

template <class T> inline bool chkmax(T &x,T y){
	return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
	return x > y ? x = y,true : false;
}

int fst[maxm],nxt[maxm],to[maxm],val[maxm],pre[maxm],dis[maxm];
int dpt[maxm],size[maxm],ftr[maxm],son[maxm],top[maxm],pos[maxm];
int tmp[maxm];
int n,m,cnt,sz;

struct asd{
	int x,y,v,lca;
}A[maxm];

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,val[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,val[cnt] = v,fst[t] = cnt;
}

void dfs1(int x){
	size[x] = 1;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == ftr[x]) continue;
		ftr[v] = x,dpt[v] = dpt[x] + 1;
		dis[v] = dis[x] + val[u],pre[v] = val[u];
		dfs1(v);
		size[x] += size[v];
		if(size[son[x]] < size[v]) son[x] = v;
	}
}

void dfs2(int x,int chain){
	pos[++sz] = x,top[x] = chain;
	if(son[x]) dfs2(son[x],chain);
	for(int u = fst[x];u;u = nxt[u])
		if(to[u] != son[x] && to[u] != ftr[x]) dfs2(to[u],to[u]);
}

int LCA(int x,int y){
	while(top[x] != top[y]){
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		x = ftr[top[x]];
	}
	return dpt[x] < dpt[y] ? x : y;
}

bool chk(int x){
	memset(tmp,0,sizeof tmp); int num = 0,_dis = 0;
	for(int i = 1;i <= m;i++){
		if(A[i].v > x){
			tmp[A[i].x]++,tmp[A[i].y]++;
			tmp[A[i].lca] -= 2;
			chkmax(_dis,A[i].v - x);
			num++;
		}
	}
	
	if(!num) return true;
	
	for(int i = n;i >= 2;i--)
		tmp[ftr[pos[i]]] += tmp[pos[i]];
	
	for(int i = 2;i <= n;i++)
		if(pre[i] >= _dis && tmp[i] == num) return true;
	
	return false;
}

int main(){
	
	int u,v,w,l = 0,r = 0;
	read(n),read(m);
	for(int i = 1;i < n;i++)
		read(u),read(v),read(w),ins(u,v,w),r += w;
	
	dfs1(1),dfs2(1,1);
	
	for(int i = 1;i <= m;i++){
		read(A[i].x),read(A[i].y);
		A[i].lca = LCA(A[i].x,A[i].y);
		A[i].v = dis[A[i].x] + dis[A[i].y] - dis[A[i].lca] - dis[A[i].lca];
	}
	
	int ans = -1;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(chk(mid)) ans = mid,r = mid - 1;
		else l = mid + 1;
	}
	
	printf("%d\n",ans);   
	
	return 0;
}
