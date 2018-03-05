#include <cstdio>
#include <deque>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;
static const int INF=~(1<<31);

struct point{
	int x,col;
	bool operator < (const point &p) const {
		return x<p.x;
	}
}A[maxm];

deque<point>Q;

int color[maxm];
int n,m,num,cnt,cur,sum;
int ans=INF;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&num);int pos;
		for(int j=1;j<=num;j++){
			scanf("%d",&pos);
			A[++cnt].x=pos;A[cnt].col=i;
		}
	}
	
	sort(A+1,A+n+1);
	
	Q.push_front(A[1]);color[A[1].col]=1;sum=1;cur=1;
	
	while(!Q.empty()){
		if(sum==m)ans=min(ans,Q.back().x-Q.front().x);
		if(sum==m||cur==n){
			if(!--color[Q.front().col])sum--;
			Q.pop_front();
		}else{
			cur++;
			if(!color[A[cur].col])sum++;
			color[A[cur].col]++;
			Q.push_back(A[cur]);
		}
	}
	
	printf("%d\n",ans);
	
	return 0;
}
