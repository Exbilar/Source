#include <cstdio>
#include <algorithm>

static const int maxm = 4e6 + 10;

int size[maxm],cnt[maxm],ch[maxm][2],v[maxm],rnk[maxm],rt[maxm],A[maxm];
int sz,n,m,ans;

namespace treap{

	int chk(int x,int y){
		return x == y ? 233 : x > y;
	}
	
	void upt(int x) {
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
		if(!x) return x = ++sz,size[x] = cnt[x] = 1,rnk[x] = rand(),v[x] = val,void();
		size[x]++;
		if(v[x] == val) return cnt[x]++,void();
		int f = chk(val,v[x]);
		insert(ch[x][f],val);
		if(rnk[x] < rnk[ch[x][f]]) rotate(x,f);
	}
	
	void del(int &x,int val){
		if(!x) return;
		int k = chk(val,v[x]);
		if(val != v[x]) size[x]--,del(ch[x][k],val);
		if(val == v[x]){
			if(cnt[x] > 1) return size[x]--,cnt[x]--,void();
			if(ch[x][0] * ch[x][1] == 0) return x = ch[x][0] ^ ch[x][1],void();
			int f = chk(rnk[ch[x][0]],rnk[ch[x][1]]);
			rotate(x,f);del(x,val);
		}
	}

	int Qrank(int x,int val){
		if(!x) return 0;
		if(val < v[x]) return Qrank(ch[x][0],val);
		else if(val > v[x]) return size[ch[x][0]] + cnt[x] + Qrank(ch[x][1],val);
		else return size[ch[x][0]];
	}

	int find(int x,int val){
		if(!x) return 0;
		if(v[x] == val) return cnt[x];
		return val > v[x] ? find(ch[x][1],val) : find(ch[x][0],val);
	}
	
}

namespace BIT{
	
	using namespace treap;

	int lowbit(int x){
		return x & -x;
	}
	
	void Upt(int k,int val,int f){
		for(int i = k;i <= n;i += lowbit(i))
			f ? insert(rt[i],val) : del(rt[i],val);
	}

	int Qry(int k,int val,int f){
		int ret = 0;
		for(int i = k;i;i -= lowbit(i))
			ret += f ? Qrank(rt[i],val) : find(rt[i],val);
		return ret;
	}
	
}

using namespace BIT;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	for(int i = n;i >= 1;i--) Upt(i,A[i],1),ans += Qry(n,A[i],1) - Qry(1,A[i],1);

	printf("%d\n",ans);

	scanf("%d",&m);
	
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		if(x > y) std :: swap(x,y);
		if(A[x] == A[y]){printf("%d\n",ans);continue;}
		int tmp1 = Qry(y - 1,A[x],1) - Qry(x,A[x],1);
		int tmp2 = Qry(y - 1,A[y],1) - Qry(x,A[y],1);
		int less = tmp1 - tmp2;
		int tmp3 = (y - x - 1) - (Qry(y - 1,A[x],1) - Qry(x,A[x],1)) -(Qry(y - 1,A[x],0) - Qry(x,A[x],0));
		int tmp4 = (y - x - 1) - (Qry(y - 1,A[y],1) - Qry(x,A[y],1)) -(Qry(y - 1,A[y],0) - Qry(x,A[y],0));
		int more = tmp3 - tmp4;
		ans = ans + more - less;
		ans += A[x] > A[y] ? -1 : 1;
		Upt(x,A[x],0);Upt(y,A[x],1);
		Upt(y,A[y],0);Upt(x,A[y],1);
		std :: swap(A[x],A[y]);
		printf("%d\n",ans);
	}
	
	return 0;
}
