#include <cstdio>

static const int maxm=1e6+10;

int stack[maxm],fst[maxm],nxt[maxm],to[maxm],root[maxm],bel[maxm];
int cnt,top,B,num,n;

void ins(int f,int t){
    nxt[++cnt]=fst[f];
    fst[f]=cnt;
    to[cnt]=t;
}

void dfs(int x,int ftr){
    int now=top;
    for(int u=fst[x];u;u=nxt[u]){
		int v=to[u];
		if(v==ftr)continue;
		dfs(v,x);
		if(top-now>=B)
	    	{root[++num]=x;while(top!=now)bel[stack[top--]]=num;}
    }
    stack[++top]=x;
}

int main(){
    scanf("%d%d",&n,&B);

    for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		ins(u,v);ins(v,u);
    }

    dfs(1,0);

    while(top)bel[stack[top--]]=num;

    printf("%d\n",num);
    for(int i=1;i<=n;i++)printf("%d ",bel[i]);puts("");
    for(int i=1;i<=num;i++)printf("%d ",root[i]);puts("");
    
    return 0;
}
