#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1000000 + 10;

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

struct Segment{
	int l,r;
	Segment(){}
	Segment(int _,int __){l = _,r = __;}
	bool operator < (const Segment &rhs) const {
		return r < rhs.r;
	}
}L[maxm];

char str[maxm],_str[maxm];
int RL[maxm],bit[maxm];
int n,len,sz,ans;

int lowbit(int x){
	return x & -x;
}

void Upt(int k,int v){
	for(int i = k;i;i -= lowbit(i)) chkmin(bit[i],v);
}

int Qry(int k){
	if(!k) return 0;
	
	int res = INF;
	for(int i = k;i <= n;i += lowbit(i)) chkmin(res,bit[i]);
	return res;
}

void pretreat(){
	len = n << 1 | 1;
	for(int i = 1;i <= n;i++){
		str[i << 1] = _str[i],str[i << 1 | 1] = '#';
	}
	str[0] = '+',str[1] = '#',str[len + 1] = '-';
}

void insert(int l,int r){
	l = (l >> 1) + 1,r = (r >> 1) - 1;
	if(l > r) return ;
	L[++sz] = Segment(l,r);
}

void manacher(){
	pretreat();
	int maxR = 0,pos = 0;
	for(int i = 1;i <= len;i++){
		if(i < maxR) RL[i] = min(maxR - i,RL[pos * 2 - i]);
		else RL[i] = 1;
		while(str[i - RL[i]] == str[i + RL[i]]) RL[i]++;
		insert(i - RL[i],i + RL[i]);
		if(RL[i] + i > maxR) maxR = RL[i] + i,pos = i;
	}
}

int main(){
	
	while(scanf("%s",_str + 1) != EOF){
		n = strlen(_str + 1); sz = 0; ans = INF;
		for(int i = 1;i <= n;i++) bit[i] = INF;
		manacher();
		
		std :: sort(L + 1,L + sz + 1);

		for(int i = 1;i <= sz;i++){
			int tmp = Qry(L[i].l - 1) + 1;
			Upt(L[i].r,tmp);
			if(L[i].r == n) chkmin(ans,tmp);
		}
		printf("%d\n",ans - 1);
	}

	return 0;
}
