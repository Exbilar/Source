#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int A[maxm];
int n,ans,f = -1;

int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
    for(int i = 2;i <= n;i++){
        if(A[i] < A[i - 1] && f != 1) ans++ , f = 0;
        if(A[i] > A[i - 1] && f != 0) ans++ , f = 1; 
    }

    printf("%d\n",ans);

    return 0;
}