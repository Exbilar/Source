#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int ftr[maxm<<1],fst[maxm<<1],nxt[maxm<<1],to[maxm<<1],P[maxm],ans[maxm],tr[maxm];
int cnt,n;

void ins(int f,int t){
	nxt[++cnt]=fst[f];
	fst[f]=cnt;
	to[cnt]=t;
}

int lowbit(int x){
	return x&-x;
}

void update(int val,int k){
	for(int i=k;i<=n;i+=lowbit(i))tr[i]+=val;
}

int Query(int k){
	int ret=0;
	for(int i=k;i;i-=lowbit(i))ret+=tr[i];
	return ret;
}

void dfs(int x,int ftr){
	ans[P[x]]=Query(P[x]);
	update(1,P[x]);
	for(int u=fst[x];u;u=nxt[u])
		if(to[u]!=ftr)dfs(to[u],x);
	update(-1,P[x]);
}

int main(){
	int u,v;
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		ins(u,v);ins(v,u);
	}
	
	for(int i=1;i<=n;i++){
		scanf("%d",&u);
		P[u]=i;
	}
	
	dfs(1,0);
	
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
	
	return 0;
}
