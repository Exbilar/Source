#include <cstdio>
#include <algorithm>

using std :: max;
using std :: min;

typedef long long LL;

static const int maxm = 1e6 + 10;

int pre[maxm],tr[maxm],rt[maxm],ch[maxm][2],cnt[maxm];
int	size[maxm],v[maxm],rnk[maxm],A[maxm],pos[maxm];
int sz,n,m;
LL ans;

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

}

namespace BIT{

	using namespace treap;
	
	int lowbit(int x){
		return x & -x;
	}

	void TUpt(int k,int val,int f){
		for(int i = k;i <= n;i += lowbit(i))
			f ? tr[i] += val : pre[i] += val; 
	}

	LL TQry(int k,int f){
		LL ret = 0;
		for(int i = k;i;i -= lowbit(i))
			ret += f ? tr[i] : pre[i];
		return ret;
	}

	void Upt(int k,int val,int f){
		for(int i = k;i <= n;i += lowbit(i))
			f ? insert(rt[i],val) : del(rt[i],val);
	}

	LL Qry(int k,int val){
		LL ret = 0;
		for(int i = k;i;i -= lowbit(i))
			ret += Qrank(rt[i],val);
		return ret;
	}
	
}

using namespace BIT;

int main(){
	int x;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),pos[A[i]] = i;
	for(int i = 1;i <= n;i++) TUpt(i,1,0),Upt(i,A[i],1);
	for(int i = n;i >= 1;i--) ans += TQry(A[i],1),TUpt(A[i],1,1);

	while(m--){
		scanf("%d",&x);
		printf("%lld\n",ans);
		int tot = TQry(pos[x] - 1,0);
		int pre_num = tot - Qry(pos[x],x);
		int nxt_num = Qry(n,x) - Qry(pos[x],x);
		ans = ans - pre_num - nxt_num;
		Upt(pos[x],x,0);TUpt(pos[x],-1,0);
	}

	return 0;
}
