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

int A[maxm],ans[maxm],tmp[maxm],num[maxm];

char str[10];

int blck,n,m,sz,cnt,_cnt;
int L = 1,R = 0,T = 0,cur = 0;

struct Query{
	int l,r,t,id;
	bool operator < (const Query &Q) const {
		if(l / blck == Q.l / blck)
			return r / blck == Q.r / blck ? t < Q.t : r / blck < Q.r / blck;
		
		return l / blck < Q.l / blck;
	}
}opt[maxm];

struct Modify{
	int p,pre,nxt,t;
}mdf[maxm];

void add(int pos){
	num[A[pos]]++;
	if(num[A[pos]] == 1) cur++;
}

void del(int pos){
	num[A[pos]]--;
	if(num[A[pos]] == 0) cur--;
}

void modify_add(int pos){
	if(mdf[pos].nxt == mdf[pos].pre) return ;
	if(mdf[pos].p >= L && mdf[pos].p <= R){
		num[mdf[pos].pre]--,num[mdf[pos].nxt]++;
		if(num[mdf[pos].pre] == 0) cur--;
		if(num[mdf[pos].nxt] == 1) cur++;
	}
	A[mdf[pos].p] = mdf[pos].nxt;
}

void modify_del(int pos){
	if(mdf[pos].pre == mdf[pos].nxt) return ;
	if(mdf[pos].p >= L && mdf[pos].p <= R){
		num[mdf[pos].pre]++,num[mdf[pos].nxt]--;
		if(num[mdf[pos].pre] == 1) cur++;
		if(num[mdf[pos].nxt] == 0) cur--;
	}

	A[mdf[pos].p] = mdf[pos].pre;
}

int main(){
	
	read(n),read(m);
	for(int i = 1;i <= n;i++) read(A[i]),tmp[i] = A[i];

	for(int i = 1,x,y;i <= m;i++){
		scanf("%s",str);
		read(x),read(y);
		
		if(str[0] == 'Q'){
			opt[++cnt].l = x,opt[cnt].r = y;
			opt[cnt].t = ++sz;
			opt[cnt].id = cnt;
		}
		if(str[0] == 'R'){
			mdf[++sz].pre = tmp[x];
			mdf[sz].p = x;
			mdf[sz].nxt = y;
			tmp[x] = y;
		}
	}

	blck = pow(n,2 / (double) 3);

	std :: sort(opt + 1,opt + cnt + 1);

	for(int i = 1;i <= cnt;i++){
		while(T < opt[i].t) modify_add(++T);
		while(T > opt[i].t) modify_del(T--);
		while(R < opt[i].r) add(++R);
		while(R > opt[i].r) del(R--);
		while(L < opt[i].l) del(L++);
		while(L > opt[i].l) add(--L);
		ans[opt[i].id] = cur;
	}
	
	for(int i = 1;i <= cnt;i++) printf("%d\n",ans[i]);
	
	return 0;
}
