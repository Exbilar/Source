#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
    scanf("%d%d",&n,&k);
    printf("%d\n",n==1?1:min(k,n-k+1)<<1);

    return 0;
}
