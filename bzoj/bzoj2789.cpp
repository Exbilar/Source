#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

using std :: queue;

typedef long long LL;

static const int maxm = 1e6 + 10;

LL tr[maxm],A[maxm];
char ch1[maxm],ch2[maxm];
int n;
LL ans;

queue <int> Q[26+10];

int lowbit(int x){
	return x&-x;
}

void Upt(int k,LL val){
	for(int i = k;i <= n;i += lowbit(i))
		tr[i] += val;
}

LL Query(int k){
	LL ret = 0;
	for(int i = k;i;i -= lowbit(i))
		ret += tr[i];
	return ret;
}

int main(){
	scanf("%d%s%s",&n,ch1+1,ch2+1);
	
	for(int i = 1;i <= n;i++)Q[ch1[i] - 'A' + 1].push(i);
	for(int i = 1;i <= n;i++)A[i]=Q[ch2[i] - 'A' + 1].front(),Q[ch2[i] - 'A' + 1].pop();
	
	for(int i = 1;i <= n;i++){
		ans += Query(n) - Query(A[i]);
		Upt(A[i],1);
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
