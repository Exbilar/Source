#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

static const int maxm=1e6+10;
static const int INF=~(1<<31);

int nxt[maxm],to[maxm],fst[maxm],val[maxm];
int dpt[maxm],ftr[maxm],size[maxm],top[maxm],pos[maxm];
int lft[maxm],rgt[maxm],sum[maxm],mx[maxm];
char ch[10];
int n,q,sz,cnt;

void ins(int f,int t){
    nxt[++cnt]=fst[f];
    fst[f]=cnt;
    to[cnt]=t;
}

void dfs1(int x){
    size[x]=1;
    for(int u=fst[x];u;u=nxt[u]){
	int v=to[u];
	if(v==ftr[x])continue;
	dpt[v]=dpt[x]+1;
	ftr[v]=x;
	dfs1(v);
	size[x]+=size[v];
    }
}

void dfs2(int x,int chain){
    pos[x]=++sz;top[x]=chain;int k=0;
    for(int u=fst[x];u;u=nxt[u]){
	int v=to[u];
	if(dpt[v]>dpt[x]&&size[v]>size[k])k=v;
    }
    if(!k)return;
    dfs2(k,chain);
    for(int u=fst[x];u;u=nxt[u]){
	int v=to[u];
	if(dpt[v]>dpt[x]&&v!=k)dfs2(v,v);
    }
}

void build(int id,int l,int r){
    lft[id]=l;rgt[id]=r;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(id<<1,l,mid);
    build(id<<1|1,mid+1,r);
}

void modify(int id,int x,int y){
    if(lft[id]==rgt[id]&&lft[id]==x){mx[id]=sum[id]=y;return;}
    if(lft[id]>x||rgt[id]<x)return;
    modify(id<<1,x,y);
    modify(id<<1|1,x,y);
    sum[id]=sum[id<<1]+sum[id<<1|1];
    mx[id]=max(mx[id<<1],mx[id<<1|1]);
}

int Querysum(int id,int l,int r){
    if(lft[id]>=l&&rgt[id]<=r)return sum[id];
    if(lft[id]>r||rgt[id]<l)return 0;
    return (Querysum(id<<1,l,r)+Querysum(id<<1|1,l,r));
}

int Querymax(int id,int l,int r){
    if(lft[id]>=l&&rgt[id]<=r)return mx[id];
    if(lft[id]>r||rgt[id]<l)return -INF;
    return max(Querymax(id<<1,l,r),Querymax(id<<1|1,l,r));
}

int solvesum(int x,int y){
    int sum=0;
    while(top[x]!=top[y]){
	if(dpt[top[x]]<dpt[top[y]])swap(x,y);
	sum+=Querysum(1,pos[top[x]],pos[x]);
	x=ftr[top[x]];
    }
    if(pos[x]>pos[y])swap(x,y);
    sum+=Querysum(1,pos[x],pos[y]);
    return sum;
}

int solvemax(int x,int y){
    int MAX=-INF;
    while(top[x]!=top[y]){
	if(dpt[top[x]]<dpt[top[y]])swap(x,y);
	MAX=max(MAX,Querymax(1,pos[top[x]],pos[x]));
	x=ftr[top[x]];
    }
    if(pos[x]>pos[y])swap(x,y);
    MAX=max(MAX,Querymax(1,pos[x],pos[y]));
    return MAX;
}

void init(){
    int u,v;
    scanf("%d",&n);
    for(int i=1;i<n;i++)scanf("%d%d",&u,&v),ins(u,v),ins(v,u);
    for(int i=1;i<=n;i++)scanf("%d",&val[i]);
}

void solve(){
    int x,y;
    build(1,1,n);
    for(int i=1;i<=n;i++)modify(1,pos[i],val[i]);
    scanf("%d",&q);
    while(q--){
	scanf("%s%d%d",ch,&x,&y);
	if(ch[0]=='C')modify(1,pos[x],y);
	else{
	    if(ch[1]=='M')printf("%d\n",solvemax(x,y));
	    else printf("%d\n",solvesum(x,y));
	}
    }
}

int main(){
    init();
    dfs1(1);
    dfs2(1,1);
    solve();

    return 0;
}
