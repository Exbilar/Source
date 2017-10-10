#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int f[maxm][2],nxt[maxm],fst[maxm],to[maxm],r[maxm],staff[maxm];
int cnt,n,a,b;

void ins(int f,int t){
    nxt[++cnt]=fst[f];
    fst[f]=cnt;
    to[cnt]=t;
}

void dfs(int x){
    for(int u=fst[x];u;u=nxt[u]){
	int v=to[u];
	dfs(v);
	f[x][0]+=max(f[v][1],f[v][0]);
	f[x][1]+=f[v][0];
    }
    f[x][1]+=r[x];
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&r[i]);
    for(int i=1;i<n;i++){
	int u,v;
	scanf("%d%d",&u,&v);
	ins(v,u);staff[u]=1;
    }
    scanf("%d%d",&a,&b);
    for(int i=1;i<=n;i++){
	if(!staff[i]){
	    dfs(i);
	    printf("%d\n",max(f[i][1],f[i][0]));
	    return 0;
	}
    }
    
    return 0;
}
