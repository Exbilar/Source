#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: queue;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 30000 + 10;

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

int ind[maxm],nxt[maxm],fst[maxm],to[maxm];
char str[maxm];
int cnt,n;

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	ind[t]++;
}

struct AC_Automaton{
	int val[maxm],fail[maxm],ch[maxm][2];
	int sz;

	queue<int> que;

	void insert(char *str){
		int len = strlen(str),x = 0;
		for(int i = 0;i < len;i++){
			int v = str[i] - '0';
			if(!ch[x][v]) ch[x][v] = ++sz;
			x = ch[x][v];
		}
		val[x] = 1;
	}

	void getFail(){
		for(int i = 0;i < 2;i++)
			if(ch[0][i]) que.push(ch[0][i]),fail[ch[0][i]] = 0;
		
		while(!que.empty()){
			int x = que.front(); que.pop();
			val[x] |= val[fail[x]];
			for(int i = 0;i < 2;i++){
				int v = ch[x][i];
				if(ch[x][i]) fail[v] = ch[fail[x]][i],que.push(v);
				else ch[x][i] = ch[fail[x]][i];
			}
		}
		for(int i = 0;i <= sz;i++)
			for(int j = 0;j < 2;j++)
				if(!val[i] && !val[ch[i][j]]) ins(i,ch[i][j]);
	}

	void solve(){
		int res = 0;
		
		for(int i = 0;i <= sz;i++)
			if(!ind[i]) que.push(i);		
		
		while(!que.empty()){
			int x = que.front(); que.pop(); res++;
			for(int u = fst[x];u;u = nxt[u]){
				int v = to[u];
				ind[v]--;
				if(!ind[v]) que.push(v);
			}
		}
		
		if(res != sz + 1) puts("TAK");
		else puts("NIE");
	}
	
}AC;

int main(){
	
	read(n);
	for(int i = 1;i <= n;i++) scanf("%s",str),AC.insert(str);
	AC.getFail();
	AC.solve();
	
	return 0;
}
