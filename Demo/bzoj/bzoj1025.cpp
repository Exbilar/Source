#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm = 2e3 + 10;

int npr[maxm],prm[maxm],f[maxm][maxm];
int cnt,n,ans;

void init(){
	npr[1] = 1;
	for(int i = 2;i <= 1e3;i++){
		if(!npr[i]) prm[++cnt] = i;
		for(int j = 1;j <= cnt && prm[j] * i <= 1e3;j++){
			npr[prm[j] * i] = 1;
			if(i % prm[j] == 0) break;
		}
	}
}

int main(){
	scanf("%d",&n);
	init();
	f[0][0] = 1;	
	
	for(int i = 1;i <= cnt;i++){
		for(int j = 0;j <= n;j++){
			int k = prm[i];
			f[i][j] = f[i - 1][j];
			while(k <= j){
				f[i][j] += f[i - 1][j - k];
				k *= prm[i];
			}			
		}
	}
	
	for(int i = 0;i <= cnt;i++) ans += f[cnt][i];
	
	printf("%d\n",ans);

	return 0;
}
