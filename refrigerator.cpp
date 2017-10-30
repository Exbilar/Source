#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
const int size=100010,mod=19260817;
int n,m,ans=0,f[size];
bool flag;
struct data{
	int k,d;
	bool operator < (const data &x)const{return d<x.d;}
}c[510];
template <typename Tp> inline void read(Tp &x)
{
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
}
void input()
{
	read(n),read(m);
	for(int i=1;i<=n;i++)
	  read(c[i].k),read(c[i].d);
}
int main()
{
	freopen("refrigerator.in","r",stdin);
	freopen("refrigerator.out","w",stdout);
	input();
	sort(c+1,c+n+1);
	f[m]=1;
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m-c[i].d;j++)
	  {
	  	for(int r=c[i].k;r>=1;r--)
	      if(j+r*c[i].d<=m)
	      	f[j]=(f[j]+f[j+r*c[i].d])%mod;
	    if(i==1&&j<=c[2].d)
	      ans=(ans+f[j])%mod;
	    else if(i!=1&&j<=c[1].d)
	      ans=(ans+f[j])%mod;
	  }
	printf("%d\n",ans%mod);
	return 0;
}
