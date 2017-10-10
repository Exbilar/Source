#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

static const int maxm=2e6+10;

struct node{
	int v,id;
	bool operator < (const node &n) const {
		return v>n.v;
	}
}A[maxm];

int tr[maxm];
int N,N1,N2,pos;
LL ans;

int lowbit(int x){
	return x&-x;
}

void add(int val,int k){
	for(int i=k;i<=N;i+=lowbit(i))tr[i]+=val;
}

int Query(int k){
	int ret=0;
	for(int i=k;i;i-=lowbit(i))ret+=tr[i];
	return ret;
}

int solve(int l,int r){
	if(l>r)swap(l,r);
	return Query(r)-Query(l-1);
}

int main(){
	scanf("%d%d",&N1,&N2);N=N1+N2+1;pos=N1+1;
	for(int i=N1;i>=1;i--)scanf("%d",&A[i].v);
	for(int i=N1+2;i<=N;i++)scanf("%d",&A[i].v);
	
	for(int i=1;i<=N;i++){
		if(i!=pos)add(1,i);
		A[i].id=i;
	}
	
	sort(A+1,A+N+1);
	
	for(int i=1;i<N;i++){
		ans+=solve(A[i].id,pos)-1;
		pos=A[i].id;add(-1,pos);
	}
	
	printf("%lld\n",ans);

	return 0;	
}
