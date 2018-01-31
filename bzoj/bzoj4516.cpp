#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: map;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 2e6 + 10;

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

int A[maxm];

int n;
LL ans;

struct Suffix_Automaton{
	int len[maxm],size[maxm],fail[maxm],bin[maxm],rnk[maxm];
	map<int,int> ch[maxm];
	int sz,lst;

	Suffix_Automaton(){sz = 0,lst = 0; len[0] = 0,fail[0] = -1;}

	void insert(int v){
		int x = ++sz,cur = lst;
		len[x] = len[lst] + 1,size[x] = 1;
		lst = x;

		while(cur != -1 && !ch[cur][v]) ch[cur][v] = x,cur = fail[cur];
		if(cur == -1) return fail[x] = 0,ans += len[x] - len[fail[x]],void();

		int pos = ch[cur][v];
		if(len[pos] == len[cur] + 1)
			return fail[x] = pos,ans += len[x] - len[fail[x]],void();

		int clone = ++sz;
		len[clone] = len[cur] + 1;
		fail[clone] = fail[pos];
		ch[clone] = ch[pos];
		
		fail[x] = fail[pos] = clone;
		while(cur != -1 && ch[cur][v] == pos)
			ch[cur][v] = clone,cur = fail[cur];
		
		ans += len[x] - len[fail[x]];
	}
	
}SAM;

int main(){
		
	read(n);
	for(int i = 1;i <= n;i++){
		read(A[i]);
		SAM.insert(A[i]);
		printf("%lld\n",ans);
	}

	return 0;
}
