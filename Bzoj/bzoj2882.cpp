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

struct Suffix_Automaton{
	int size[maxm],len[maxm],fail[maxm];
	map<int,int> ch[maxm];
	int sz,rt,lst;

	Suffix_Automaton(){lst = 0,sz = 0,len[0] = 0,fail[0] = -1;}

	void insert(int v){
		int x = ++sz,cur = lst;
		size[x] = 1,len[x] = len[lst] + 1;
		lst = x;

		while(cur != -1 && !ch[cur][v]) ch[cur][v] = x,cur = fail[cur];
		if(cur == -1) return fail[x] = rt,void();

		int pos = ch[cur][v];
		if(len[cur] + 1 == len[pos]) return fail[x] = pos,void();

		int clone = ++sz;
		len[clone] = len[cur] + 1;
		fail[clone] = fail[pos];
		ch[clone] = ch[pos];
		fail[x] = fail[pos] = clone;
		while(cur != -1 && ch[cur][v] == pos)
			ch[cur][v] = clone,cur = fail[cur];
	}

	void solve(){
		int cur = rt;
		for(int i = 1;i <= n;i++){
			printf("%d%c",ch[cur].begin() -> first," \n"[i == n]);
			cur = ch[cur].begin() -> second;
		}
	}
	
}SAM;

int main(){

	read(n);
	for(int i = 1;i <= n;i++) read(A[i]),A[i + n] = A[i];

	for(int i = 1;i <= (n << 1);i++) SAM.insert(A[i]);

	SAM.solve();

	return 0;
}
