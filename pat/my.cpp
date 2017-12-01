#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: max;
using std :: min;

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;
static const LL oo = 1LL << 63;

template <class T> inline bool chkmax(T &x,T y){
	return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
	return x > y ? x = y,true : false;
}

namespace IO{
	
	static const int len = 1 << 20 | 1 ;
	char buffer[len], *Ser, *Ter ;
	inline char Getchar(){
		if (Ser == Ter) Ter = (Ser = buffer) + fread(buffer,1,len,stdin) ;
		return (Ser == Ter) ? (char) EOF : (*Ser++) ;
	}

	template <typename T> inline void read (T &in){
		in = 0; char ch = Getchar(); T f = 1;
		for (;ch > '9' || ch < '0';ch = Getchar()) if(ch == '-') f = -1;
		for (;ch >= '0' && ch <= '9';ch = Getchar()) in = in * 10 + ch - '0';
		in = in * f;
	}
};

int col[maxm],num[maxm],val[maxm],ans[maxm],pre[maxm],ddf[maxm];
int cur,n,m,cnt,tot,block,L,R,T;

struct Opt{
	int l,r,t,id;
	bool operator < (const Opt &opt) const {
		if(t / block == opt.t / block){
			return l / block == opt.l / block ?
				r < opt.r : l / block < opt.l / block;
		}
		else return t / block < opt.t / block;
	}
}opt[maxm];

struct Modify{
	int p,c;
}mdi[maxm];

using namespace IO;

inline void add(int pos){
	if(!num[col[pos]]) cur += val[col[pos]];
	num[col[pos]]++;
}

inline void del(int pos){
	num[col[pos]]--;
	if(!num[col[pos]]) cur -= val[col[pos]];
}

inline void addt(int pos){		
	if(mdi[pos].p < L || mdi[pos].p > R){
		col[mdi[pos].p] = mdi[pos].c;
	}
	else{
		num[col[mdi[pos].p]]--;
		if(!num[col[mdi[pos].p]]) cur -= val[col[mdi[pos].p]];
		num[mdi[pos].c]++;
		if(num[mdi[pos].c] == 1) cur += val[mdi[pos].c];		
		col[mdi[pos].p] = mdi[pos].c;
	}
}

inline void delt(int pos){
	if(mdi[pos].p < L || mdi[pos].p > R){
		col[mdi[pos].p] = pre[pos];
	}
	else{
		num[pre[pos]]++;
		if(num[pre[pos]] == 1) cur += val[pre[pos]];
		num[mdi[pos].c]--;		
		if(!num[mdi[pos].c]) cur -= val[mdi[pos].c];
		col[mdi[pos].p] = pre[pos];
	}
}

int main(){
	
	read(n),read(m); block = sqrt(n);
	
	for(int i = 1;i <= n;i++) read(col[i]),ddf[i] = col[i];
	for(int i = 1;i <= n;i++) read(val[i]);
	
	for(int i = 1;i <= m;i++){
		int f; read(f);
		if(f == 1){
			read(mdi[++cnt].p),read(mdi[cnt].c);
			pre[cnt] = ddf[mdi[cnt].p];
			ddf[mdi[cnt].p] = mdi[cnt].c;
		}
		if(f == 2){
			read(opt[++tot].l),read(opt[tot].r);
			opt[tot].id = tot,opt[tot].t = cnt;
		}
	}
	
	std :: sort(opt + 1,opt + tot + 1);
	
	for(int i = 1;i <= tot;i++){
		while(R < opt[i].r) add(++R);
		while(R > opt[i].r) del(R--);
		while(L < opt[i].l) del(L++);
		while(L > opt[i].l) add(--L);
		while(T < opt[i].t) addt(++T);
		while(T > opt[i].t) delt(T--);
		ans[opt[i].id] = cur;
	}
	
	for(int i = 1;i <= tot;i++)
		printf("%d\n",ans[i]);
	
	return 0;
}
