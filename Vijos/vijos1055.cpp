#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

struct point{
    int x,y;
}pt[maxm];

int n,l,w,ans=-1;

bool cmp1(const point& A,const point &B){
    return A.x==B.x?A.y<B.y:A.x<B.x;
}

bool cmp2(const point &A,const point &B){
    return A.y==B.y?A.x<B.x:A.y<B.y;
}

int main(){
    scanf("%d%d%d",&l,&w,&n);
    if(!n)return printf("%d\n",l*w),0;
    for(int i=1;i<=n;i++)scanf("%d%d",&pt[i].x,&pt[i].y);

    sort(pt+1,pt+n+1,cmp1);
    
    for(int i=1;i<=n;i++){
		int u=w;int d=0;
		for(int j=i+1;j<=n;j++){
			ans=max(ans,(u-d)*(pt[j].x-pt[i].x));
			if(pt[j].y>=pt[i].y)u=min(u,pt[j].y);
			if(pt[j].y<=pt[i].y)d=max(d,pt[j].y);
		}
		ans=max(ans,(l-pt[i].x)*(u-d));
    }

    for(int i=n;i>=1;i--){
		int u=w;int d=0;
		for(int j=i-1;j>=1;j--){
			ans=max(ans,(u-d)*(pt[i].x-pt[j].x));
			if(pt[j].y>=pt[i].y)u=min(u,pt[j].y);
			if(pt[j].y<=pt[i].y)d=max(d,pt[j].y);
		}
		ans=max(ans,pt[i].x*(u-d));
    }

    sort(pt+1,pt+n+1,cmp2);

    for(int i=1;i<n;i++)
		ans=max(ans,l*(pt[i+1].y-pt[i].y));
    
    printf("%d\n",ans);
    
    return 0;
}
