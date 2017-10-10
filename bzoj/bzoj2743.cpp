#include <cstdio>
#include <algorithm>

using std :: sort;

static const int maxm = 1e6 + 10;

struct Query{
	int l,r,id;
	bool operator < (const Query &Q) const {
		return l < Q.l;
	}
}ask[maxm];

int nxt[maxm],lst[maxm],tr[maxm],A[maxm],v[maxm],ans[maxm];
int n,c,m,cur = 1;

int lowbit(int x){
	return x&-x;
}

void Upt(int k,int val){
	for(int i = k;i <= n;i += lowbit(i)) tr[i] += val;
}

int Qry(int k){
	int ret = 0;
	for(int i = k;i;i -= lowbit(i))ret += tr[i];
	return ret;
}

int main(){
	scanf("%d%d%d",&n,&c,&m);
	for(int i = 1;i <= n;i++)scanf("%d",&A[i]);
	for(int i = 1;i <= m;i++)scanf("%d%d",&ask[i].l,&ask[i].r),ask[i].id = i;
	sort(ask + 1,ask + m + 1);
	
	for(int i = 1;i <= n;i++){
		if(lst[A[i]]) nxt[lst[A[i]]] = i;
		else v[i] = 1;
		lst[A[i]] = i;
	}
	
	for(int i = 1;i <= n;i++)
		if(v[i] && nxt[i])Upt(nxt[i],1);
	
	for(int i = 1;i <= m;i++){
		while(cur < ask[i].l){
			if(nxt[cur]){
				Upt(nxt[cur],-1);
				if(nxt[nxt[cur]]) Upt(nxt[nxt[cur]],1);
			}
			cur++;
		}
		ans[ask[i].id]=Qry(ask[i].r);
	}
	
	for(int i = 1;i <= m;i++)printf("%d\n",ans[i]);
	
	return 0;
}
