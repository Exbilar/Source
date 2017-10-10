#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int ch[maxm][2],v[maxm],size[maxm],rnk[maxm],A[maxm],tr[maxm],ans[maxm];
int rt,cnt,sz,n,m;

void upt(int x){
	size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
}

void rotate(int &x,int f){
	int t = ch[x][f];
	ch[x][f] = ch[t][f ^ 1];
	ch[t][f ^ 1] = x;
	size[t] = size[x];
	upt(x),x = t;
}

void insert(int &x,int pos){
	if(!x) return x = ++sz,rnk[x] = rand(),size[x] = 1,void();
	size[x]++;
	if(pos <= size[ch[x][0]]){
		insert(ch[x][0],pos);
		if(rnk[x] < rnk[ch[x][0]]) rotate(x,0);
	}
	if(pos > size[ch[x][0]]){
		insert(ch[x][1],pos - size[ch[x][0]] - 1);
		if(rnk[x] < rnk[ch[x][1]]) rotate(x,1);
	}
}

void dfs(int x){
	if(!x) return;
	dfs(ch[x][0]);
	A[++cnt] = x;
	dfs(ch[x][1]);
}

int lowbit(int x){
	return x & -x;
}

void Upt(int k,int val){
	for(int i = k;i <= n;i += lowbit(i))
		tr[i] = std :: max(tr[i],val);
}

int Qry(int k){
	int ret = 0;
	for(int i = k;i;i -= lowbit(i))
		ret = std :: max(ret,tr[i]);
	return ret;
}

int main(){
	int x;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&x);
		insert(rt,x);
	}

	dfs(rt);
	
	for(int i = 1;i <= n;i++){
		int tmp = Qry(A[i]) + 1;
		Upt(A[i],tmp);
		ans[A[i]] = tmp;
	}

	for(int i = 1;i <= n;i++) ans[i] = std :: max(ans[i - 1],ans[i]);

	for(int i = 1;i <= n;i++) printf("%d\n",ans[i]);
	
	return 0;
}
