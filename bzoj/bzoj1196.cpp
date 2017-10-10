#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

struct Edge{
    int x,y,val1,val2;
    bool operator < (const Edge &E)const{
		return val2<E.val2;
    }
}edge[maxm];

int val[maxm],ftr[maxm];
int n,m,k,ans;

int find(int x){
    return x==ftr[x]?x:ftr[x]=find(ftr[x]);
}

void unionn(int x,int y,int &d){
    x=find(x);y=find(y);
    if(x!=y)ftr[x]=y,d++;
}

bool check(int MAX){
    int cnt=0;int num=0;
    for(int i=1;i<=n;i++)ftr[i]=i;
    
    for(int i=1;i<m;i++)
	if(edge[i].val1<=MAX&&find(edge[i].x)!=find(edge[i].y))
	    unionn(edge[i].x,edge[i].y,num);
    
    if(num<k)return false;
    
    for(int i=1;i<m;i++)
	if(edge[i].val2<=MAX&&find(edge[i].x)!=find(edge[i].y))
	    unionn(edge[i].x,edge[i].y,num);
    
    if(num<n-1)return false;
    
    return true;
}

int main(){
    int l=1,r=20011025;
    scanf("%d%d%d",&n,&k,&m);
    for(int i=1;i<m;i++)
		scanf("%d%d%d%d",&edge[i].x,&edge[i].y,&edge[i].val1,&edge[i].val2);

    while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
    }

    printf("%d\n",ans);
    
    return 0;
}
