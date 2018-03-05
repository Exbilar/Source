#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int n,m,ans;
int bit[maxm],val[maxm];
char str[maxm];

int calc(int num){
    for(int i=1;i<=n;i++)
	if(bit[i]==1)num&=val[i];
	else if(bit[i]==2)num|=val[i];
	else if(bit[i]==3)num^=val[i];
    return num;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
	scanf("%s",str);
	if(str[0]=='A')bit[i]=1;
	if(str[0]=='O')bit[i]=2;
	if(str[0]=='X')bit[i]=3;
	scanf("%d",&val[i]);
    }

    for(int i=31;i>=0;i--){
	if(ans+(1<<i)>m)continue;
	int ans1=calc(ans)&(1<<i);
	int ans2=calc(ans+(1<<i))&(1<<i);
	ans=ans1<ans2?ans+(1<<i):ans;
    }
    printf("%d\n",calc(ans));
    
    return 0;
}
