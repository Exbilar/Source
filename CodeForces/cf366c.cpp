#include <cstdio>
#include <cstring>
#include <algorithm>

using std :: max;
using std :: min;

static const int maxm = 2e5 + 10;

int f[200][maxm],A[maxm],B[maxm],w[maxm],c[maxm];
int n,m,k;

int main(){
	
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	for(int i = 1;i <= n;i++) scanf("%d",&B[i]);

	for(int i = 1;i <= n;i++) w[i] = A[i] - k * B[i],c[i] = A[i];
	
	m = n * 1000;

	memset(f,-0x3f,sizeof f); f[0][m] = 0;
	
	for(int i = 1;i <= n;i++){
		for(int v = m + m;v >= w[i];v--){
			f[i][v] = max(f[i - 1][v],f[i - 1][v - w[i]] + c[i]);
		}
	}
	
	if(f[n][m] <= 0) return puts("-1"),0;
	printf("%d\n",f[n][m]);
	
	return 0;
}
