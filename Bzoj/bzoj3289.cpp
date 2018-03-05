#include <cstdio>
#include <cmath>
#include <algorithm>

static const int maxm=1e6+10;

int tr[maxm],F[maxm],ans[maxm];
int block,n,m,cnt,now;

struct Ask{
	int l,r,id;
	bool operator < (const Ask &A) const {
		return l/block==A.l/block?r<A.r:l/block<A.l/block;
	}
}ask[maxm];

struct file{
	int rnk,id;
	bool operator < (const file &f) const {
		return rnk<f.rnk;
	}
}A[maxm];

int lowbit(int x){
	return x&-x;
}

void Add(int k,int val){
	for(int i=k;i<=n;i+=lowbit(i))tr[i]+=val;
}

int Query(int k){
	int ret=0;
	for(int i=k;i;i-=lowbit(i))ret+=tr[i];
	return ret;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i].rnk),A[i].id=i;	
	scanf("%d",&m);
	for(int i=1;i<=m;i++)scanf("%d%d",&ask[i].l,&ask[i].r),ask[i].id=i;
	
	std::sort(A+1,A+n+1);
	
	for(int i=1;i<=n;i++)
		if(A[i].rnk!=A[i-1].rnk)F[A[i].id]=++cnt;
	
	block=std::sqrt(n);
	std::sort(ask+1,ask+m+1);
	
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(l<ask[i].l)Add(F[l],-1),now-=Query(F[l++]-1);
		while(l>ask[i].l)now+=Query(F[--l]-1),Add(F[l],1);
		while(r<ask[i].r)now+=Query(cnt)-Query(F[++r]),Add(F[r],1);
		while(r>ask[i].r)Add(F[r],-1),now-=Query(cnt)-Query(F[r--]);
		ans[ask[i].id]=now;
	}
	
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	
	return 0;
}
