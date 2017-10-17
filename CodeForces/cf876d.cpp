#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int p[maxm],A[maxm],pos[maxm],tr[maxm];
int n;

int lowbit(int x){
	return x & -x;
}

void Upt(int k,int v){
	for(int i = k;i <= n;i += lowbit(i)) tr[i] += v;
}

int Qry(int k){
	int res = 0;
	for(int i = k;i;i -= lowbit(i)) res += tr[i];
	return res;
}

int find(){
	int l = 1,r = n,res = n + 1;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(Qry(n) - Qry(mid - 1) == n - mid + 1) res = mid,r = mid - 1;
		else l = mid + 1;
	}
	return res;
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&p[i]);
	
	printf("%d ",1);
	for(int i = 1;i <= n;i++){
		Upt(p[i],1);
		int tmp = find();
		printf("%d ",i - (n - tmp + 1) + 1);
	}
	putchar(10);
	
	return 0;
}
