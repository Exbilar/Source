#include <cstdio>

typedef long long LL;

static const int maxm=100005;

LL A[maxm],pls[maxm<<2],mul[maxm<<2],tr[maxm<<2];
int left[maxm<<2],right[maxm<<2];
int n,m;
LL MOD;

int build(int id,int l,int r){
    left[id]=l;right[id]=r;mul[id]=1;
    if(l==r)return tr[id]=A[l]%MOD,0;
    int mid=(l+r)>>1;
    build(id<<1,l,mid);
    build(id<<1|1,mid+1,r);
    tr[id]=(tr[id<<1]+tr[id<<1|1])%MOD;
}

void pushdown(int id){
    int l=left[id];int r=right[id];int mid=(l+r)>>1;
    pls[id<<1]=(pls[id<<1]*mul[id]%MOD+pls[id])%MOD;
    pls[id<<1|1]=(pls[id<<1|1]*mul[id]%MOD+pls[id])%MOD;
    mul[id<<1]=(mul[id]*mul[id<<1])%MOD;
    mul[id<<1|1]=(mul[id]*mul[id<<1|1])%MOD;
    tr[id<<1]=(tr[id<<1]*mul[id]%MOD+pls[id]*(mid-l+1)%MOD)%MOD;
    tr[id<<1|1]=(tr[id<<1|1]*mul[id]%MOD+pls[id]*(r-mid)%MOD)%MOD;
    mul[id]=1;pls[id]=0;
}

void modify(int id,int l,int r,int c,int opt){
    if(left[id]>=l&&right[id]<=r){
	if(opt==1){
	    mul[id]=(mul[id]*c)%MOD;
	    pls[id]=(pls[id]*c)%MOD;
	    tr[id]=(tr[id]*c)%MOD;
	}else if(opt==2){
	    pls[id]=(pls[id]+c)%MOD;
	    tr[id]=(tr[id]+(LL)c*(right[id]-left[id]+1)%MOD)%MOD;
	}
	return ;
    }
    if(right[id]<l||left[id]>r)return ;
    pushdown(id);
    modify(id<<1,l,r,c,opt);
    modify(id<<1|1,l,r,c,opt);
    tr[id]=(tr[id<<1]+tr[id<<1|1])%MOD;
}

LL Query(int id,int l,int r){
    if(left[id]>=l&&right[id]<=r)return tr[id]%MOD;
    if(left[id]>r||right[id]<l)return 0;
    pushdown(id);
    return (Query(id<<1,l,r)%MOD+Query(id<<1|1,l,r)%MOD)%MOD;
}

int main(){
    int opt,l,r,c;
    scanf("%d%lld",&n,&MOD);
    for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
    scanf("%d",&m);

    build(1,1,n);
    
    while(m--){
	scanf("%d",&opt);
	if(opt!=3){
	    scanf("%d%d%d",&l,&r,&c);
	    modify(1,l,r,c,opt);
	}
	else scanf("%d%d",&l,&r),printf("%lld\n",Query(1,l,r)%MOD);
    }

    return 0;
}
