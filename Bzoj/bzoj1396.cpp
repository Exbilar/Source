#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;

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

char str[maxm];
int ans[maxm];

struct SegmentTree{
	int smin[maxm];

	void build(int x,int l,int r){
		smin[x] = INF;
		if(l == r) return ;
		int mid = (l + r) >> 1;
		build(x << 1,l,mid);
		build(x << 1 | 1,mid + 1,r);
	}

	void pushtag(int x,int v){
		chkmin(smin[x],v);
	}
	
	void pushdown(int x){
		pushtag(x << 1,smin[x]);
		pushtag(x << 1 | 1,smin[x]);
	}
	
	void modify(int x,int l,int r,int L,int R,int v){
		if(L > R) return ;
		if(l >= L && r <= R) return pushtag(x,v),void();
		int mid = (l + r) >> 1;
		pushdown(x);
		if(L <= mid) modify(x << 1,l,mid,L,R,v);
		if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,v);
	}
	
	int Query(int x,int l,int r,int pos){
		if(l == r) return smin[x];
		int mid = (l + r) >> 1;
		pushdown(x);
		if(pos <= mid) return Query(x << 1,l,mid,pos);
		else return Query(x << 1 | 1,mid + 1,r,pos);
	}
}T1,T2;

struct Suffix_Automaton{
	int len[maxm],size[maxm],fail[maxm],ch[maxm][26];
	int bin[maxm],rnk[maxm];
	int rt,sz,lst;

	Suffix_Automaton(){
		sz = 0; lst = rt = ++sz;
		len[rt] = fail[rt] = 0;
	}

	void insert(int v){
		int x = ++sz,cur = lst;
		len[x] = len[lst] + 1; size[x] = 1;
		lst = x;

		while(cur && !ch[cur][v]) ch[cur][v] = x,cur = fail[cur];
		if(!cur) return fail[x] = rt,void();

		int pos = ch[cur][v];
		if(len[pos] == len[cur] + 1) return fail[x] = pos,void();

		int clone = ++sz;
		fail[clone] = fail[pos];
		len[clone] = len[cur] + 1;
		memcpy(ch[clone],ch[pos],sizeof ch[pos]);

		fail[x] = fail[pos] = clone;
		while(cur && ch[cur][v] == pos) ch[cur][v] = clone,cur = fail[cur];
	}

	void radixSort(int n){
		for(int i = 1;i <= sz;i++) bin[len[i]]++;
		for(int i = 1;i <= n;i++) bin[i] += bin[i - 1];
		for(int i = 1;i <= sz;i++) rnk[bin[len[i]]--] = i;
		for(int i = sz;i >= 1;i--) size[fail[rnk[i]]] += size[rnk[i]];
	}
	
	void solve(int n){
		for(int i = 1;i <= sz;i++){
			if(size[i] != 1) continue;
			int r = len[i],l = len[i] - len[fail[i]];
			T1.modify(1,1,n,1,l - 1,r + 1);
			T2.modify(1,1,n,l,r,r - l + 1);
		}
		for(int i = 1;i <= n;i++)
			ans[i] = min(T1.Query(1,1,n,i) - i,T2.Query(1,1,n,i));
		
		for(int i = 1;i <= n;i++) printf("%d\n",ans[i]);
	}
	
}SAM;

int main(){
	
	scanf("%s",str);
	int n = strlen(str);

	T1.build(1,1,n),T2.build(1,1,n);

	for(int i = 0;i < n;i++) SAM.insert(str[i] - 'a');
	SAM.radixSort(n);
	SAM.solve(n);

	return 0;
}
