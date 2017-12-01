#include <bits/stdc++.h>
using namespace std;

static const int maxm = 1e6 + 10;

int col[maxm],val[maxm],num[maxm];
int ans,n,m;

int main(){
	scanf("%d%d",&n,&m);

	for(int i = 1;i <= n;i++) scanf("%d",&col[i]);
	for(int i = 1;i <= n;i++) scanf("%d",&val[i]);

	while(m--){
		int opt,l,r,p,c;
		scanf("%d",&opt);
		if(opt == 1){
			scanf("%d%d",&p,&c); col[p] = c;
		}
		if(opt == 2){
			memset(num,0,sizeof num);
			scanf("%d%d",&l,&r); int ans = 0;
			for(int i = l;i <= r;i++){
				if(!num[col[i]]) ans += val[col[i]];
				num[col[i]]++;
			}
			printf("%d\n",ans);
		}
	}
	
	return 0;
}
