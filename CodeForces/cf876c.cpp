#include <bits/stdc++.h>

using std :: max;
using std :: min;

static const int maxm = 1e6 + 10;

int ans[maxm],tmp[maxm];
int n,cnt;

int calc(int x){
	int num = 0,res = 0;
	while(x){
		tmp[++num] = x % 10;
		x /= 10;
	}	   		   	
	
	for(int i = 1;i <= num;i++) res += tmp[i];	
	return res;
}

int main(){
	scanf("%d",&n);
	
	for(int i = max(1,n - 100);i <= n;i++){
		if(calc(i) + i == n) ans[++cnt] = i;
	}
	
	printf("%d\n",cnt);
	for(int i = 1;i <= cnt;i++) printf("%d\n",ans[i]);
	
	return 0;
}
