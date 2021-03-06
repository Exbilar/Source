#include <cstdio>
#include <cstring>
#include <algorithm>

using std :: max;
using std :: min;
using std :: sort;

static const int maxm = 3e3 + 10;

struct object{
    int w,v;
    bool operator < (const object &ob) const {
		return w > ob.w;
    }
}ob[maxm];

int f[maxm][maxm];
int ans,n;

int main(){

    memset(f,128,sizeof f);f[0][1] = 0;
    
    scanf("%d",&n);
    for(int i = 1;i <= n;i++)scanf("%d%d",&ob[i].w,&ob[i].v);
    
    sort(ob+1,ob+n+1);

    for(int i = 1;i <= n;i++)
		for(int v = 0;v <= n;v++)
			f[i][v] = max(f[i - 1][v],f[i - 1][max(v - ob[i].w,0)+1] + ob[i].v);

    for(int i = 0;i <= n;i++)ans = max(ans,f[n][i]);

    printf("%d\n",ans);
    
    return 0;
}
