#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int cnt[maxm];
int n,m,x,y;

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++) scanf("%d%d",&x,&y),cnt[x]++,cnt[y]++;

	for(int i = 1;i <= n;i++){
		if(cnt[i] & 1) return puts("NO"),0;
	}

	puts("YES");
	
	return 0;
}
