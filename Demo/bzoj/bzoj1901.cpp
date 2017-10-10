#include <cstdio>
#include <algorithm>

static const int maxm = 2e6 + 10;
static const int INF = 1 << 29;

int ch[maxm][2],v[maxm],rnk[maxm],rt[maxm],size[maxm],cnt[maxm],A[maxm];
char opt[10];
int sz,n,m;

namespace treap{
	
	int chk(int x,int y){
		return x == y ? 233 : x > y;
	}
	
	void upt(int x){
		size[x] = size[ch[x][0]] + size[ch[x][1]] + cnt[x];
	}
	
	void rotate(int &x,int f){
		int t = ch[x][f];
		ch[x][f] = ch[t][f ^ 1];
		ch[t][f ^ 1] = x;
		size[t] = size[x];
		upt(x);x = t;
	}
	
	void insert(int &x,int val){
		if(!x){
			x = ++sz; size[x] = cnt[x] = 1; v[x] = val; rnk[x] = rand();
			return;
		}
		size[x]++;
		if(v[x] == val) return cnt[x]++,void();
		int f = chk(val,v[x]);
		insert(ch[x][f],val);
		if(rnk[x] < rnk[ch[x][f]]) rotate(x,f);
	}
	
	void del(int &x,int val){
		if(!x) return;
		int k = chk(val,v[x]);
		if(v[x] != val) size[x]--,del(ch[x][k],val);
		if(v[x] == val){
			if(cnt[x] > 1) return cnt[x]--,void();
			if(ch[x][0] * ch[x][1] == 0) return x = ch[x][0] ^ ch[x][1],void();
			int f = chk(rnk[ch[x][0]],rnk[ch[x][1]]);
			rotate(x,f);del(x,val);
		}
	}
	
	int Qrank(int x,int val){
		if(!x) return 0;
		if(v[x] == val) return size[ch[x][0]];
		return val > v[x] ? size[ch[x][0]] + cnt[x] + Qrank(ch[x][1],val) : Qrank(ch[x][0],val);
	}

}

namespace SMT{

	using namespace treap;
	
	void build(int x,int l,int r){
		for(int i = l;i <= r;i++) insert(rt[x],A[i]);
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1,l,mid);
		build(x << 1 | 1,mid + 1,r);
	}
	
	void modify(int x,int l,int r,int pos,int val){
		del(rt[x],A[pos]);
		insert(rt[x],val);
		if(l == r) return;
		int mid = (l + r) >> 1;
		if(pos <= mid) modify(x << 1,l,mid,pos,val);
		else modify(x << 1 | 1,mid + 1,r,pos,val);
	}
	
	int find_rank(int x,int l,int r,int L,int R,int val){
		if(l >= L && r <= R) return Qrank(rt[x],val);
		int mid = (l + r) >> 1,ret = 0;
		if(L <= mid) ret += find_rank(x << 1,l,mid,L,R,val);
		if(R > mid) ret += find_rank(x << 1 | 1,mid + 1,r,L,R,val);
		return ret;
	}
	
	int solve(int kth,int L,int R){
		int l = 0,r = INF,ret = 0;
		while(l <= r){
			int mid = (l + r) >> 1;
			int tmp = find_rank(1,1,n,L,R,mid) + 1;
			if(tmp <= kth) ret = mid,l = mid + 1;
			else r = mid - 1;
		}
		return ret;
	}
	
}

using namespace SMT;

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	build(1,1,n);
	
	int l,r,pos,val,kth;
	while(m--){
		scanf("%s",opt);
		if(opt[0] == 'C') scanf("%d%d",&pos,&val),modify(1,1,n,pos,val),A[pos] = val;
		if(opt[0] == 'Q') scanf("%d%d%d",&l,&r,&kth),printf("%d\n",solve(kth,l,r));
	}
	
	return 0;
}
