#include <cstdio>
#include <bitset>
#include <algorithm>
using namespace std;

static const int maxm = 1e6 + 10;

bitset<maxm> A[100 + 10];
int n,l,r;

int main(){
	scanf("%d",&n);
	A[0][0] = 1;
	for(int i = 1;i <= n;i++){
		scanf("%d%d",&l,&r);
		for(int j = l;j <= r;j++) A[i] |= A[i - 1] << (j * j);
	}

	printf("%d\n",(int)A[n].count());
	
	return 0;
}
