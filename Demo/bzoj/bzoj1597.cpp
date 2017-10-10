#include <cstdio>
#include <algorithm>

using std:: max;
using std:: min;

typedef long long LL;

static const int maxm=1e6+10;

struct mtx{
	LL x,y;
	bool operator < (const mtx &m) const {
		return x==m.x?y<m.y:x<m.x;
	}
}A[maxm];

LL Q[maxm],xx[maxm],yy[maxm],f[maxm];
int cnt,n,head=1,tail=1;

double slp(int j,int k){
	return (double)(f[k]-f[j])/(yy[j+1]-yy[k+1]);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&A[i].x,&A[i].y);
	
	std::sort(A+1,A+n+1);
	
	for(int i=1;i<=n;i++){
		while(cnt&&yy[cnt]<=A[i].y)cnt--;
		yy[++cnt]=A[i].y;xx[cnt]=A[i].x;
	}
	
	for(int i=1;i<=cnt;i++){
        while(head<tail&&slp(Q[head+1],Q[head])<=xx[i])head++;
        f[i]=f[Q[head]]+yy[Q[head]+1]*xx[i];
        while(head<tail&&slp(i,Q[tail])<=slp(Q[tail],Q[tail-1]))tail--;
        Q[++tail]=i;
    }
	
	printf("%lld\n",f[cnt]);
	
	return 0;
}
