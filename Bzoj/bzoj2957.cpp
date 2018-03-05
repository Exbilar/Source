#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int tr[maxm],lft[maxm],rht[maxm];
double maxl[maxm];
int n,m;

void build(int id,int l,int r){
    lft[id]=l;rht[id]=r;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(id<<1,l,mid);
    build(id<<1|1,mid+1,r);
}

int calc(int id,int l,int r,double v){
    int mid=(l+r)>>1;
    if(l==r)return maxl[id]>v;
    if(maxl[id]<=v)return 0;
    if(maxl[id<<1]<=v)return calc(id<<1|1,mid+1,r,v);
    else return calc(id<<1,l,mid,v)+tr[id]-tr[id<<1];
}

void modify(int id,int pos,double v){
    if(lft[id]==rht[id]){
	tr[id]=1;
	maxl[id]=v;
	return;
    }
    int l=lft[id];int r=rht[id];int mid=(l+r)>>1;
    if(pos<=mid)modify(id<<1,pos,v);
    else modify(id<<1|1,pos,v);
    tr[id]=tr[id<<1]+calc(id<<1|1,mid+1,r,maxl[id<<1]);
    maxl[id]=max(maxl[id<<1],maxl[id<<1|1]);
}

int main(){
    int x,y;
    scanf("%d%d",&n,&m);
    build(1,1,n);
	
    while(m--){
	scanf("%d%d",&x,&y);
	double l=(double)y/(double)x;
	modify(1,x,l);
	printf("%d\n",tr[1]);
    }

    return 0;
}
