#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

map<int,int>mp;
int ftr[maxm],u[maxm],v[maxm],opt[maxm];
int T,n,cnt;

int find(int x){
    return x==ftr[x]?x:ftr[x]=find(ftr[x]);
}

void init(){
    mp.clear();cnt=0;
    for(int i=1;i<=n;i++)
	scanf("%d%d%d",&u[i],&v[i],&opt[i]);
    for(int i=1;i<=n;i++){
	if(!mp[u[i]])mp[u[i]]=++cnt;
	if(!mp[v[i]])mp[v[i]]=++cnt;
    }
    for(int i=1;i<=n;i++)u[i]=mp[u[i]],v[i]=mp[v[i]];
    for(int i=1;i<=cnt;i++)ftr[i]=i;
}

int main(){
    scanf("%d",&T);
    while(T--){
	scanf("%d",&n);
	init();int f=1;
	for(int i=1;i<=n;i++){
	    if(!opt[i])continue;
	    int x=find(u[i]);
	    int y=find(v[i]);
	    if(x!=y)ftr[x]=y;
	}
	for(int i=1;i<=n;i++){
	    if(opt[i])continue;
	    int x=find(u[i]);
	    int y=find(v[i]);
	    if(x==y){f=0;break;}
	}
	if(!f)puts("NO");
	else puts("YES");
    }

    return 0;
}
