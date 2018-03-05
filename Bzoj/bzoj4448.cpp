#include <cstdio>
#include <algorithm>

static const int maxm = 2e6 + 10;

struct element{
	int x,y,z,f,id;
	bool operator < (const element &ele) const {
		return z == ele.z ? f > ele.f : z < ele.z;
	}
}ele[maxm];

int ftr[maxm],top[maxm],pos[maxm],size[maxm],son[maxm],dpt[maxm];
int nxt[maxm],to[maxm],fst[maxm],tr[maxm],ans1[maxm],ans2[maxm];
int cnt,sz,n,m,ask,rt;

void ins(int f,int t){
	if(!f || !t) return;
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
}

void dfs1(int x){
	size[x] = 1;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == ftr[x]) continue;
		ftr[v] = x,dpt[v] = dpt[x] + 1;
		dfs1(v);
		size[x] += size[v];
		if(size[son[x]] < size[v]) son[x] = v;
	}
}

void dfs2(int x,int chain){
	pos[x] = ++sz,top[x] = chain;
	if(son[x]) dfs2(son[x],chain);
	for(int u = fst[x];u;u = nxt[u])
		if(to[u] != son[x] && to[u] != ftr[x]) dfs2(to[u],to[u]);
}

int lowbit(int x){
	return x & -x;
}

void Upt(int k,int val){
	for(int i = k;i <= n;i += lowbit(i))
		tr[i] += val;
}

int Qry(int k){
	int ret = 0;
	for(int i = k;i;i -= lowbit(i))
		ret += tr[i];
	return ret;
}

int solve_Qry(int x,int y){
	int ret = 0;
	while(top[x] != top[y]){
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		ret += Qry(pos[x]),ret -= Qry(pos[top[x]] - 1);
		x = ftr[top[x]];
	}
	if(pos[x] > pos[y]) std :: swap(x,y);
	ret += Qry(pos[y]),ret -= Qry(pos[x] - 1);
	return ret;
}

int LCA(int x,int y){
	while(top[x] != top[y]){
		if(dpt[top[x]] < dpt[top[y]]) std :: swap(x,y);
		x = ftr[top[x]];
	}
	return dpt[x] < dpt[y] ? x : y;
}

int main(){
	int dx;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&dx);
		ins(dx,i),ins(i,dx);
	}
	
	scanf("%d",&m);

	for(int i = 1;i <= m;i++){
		scanf("%d",&ele[i].f);
		if(ele[i].f == 1){
			scanf("%d%d%d",&ele[i].x,&ele[i].y,&ele[i].z);
			ele[i].z = i - ele[i].z - 1;
		}
		if(ele[i].f == 2) scanf("%d",&ele[i].x),ele[i].z = i;
		ele[i].id = i;
	}

	std :: sort(ele + 1,ele + m + 1);
	dfs1(1),dfs2(1,1);
	
	for(int i = 1;i <= m;i++){
		if(ele[i].f == 1){
			int lca = LCA(ele[i].x,ele[i].y);
			ans1[ele[i].id] = dpt[ele[i].x] + dpt[ele[i].y] - 2 * dpt[lca] + 1;
			ans2[ele[i].id] = solve_Qry(ele[i].x,ele[i].y);
		}
		if(ele[i].f == 2) Upt(pos[ele[i].x],1);
	}

	for(int i = 1;i <= m;i++)
		if(ans1[i] || ans2[i]) printf("%d %d\n",ans1[i],ans2[i]);
	
	return 0;
}
