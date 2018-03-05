#include <cstdio>
#include <cmath>
#include <algorithm>

static const int maxm = 2e6 + 10;

int pos[maxm],k[maxm],st[maxm],pt[maxm];
int block,n,m,x,v,opt;

int main(){
	scanf("%d",&n); block = sqrt(n + 0.5);
	for(int i = 1;i <= n;i++) scanf("%d",&k[i]);
	
	for(int i = 1;i <= n;i++) pos[i] = (i - 1) / block + 1;
	
	for(int i = n;i;i--){
		if(pos[i + k[i]] == pos[i]) st[i] = st[i + k[i]] + 1,pt[i] = pt[i + k[i]];
		else if(i + k[i] > n) st[i] = 1,pt[i] = n + 1;
		else st[i] = 1,pt[i] = i + k[i];
	}

	scanf("%d",&m);

	for(int i = 1;i <= m;i++){
		int ans = 0;
		scanf("%d",&opt);
		if(opt == 1){
			scanf("%d",&x);x++;
			while(x <= n) ans += st[x],x = pt[x];
			printf("%d\n",ans);
		}
		if(opt == 2){
			scanf("%d%d",&x,&v);x++;k[x] = v;
			for(int i = x;i >= (pos[x] - 1) * block + 1;i--)
				if(pos[i + k[i]] == pos[i]) st[i] = st[i + k[i]] + 1,pt[i] = pt[i + k[i]];
				else if(i + k[i] > n) st[i] = 1,pt[i] = n + 1;
				else st[i] = 1,pt[i] = i + k[i];
		}
	}

	
	return 0;
}
