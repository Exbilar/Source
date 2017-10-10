#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

multiset<int>Set;

int fst[maxm],nxt[maxm],to[maxm],sum[maxm],val[maxm];
int S,cnt,n,x,y,ans;

void ins(int f,int t){
    nxt[++cnt]=fst[f];
    fst[f]=cnt;
    to[cnt]=t;
}

void dfs(int x){
    if(Set.find(sum[x]-S)!=Set.end())ans++;
    Set.insert(sum[x]);
    for(int u=fst[x];u;u=nxt[u]){
	int v=to[u];
	sum[v]=sum[x]+val[v];
	dfs(v);
    }
    Set.erase(Set.find(sum[x]));
}

int main(){
    scanf("%d%d",&n,&S);
    for(int i=1;i<=n;i++)scanf("%d",&val[i]);
    for(int i=1;i<n;i++)
	scanf("%d%d",&x,&y),ins(x,y);
    
    sum[1]=val[1];Set.insert(0);

    dfs(1);

    printf("%d\n",ans);
    
    return 0;
}
