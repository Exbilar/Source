#include <cstdio>
#include <algorithm>

static const int maxm = 2e6 + 10;

int nxt[maxm],fst[maxm],to[maxm],c[maxm],f[maxm];
int cnt,ans,n,m;

void ins(int f,int t){
    nxt[++cnt]=fst[f];
    to[cnt]=t;
    fst[f]=cnt;
}

void dfs(int x){
    for(int u = fst[x];u;u = nxt[u])dfs(to[u]);
    int num = 0;
    for(int u = fst[x];u;u = nxt[u])f[++num] = c[to[u]];
    std :: sort(f + 1,f + num + 1);
    for(int i = 1;i <= num;i++){
	if(c[x] + f[i] - 1 > m)break;
	c[x] += (f[i] - 1),ans++;
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++)scanf("%d",&c[i]);
    for(int i = 1;i <= n;i++){
	int num,x;scanf("%d",&num);
	for(int j = 1;j <= num;j++)scanf("%d",&x),ins(i,x + 1);
	c[i] += num;
    }

    dfs(1);

    printf("%d\n",ans);
    
    return 0;
}
