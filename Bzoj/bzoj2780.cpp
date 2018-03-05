#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: string;

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

char chr[maxm];
string str[maxm];
int n,m;

struct Suffix_Automaton{
	int len[maxm],size[maxm],fail[maxm],ch[maxm][26],ddf[maxm],cnt[maxm];
	int lst,rt,sz;

	Suffix_Automaton(){
		sz = 0; lst = rt = ++sz;
		len[rt] = fail[rt] = 0;
	}

	void insert(int v){
		int x = ++sz,cur = lst;
		len[x] = len[lst] + 1,size[x] = 1;
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

	void dfs(string str,int n,int pos){
		int x = rt;
		for(int i = 0;i < n;i++){
			x = ch[x][str[i] - 'a'];
			int cur = x;
			while(cur && ddf[cur] != pos)
				ddf[cur] = pos,cnt[cur]++,cur = fail[cur];
		}
	}

	int solve(char *str,int n){
		int x = rt;
		for(int i = 0;i < n;i++){
			int v = str[i] - 'a';
			if(ch[x][v]) x = ch[x][v];
			else return 0;
		}
		return cnt[x];
	}

	void insertStr(char *str,int n){
		for(int i = 0;i < n;i++) insert(str[i] - 'a');
	}
	
}SAM;

int main(){

	read(n),read(m);

	for(int i = 1;i <= n;i++){
		scanf("%s",chr);
		str[i] = string(chr);
		SAM.lst = SAM.rt;
		SAM.insertStr(chr,strlen(chr));
	}

	for(int i = 1;i <= n;i++){
		int len = str[i].size();
		SAM.dfs(str[i],len,i);
	}
	
	while(m--){
		scanf("%s",chr);
		printf("%d\n",SAM.solve(chr,strlen(chr)));
	}

	return 0;
}
