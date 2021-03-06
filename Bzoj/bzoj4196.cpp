#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int nxt[maxm],to[maxm],fst[maxm];
int top[maxm],dpt[maxm],ftr[maxm],pos[maxm],son[maxm],fnl[maxm],size[maxm];
int tr[maxm],lft[maxm],rgt[maxm],lz[maxm];
char ch[10];
int cnt,sz,n,m;

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
		if(size[v]>size[son[x]])son[x]=v;
    }
}

void dfs2(int x,int chain){
    pos[x]=++sz;top[x]=chain;
    if(son[x])dfs2(son[x],chain);
    for(int u=fst[x];u;u=nxt[u]){
		int v=to[u];
		if(dpt[v]>dpt[x]&&v!=son[x])dfs2(v,v);
    }
    fnl[x]=sz;
}

void build(int id,int l,int r){
    lft[id]=l;rgt[id]=r;lz[id]=-1;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(id<<1,l,mid);
    build(id<<1|1,mid+1,r);
}

void pushdown(int id){
    int l=lft[id];int r=rgt[id];int mid=(l+r)>>1;
    lz[id<<1]=lz[id];
    lz[id<<1|1]=lz[id];
    tr[id<<1]=(mid-l+1)*lz[id];
    tr[id<<1|1]=(r-mid)*lz[id];
    lz[id]=-1;
}

void modify(int id,int l,int r,int C){
    if(lft[id]>=l&&rgt[id]<=r){
		lz[id]=C;
		tr[id]=(rgt[id]-lft[id]+1)*C;
		return;
    }
    if(lft[id]>r||rgt[id]<l)return;
    if(lz[id]!=-1)pushdown(id);
    modify(id<<1,l,r,C);
    modify(id<<1|1,l,r,C);
    tr[id]=tr[id<<1]+tr[id<<1|1];
}

int Query(int id,int l,int r){
    if(lft[id]>=l&&rgt[id]<=r)return tr[id];
    if(lft[id]>r||rgt[id]<l)return 0;
    if(lz[id]!=-1)pushdown(id);
    return (Query(id<<1,l,r)+Query(id<<1|1,l,r));
}

int update(int x,int y){
    int sum=0,d=dpt[y]+1;
    while(top[x]!=top[y]){
		if(dpt[top[x]]<dpt[top[y]])swap(x,y);
		sum+=Query(1,pos[top[x]],pos[x]);
		modify(1,pos[top[x]],pos[x],1);
		x=ftr[top[x]];
    }
    if(pos[x]>pos[y])swap(x,y);
    sum+=Query(1,pos[x],pos[y]);
    modify(1,pos[top[y]],pos[y],1);
    return d-sum;
}

int main(){
    int x,y;

    scanf("%d",&n);

    for(int i=2;i<=n;i++)scanf("%d",&x),ins(i,x+1),ins(x+1,i);
    scanf("%d",&m);

    dfs1(1);
    dfs2(1,1);
    build(1,1,n);

    while(m--){
		scanf("%s%d",ch,&x);x++;
		if(ch[0]=='i'){
			printf("%d\n",update(1,x));
		}else if(ch[0]=='u'){
			printf("%d\n",Query(1,pos[x],fnl[x]));
			modify(1,pos[x],fnl[x],0);
		}
    }
    
    return 0;
}
