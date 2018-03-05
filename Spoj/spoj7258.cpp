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
int m;

struct Suffix_Automaton{
	int len[maxm],size[maxm],fail[maxm],bin[maxm],rnk[maxm];
	int ch[maxm][26];
	int sz,lst,rt;

	Suffix_Automaton(){sz = 0,lst = 0; len[0] = 0,fail[0] = -1;}

	void insert(int v){
		int x = ++sz,cur = lst;
		size[x] = 1,len[x] = len[lst] + 1;
		lst = x;

		while(cur != -1 && !ch[cur][v]) ch[cur][v] = x,cur = fail[cur];
		if(cur == -1) return fail[x] = rt,void();

		int pos = ch[cur][v];
		if(len[pos] == len[cur] + 1) return fail[x] = pos,void();

		int clone = ++sz;
		len[clone] = len[cur] + 1;
		fail[clone] = fail[pos];
		memcpy(ch[clone],ch[pos],sizeof ch[pos]);
		fail[x] = fail[pos] = clone;

		while(cur != -1 && ch[cur][v] == pos) ch[cur][v] = clone,cur = fail[cur];
	}

	void radixSort(int n){
		for(int i = 1;i <= sz;i++) bin[len[i]]++;
		for(int i = 1;i <= n;i++) bin[i] += bin[i - 1];
		for(int i = 1;i <= sz;i++) rnk[bin[len[i]]--] = i;
		for(int i = sz;i >= 1;i--){
			int x = rnk[i];
			size[x] = 1;
			for(int j = 0;j < 26;j++) size[x] += size[ch[x][j]];
		}
	}

	void dfs(int kth){
		int x = rt;
		while(kth){
			for(int i = 0;i < 26;i++){
				if(!ch[x][i]) continue;
				int v = ch[x][i];
				if(kth <= size[v]){
					putchar(i + 'a');
					x = v,kth--;
					break;
				}
				else kth -= size[v];
			}
		}
		putchar(10);
	}
	
}SAM;

int main(){

	scanf("%s",str);
	int len = strlen(str);
	for(int i = 0;i < len;i++) SAM.insert(str[i] - 'a');

	SAM.radixSort(len);
	
	read(m);

	int kth;
	while(m--){
		read(kth);
		SAM.dfs(kth);
	}

	return 0;
}
