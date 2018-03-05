#include <cstdio>
#include <cstring>
#include <algorithm>

using std :: max;
using std :: min;

static const int maxm = 20;

int cnt[maxm],card[maxm];
int n,m,cas,ans;

void dfs(int x){
	if(x > ans) return ;
	memset(cnt,0,sizeof cnt); int res = 0;
	for(int i = 0;i <= 14;i++) cnt[card[i]]++;
	
	while(cnt[4]){
		cnt[4]--; res++;
		if(cnt[2] >= 2) cnt[2] -= 2;
		else if(cnt[1] >= 2) cnt[1] -= 2;
	}
	
	while(cnt[3]){
		cnt[3]--; res++;
		if(cnt[2]) cnt[2]--;
		else if(cnt[1]) cnt[1]--;
	}
	
	if(card[0] && card[1] && cnt[1] >= 2) res--;
	res += cnt[1] + cnt[2];
	
	ans = min(ans,x + res);
	
	for(int i = 3;i <= 14;i++){
		int j = 0;
		for(j = i;card[j] && j <= 14;j++){
			card[j]--;
			if(j - i + 1 >= 5) dfs(x + 1);
		}
		while(j > i) card[--j]++;
	}
	
	for(int i = 3;i <= 14;i++){
		int j = 0;
		for(j = i;card[j] >= 2 && j <= 14;j++){
			card[j] -= 2;
			if(j - i + 1 >= 3) dfs(x + 1);
		}
		while(j > i) card[--j] += 2;
	}

	for(int i = 3;i <= 14;i++){
		int j = 0;
		for(j = i;card[j] >= 3 && j <= 14;j++){
			card[j] -= 3;
			if(j - i + 1 >= 2) dfs(x + 1);
		}
		while(j > i) card[--j] += 3;
	}
	
}

int main(){
	int A,B;
	scanf("%d%d",&cas,&n);
	while(cas--){
		memset(card,0,sizeof card); ans = n;
		for(int i = 1;i <= n;i++){
			scanf("%d%d",&A,&B);
			if(A == 0) card[B - 1]++;
			else if(A == 1) card[14]++;
			else card[A]++;
		}
		dfs(0);
		printf("%d\n",ans);
	}	

	return 0;
}
