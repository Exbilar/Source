#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

static const int maxm = 1e6 + 10;

int ftr[maxm],lc[maxm],rc[maxm],ans[maxm];
int n,v,rt,top;

int solve(){
	int x = rt;
	while(rc[x] != -1) x = lc[x];
	int t = lc[x];
	if(t != -1 && lc[t] == -1 && rc[t] == -1) x = t;
	ans[++top] = x;
	if(x == rt) rt = lc[rt];
	int fa = ftr[x];
	if(fa != -1) lc[fa] = lc[x],ftr[lc[x]] = fa;
	while(fa != -1) swap(lc[fa],rc[fa]),fa = ftr[fa];
}

int main(){

	memset(ftr,-1,sizeof ftr);
	memset(lc,-1,sizeof lc);
	memset(rc,-1,sizeof rc);
	
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&v);
		if(v >= 100) rc[v - 100] = i,ftr[i] = v - 100;
		else lc[v] = i,ftr[i] = v;
	}

	for(int i = 1;i <= n + 1;i++) solve();

	while(top >= 2) printf("%d ",ans[top--]);
	printf("%d",ans[top]);
	
	return 0;
}
