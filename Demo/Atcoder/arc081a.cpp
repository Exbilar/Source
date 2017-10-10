#include <bits/stdc++.h>

using std :: map;

static const int maxm = 1e6 + 10;

map<int,int> cnt;

int A[maxm];
int n;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),cnt[A[i]]++;
	
	std :: sort(A + 1,A + n + 1);

	long long x = 0,y = 0;
	
	for(int i = n;i;i--){
		if(x && y) break;
		if(cnt[A[i]] >= 2 && !x) x = A[i],cnt[A[i]] -= 2;
		else if(cnt[A[i]] >= 2 && !y) y = A[i],cnt[A[i]] -= 2;
	}

	printf("%lld\n",1LL * x * y);

	return 0;
}
