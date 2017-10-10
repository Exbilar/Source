#include <set>
#include <cstdio>
#include <algorithm>

using std :: set;

typedef set<int> :: iterator itr;
static const int maxm = 1e6 + 10;

set<int> S[maxm];

int cnt[maxm],ans[maxm];
char str[10];
int n,m,x,y;

int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%s",str);
		if(str[0] == '!') scanf("%d",&x),cnt[x]++;
		if(str[0] == '+')
			scanf("%d%d",&x,&y),
				ans[x] -= cnt[y],ans[y] -= cnt[x],
				S[x].insert(y),S[y].insert(x);
		if(str[0] == '-')
			scanf("%d%d",&x,&y),
				ans[x] += cnt[y],ans[y] += cnt[x],
				S[x].erase(y),S[y].erase(x);
	}

	for(int i = 1;i <= n;i++)
		for(itr it = S[i].begin();it != S[i].end();it++)
			ans[i] += cnt[*it];

	for(int i = 1;i < n;i++) printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
	
	return 0;
}
