#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

struct Edge{
    int x,y,v,col;
    bool operator < (const Edge &E) const{
	return v==E.v?col<E.col:v<E.v;
    }
}edge[maxm];

int ftr[maxm],u[maxm],v[maxm],val[maxm],col[maxm];
int tot,ans,k,cnt,n,m,chk;

int find(int x){
    return x==ftr[x]?x:ftr[x]=find(ftr[x]);
}

bool Kruskal(int x){
    tot=0;cnt=0;chk=0;
    for(int i=1;i<=n;i++)ftr[i]=i;

    for(int i=1;i<=m;i++){
		edge[i].x=u[i];edge[i].y=v[i];edge[i].v=val[i];edge[i].col=col[i];
		if(!col[i])edge[i].v+=x;
    }

    sort(edge+1,edge+m+1);

    for(int i=1;i<=m;i++){
		int dx=find(edge[i].x);
		int dy=find(edge[i].y);
		if(dx!=dy){
	    	ftr[dx]=dy;
	    	tot+=edge[i].v;
	    	cnt++;
	    	if(!edge[i].col)chk++;
		}
		if(cnt==n-1)break;
    }
    
    if(chk<k)return false;
    return true;
}

int main(){
    scanf("%d%d%d",&n,&m,&k);

    for(int i=1;i<=m;i++)
	scanf("%d%d%d%d",&u[i],&v[i],&val[i],&col[i]),
	    u[i]++,v[i]++;

    int l=-11111,r=11111;

    while(l<=r){
		int mid=(l+r)>>1;
		if(Kruskal(mid))l=mid+1,ans=tot-k*mid;
		else r=mid-1;
    }

    printf("%d\n",ans);
    
    return 0;
}
