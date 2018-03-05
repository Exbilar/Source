#include <cstdio>
#include <algorithm>
using namespace std;

#define len first
#define col second

typedef pair<int,int> pii;

static const int maxm = 1e6 + 10;

pii stk[maxm],A[maxm];
int n,top,k,f;

int main(){
	scanf("%d",&k);
	for(int i = 1;i <= k;i++){
		scanf("%d",&n);
		for(int j = 1;j <= n;j++)
			scanf("%d",&stk[++top].len),stk[top].col = i;
	}

	sort(stk + 1,stk + top + 1);

	for(int i = 1;i <= top;i++){
		f = 0;
		for(int j = 1;j <= 3;j++){
			if(A[j].col == stk[i].col){
				A[j] = stk[i];
				break;
			}
			if(j == 3) f = 1;
		}
		if(f) A[1] = stk[i];
		sort(A + 1,A + 3 + 1);
		if(A[3].len < A[1].len + A[2].len && A[1].col)
			return printf("%d %d %d %d %d %d\n",A[1].col,A[1].len,A[2].col,A[2].len,A[3].col,A[3].len),0;
	}

	puts("NIE");
	
	return 0;
}
