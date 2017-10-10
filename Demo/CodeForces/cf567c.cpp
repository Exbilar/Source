#include <bits/stdc++.h>

using std :: max;
using std :: min;
using std :: map;

typedef long long LL;
typedef map<int,LL> :: iterator itr;

static const int maxm = 1e6 + 10;

map<int,LL> f[10];
int A[maxm];
LL n,k,ans;

int main(){
	scanf("%I64d%I64d",&n,&k);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	
	for(int i = 1;i <= n;i++){
		int x = A[i];
		if(x % k == 0){
			f[3][x] += f[2][x / k];
			f[2][x] += f[1][x / k];
		}
		f[1][x]++;
	}
	
	for(itr it = f[3].begin();it != f[3].end();it++) ans += (*it).second;
	
	printf("%I64d\n",ans);
	
	return 0;
}
