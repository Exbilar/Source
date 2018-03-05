#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int rt[maxm << 2],lc[maxm << 2],rc[maxm << 2],tr[maxm << 2],X[maxm],Y[maxm],K[maxm];
int A[maxm],v[maxm],pos[maxm],L[maxm],R[maxm],opt[maxm];
char ch[10];
int sz,n,m,cnt,cnt1,cnt2,tot;

void insert(int &x,int lst,int l,int r,int pos,int val){
	x = ++sz,lc[x] = lc[lst],rc[x] = rc[lst],tr[x] = tr[lst] + val;
	if(l == r) return ;
	int mid = (l + r) >> 1;
	if(pos <= mid) insert(lc[x],lc[lst],l,mid,pos,val);
	else insert(rc[x],rc[lst],mid + 1,r,pos,val);
}

int SMT_Qry(int l,int r,int kth){
	if(l == r) return l;
	int mid = (l + r) >> 1,tmp = 0;
	for(int i = 1;i <= cnt1;i++) tmp -= tr[lc[L[i]]];
	for(int i = 1;i <= cnt2;i++) tmp += tr[lc[R[i]]];
	if(kth <= tmp){
		for(int i = 1;i <= cnt1;i++) L[i] = lc[L[i]];
		for(int i = 1;i <= cnt2;i++) R[i] = lc[R[i]];
		return SMT_Qry(l,mid,kth);
	}else{
		for(int i = 1;i <= cnt1;i++) L[i] = rc[L[i]];
		for(int i = 1;i <= cnt2;i++) R[i] = rc[R[i]];
		return SMT_Qry(mid + 1,r,kth - tmp);
	}
}

int lowbit(int x){
	return x & -x;
}

void Upt(int k,int val,int f){
	for(int i = k;i <= tot;i += lowbit(i))
		insert(rt[i],rt[i],1,tot,val,f);
}

int Qry(int l,int r,int kth){
	l--,cnt1 = 0,cnt2 = 0;
	for(int i = l;i;i -= lowbit(i)) L[++cnt1] = rt[i];
	for(int i = r;i;i -= lowbit(i)) R[++cnt2] = rt[i];
	return SMT_Qry(1,tot,kth);
}

int main(){

	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&v[i]),A[++cnt] = v[i];
	for(int i = 1;i <= m;i++){
		scanf("%s",ch);
		if(ch[0] == 'C') scanf("%d%d",&X[i],&Y[i]),A[++cnt] = Y[i];
		if(ch[0] == 'Q') scanf("%d%d%d",&X[i],&Y[i],&K[i]),opt[i] = 1;
	}
	
	std :: sort(A + 1,A + cnt + 1);
	tot = std :: unique(A + 1,A + cnt + 1) - A - 1;
	for(int i = 1;i <= n;i++){
		v[i] = std :: lower_bound(A + 1,A + tot + 1,v[i]) - A;
		Upt(i,v[i],1);
	}
	
	for(int i = 1;i <= m;i++){
		if(!opt[i]){
			Y[i] = std :: lower_bound(A + 1,A + tot + 1,Y[i]) - A;
			Upt(X[i],v[X[i]],-1);
			v[X[i]] = Y[i];
			Upt(X[i],v[X[i]],1);
		}else printf("%d\n",A[Qry(X[i],Y[i],K[i])]);
	}
	
	return 0;
}
