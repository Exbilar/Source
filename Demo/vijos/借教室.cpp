#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

int d[maxm],s[maxm],t[maxm],num[maxm],Q[maxm];
int n,m;

inline int read(){
    int in=0;char ch;ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar());
    for(;ch>='0'&&ch<='9';ch=getchar())in=in*10+ch-'0';
    return in;
}

bool check(int x){
    int tot=0;
    for(int i=1;i<=n;i++)Q[i]=0;
    for(int i=1;i<=x;i++)Q[s[i]]+=d[i],Q[t[i]+1]-=d[i];
    for(int i=1;i<=n;i++){
		tot+=Q[i];
		if(tot>num[i])return false;
    }
    return true;
}

int main(){
    n=read();m=read();
    for(int i=1;i<=n;i++)num[i]=read();
    for(int i=1;i<=m;i++)d[i]=read(),s[i]=read(),t[i]=read();

    int l=1;int r=m;

    while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))l=mid+1;
		else r=mid-1;
    }

    if(l>m)puts("0");
    else puts("-1"),printf("%d\n",l);
    
    return 0;
}
