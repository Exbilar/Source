#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

static const int maxm=1e4+10;
static const int size=1e2+10;
static const int INF=~(1<<31);

struct Cls{
	int M,L,A;
	bool operator < (const Cls &c) const {
		return M<c.M;
	}
}cls[maxm];

struct Board{
	int C,D;
	bool operator < (const Board &b) const {
		return C<b.C;
	}
}brd[maxm];

int f[maxm][size],nd[maxm],g[maxm],ls[maxm][size];
int T,S,N;

int main(){
	memset(f,128,sizeof f);
	memset(nd,127/3,sizeof nd);
	scanf("%d%d%d",&T,&S,&N);
	
	for(int i=1;i<=S;i++){
		scanf("%d%d%d",&cls[i].M,&cls[i].L,&cls[i].A);
		ls[cls[i].M+cls[i].L][cls[i].A]=max(ls[cls[i].M+cls[i].L][cls[i].A],cls[i].M);
	}
	for(int i=1;i<=N;i++){
		scanf("%d%d",&brd[i].C,&brd[i].D);
		for(int j=brd[i].C;j<=100;j++)
			nd[j]=min(nd[j],brd[i].D);
	}
	f[0][1]=0;g[0]=0;
	for(int i=1;i<=T;i++){
		for(int j=1;j<=100;j++){
			f[i][j]=max(f[i-1][j],f[i][j]);
			if(ls[i][j])f[i][j]=max(f[i][j],g[ls[i][j]]);
			if(i>=nd[j])f[i][j]=max(f[i][j],f[i-nd[j]][j]+1);
			g[i]=max(g[i],f[i][j]);
		}
	}
	
	printf("%d\n",g[T]);

	return 0;
}
