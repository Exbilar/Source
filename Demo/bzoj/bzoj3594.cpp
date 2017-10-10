#include <cstdio>
#include <algorithm>

static const int maxm=1e6+10;

int tr[6000+5][500+5],A[maxm];
int n,m,Max_val,ans;

inline void read(int &in){
	in=0;char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar());
	for(;ch>='0'&&ch<='9';ch=getchar())in=in*10+ch-'0';
}

int lowbit(int x){
	return x&-x;
}

void Add(int x,int y,int val){
	for(int i=x;i<=Max_val+m;i+=lowbit(i))
		for(int j=y;j<=m+1;j+=lowbit(j))
			tr[i][j]=std::max(tr[i][j],val);
}

int Query(int x,int y){
	int ret=0;
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j;j-=lowbit(j))
			ret=std::max(tr[i][j],ret);
	return ret;
}

int main(){
	read(n);read(m);
	for(int i=1;i<=n;i++)read(A[i]),Max_val=std::max(Max_val,A[i]);
	
	for(int i=1;i<=n;i++){
		for(int j=m;j>=0;j--){
			int tmp=Query(A[i]+j,j+1)+1;
			ans=std::max(ans,tmp);
			Add(A[i]+j,j+1,tmp);
		}
	}
	
	printf("%d\n",ans);
	
	return 0;
}
