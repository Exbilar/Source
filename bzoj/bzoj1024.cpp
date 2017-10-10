#include <cstdio>
#include <algorithm>
using namespace std;

int n;
double x,y;

double dfs(double x,double y,int d){
    double ans=111111111.1;
    if(d==1)return (x<y?y/x:x/y);
    for(int i=1;i<=d/2;i++){
        double ans1=max(dfs(x/d*i,y,i),dfs(x-x/d*i,y,d-i));
	double ans2=max(dfs(x,y/d*i,i),dfs(x,y-y/d*i,d-i));
	ans=min(ans,min(ans1,ans2));
    }
    return ans;
}

int main(){
    scanf("%lf%lf%d",&x,&y,&n);
    printf("%lf\n",dfs(x,y,n));
	
    return 0;
}
