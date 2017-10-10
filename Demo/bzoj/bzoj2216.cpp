#include <cstdio>
#include <cmath>
#include <algorithm>

using std :: max;
using std :: sqrt;
using std :: ceil;

static const int maxm = 1e6 + 10;

int f[maxm],g[maxm],A[maxm];
int n;

void solve1(int l,int r,int L,int R){
	if(l > r || L > R) return;
	
	int pos = 0,mid = (l + r) >> 1; double mx = 0;
	
	for(int i = L;i <= R && i <= mid;i++)
		if((double) A[i] + sqrt(mid - i) >= mx)
			pos = i,mx = (double) A[i] + sqrt(mid - i);
			
	f[mid] = A[pos] + ceil(sqrt(mid - pos));
	
	solve1(l,mid - 1,L,pos);
	solve1(mid + 1,r,pos,R);
}

void solve2(int l,int r,int L,int R){
	if(l > r || L > R) return;
	
	int pos = 0,mid = (l + r) >> 1; double mx = 0;
	
	for(int i = R;i >= L && i >= mid;i--)
		if((double) A[i] + sqrt(i - mid) >= mx)
			pos = i,mx = (double) A[i] + sqrt(i - mid);
			
	g[mid] = A[pos] + ceil(sqrt(pos - mid));
	
	solve2(l,mid - 1,L,pos);
	solve2(mid + 1,r,pos,R);
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)scanf("%d",&A[i]);
	
	solve1(1,n,1,n);solve2(1,n,1,n);
	
	for(int i = 1;i <= n;i++)printf("%d\n",max(f[i],g[i])-A[i]);
	
	return 0;
}
