#include <cstdio>
#include <algorithm>

using std :: max;
using std :: min;

static const int maxm = 2e6 + 10;
static const int INF = 1 << 29;

int ch[maxm][2],v[maxm],size[maxm],cnt[maxm],rt[maxm],A[maxm],rnk[maxm];
int sz,ans,n,m;

namespace treap{
	
	int chk(int x,int y){
		return x == y ? 2333 : x > y;
	}

	void upt(int x){
		size[x] = size[ch[x][0]] + size[ch[x][1]] + cnt[x];
	}

	void rotate(int &x,int f){
		int t = ch[x][f];
		ch[x][f] = ch[t][f ^ 1];
		ch[t][f ^ 1] = x;
		size[t] = size[x];
		upt(x),x = t;
	}

	void insert(int &x,int val){
		if(!x) return x = ++sz,v[x] = val,size[x] = cnt[x] = 1,rnk[x] = rand(),void();
		size[x]++;
		if(v[x] == val) return cnt[x]++,void();
		int f = chk(val,v[x]);
		insert(ch[x][f],val);
		if(rnk[x] < rnk[ch[x][f]]) rotate(x,f);
	}

	void del(int &x,int val){
		if(!x) return;
		if(val != v[x]) size[x]--,del(ch[x][chk(val,v[x])],val);
		if(val == v[x]){
			if(cnt[x] > 1) return size[x]--,cnt[x]--,void();
			if(ch[x][0] * ch[x][1] == 0) return x = ch[x][0] ^ ch[x][1],void();
			int f = chk(rnk[ch[x][0]],rnk[ch[x][1]]);
			rotate(x,f);del(x,val);
		}
	}

	int Qrank(int x,int val){
		if(!x) return 0;
		if(val == v[x]) return size[ch[x][0]];
		return val > v[x] ? size[ch[x][0]] + cnt[x] + Qrank(ch[x][1],val) : Qrank(ch[x][0],val);
	}

	int Query(int x,int val,int f,int &ans){
		if(!x) return 0;
		if(chk(v[x],val) == f) return ans = f ? min(ans,v[x]) : max(ans,v[x]),Query(ch[x][f ^ 1],val,f,ans);
		else return Query(ch[x][f],val,f,ans);
	}// ?
	
}

namespace segment_tree{
	
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
		if(pos > mid) modify(x << 1 | 1,mid + 1,r,pos,val);
	}

	int Getrank(int x,int l,int r,int L,int R,int val){
		if(l >= L && r <= R) return Qrank(rt[x],val);
		int mid = (l + r) >> 1,ret = 0;
		if(L <= mid) ret += Getrank(x << 1,l,mid,L,R,val);
		if(R > mid)  ret += Getrank(x << 1 | 1,mid + 1,r,L,R,val);
		return ret;
	}

	int Getorder(int L,int R,int rnk){
		int l = 0,r = INF,ret = 0;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(Getrank(1,1,n,L,R,mid) + 1 <= rnk) ret = mid,l = mid + 1;
			else r = mid - 1;
		}
		return ret;
	}

	int Get(int x,int l,int r,int L,int R,int val,int f,int &ans){
		if(l >= L && r <= R) return Query(rt[x],val,f,ans);
		int mid = (l + r) >> 1;
		if(L <= mid) Get(x << 1,l,mid,L,R,val,f,ans);
		if(R > mid) Get(x << 1 | 1,mid + 1,r,L,R,val,f,ans);
	}
}

int main(){
	
	using namespace segment_tree;
	
	//	freopen("bzoj3196.in","r",stdin);
	
	int opt,x,y,k;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	build(1,1,n);

	while(m--){
		scanf("%d%d%d",&opt,&x,&y);
		if(opt == 1) scanf("%d",&k),printf("%d\n",Getrank(1,1,n,x,y,k) + 1);
		if(opt == 2) scanf("%d",&k),printf("%d\n",Getorder(x,y,k));
		if(opt == 3) modify(1,1,n,x,y),A[x] = y;
		if(opt == 4) ans = -INF,scanf("%d",&k),Get(1,1,n,x,y,k,0,ans),printf("%d\n",ans);
		if(opt == 5) ans = INF,scanf("%d",&k),Get(1,1,n,x,y,k,1,ans),printf("%d\n",ans);
	}
	
	return 0;
}
