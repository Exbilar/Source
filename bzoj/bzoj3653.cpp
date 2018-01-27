#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 3e5 + 10;

template <class T> inline bool chkmax(T &x,T y){
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in){
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

LL fst[maxm],nxt[maxm << 1],to[maxm << 1];
LL lc[maxm * 20],rc[maxm * 20],rt[maxm];
LL posl[maxm],posr[maxm],pos[maxm],dpt[maxm];
LL sum[maxm * 20],size[maxm];

LL cnt,n,m,sz,dfn,tot;

void ins(LL f,LL t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

void dfs(LL x,LL fa){
	posl[x] = ++sz,pos[sz] = x;
	chkmax(tot,dpt[x]);
	size[x] = 1;
	
	for(LL u = fst[x];u;u = nxt[u]){
		LL v = to[u];
		if(v == fa) continue;
		dpt[v] = dpt[x] + 1;
		dfs(v,x);
		size[x] += size[v];
	}
	posr[x] = sz;
}

void insert(LL &x,LL lst,LL l,LL r,LL pos,LL v){
	x = ++sz; lc[x] = lc[lst],rc[x] = rc[lst]; sum[x] = sum[lst] + v;
	if(l == r) return ;
	LL mid = (l + r) >> 1;
	if(pos <= mid) insert(lc[x],lc[lst],l,mid,pos,v);
	else insert(rc[x],rc[lst],mid + 1,r,pos,v);
}

LL Query(LL x,LL l,LL r,LL L,LL R){
	if(!x) return 0;
	if(l >= L && r <= R) return sum[x];
	LL mid = (l + r) >> 1,res = 0;
	if(L <= mid) res += Query(lc[x],l,mid,L,R);
	if(R > mid) res += Query(rc[x],mid + 1,r,L,R);
	return res;
}

int main(){

	read(n),read(m);

	LL x,y;
	for(LL i = 1;i < n;i++) read(x),read(y),ins(x,y);

	dfs(1,0);
	
	for(LL i = 1;i <= n;i++){
		insert(rt[i],rt[i - 1],0,tot,dpt[pos[i]],size[pos[i]] - 1);
	}
	
	while(m--){
		read(x),read(y);
		LL ans = 1LL * (size[x] - 1) * min(dpt[x],y);
		ans += Query(rt[posr[x]],0,tot,dpt[x] + 1,dpt[x] + y)
			- Query(rt[posl[x] - 1],0,tot,dpt[x] + 1,dpt[x] + y);
		printf("%lld\n",ans);
	}
	
	return 0;
}
