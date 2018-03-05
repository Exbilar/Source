#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

char str[maxm];
double f[maxm],l[maxm];
int n;

int main(){
	scanf("%d",&n);
	scanf("%s",str + 1);
	
	for(int i = 1;i <= n;i++){
		if(str[i] == 'x') f[i] = f[i - 1],l[i] = 0;
		else if(str[i] == 'o'){
			l[i] = l[i - 1] + 1;
			f[i] = f[i - 1] + l[i - 1] * 2 + 1;
		}
		else{
			l[i] = (l[i - 1] + 1) / 2;			
			f[i] = f[i - 1] + (l[i - 1] * 2 + 1) / 2;
		}
	}

	printf("%.4lf\n",f[n]);
	
	return 0;
}
