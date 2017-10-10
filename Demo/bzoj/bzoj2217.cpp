#include <cstdio>
#include <algorithm>

static const int maxm = 2e6 + 10;

int ext[maxm],pos[maxm],lx[maxm],rx[maxm];
char str[maxm];
int n,m,k,sum;

int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",str + 1);
	for(int i = 1;i <= n;i++)
		if(str[i] == 'T') pos[i] = 2;
		else pos[i] = 1;

	for(int i = n;i;i--){
		ext[i] = ext[i + 1] + 1;
		if(pos[i] == 1) ext[i] = 0;
	}
	
	for(int i = 1;i <= n;i++){
		sum += pos[i];
		lx[sum] = 1,rx[sum] = i;
		if(pos[i] == 2){
			if(ext[1] < ext[i])
				lx[sum - 1] = 1 + ext[1] + 1,rx[sum - 1] = i + ext[1];
			else if(i + ext[i] != n + 1)
				lx[sum - 1] = 1 + ext[i],rx[sum - 1] = ext[i] + i;
		}
	}
	
	for(int i = 1;i <= m;i++){
		scanf("%d",&k);
		if(sum < k || !lx[k]) puts("NIE");
		else printf("%d %d\n",lx[k],rx[k]);
	}

	return 0;
}
