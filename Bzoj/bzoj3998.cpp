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
int typ,kth;

struct Suffix_Automaton{
	int len[maxm],size[maxm],fail[maxm],ch[maxm][26];
	int rnk[maxm],bin[maxm],rsize[maxm];
	int sz,rt,lst;

	Suffix_Automaton(){
		sz = 0; rt = lst = ++sz;
		fail[rt] = 0,len[rt] = 0;
	}

	void insert(int v){
		int x = ++sz,cur = lst;
		len[x] = len[lst] + 1,rsize[x] = 1,size[x] = 1;
		lst = x;

		while(cur && !ch[cur][v]) ch[cur][v] = x,cur = fail[cur];
		if(!cur) return fail[x] = rt,void();

		int pos = ch[cur][v];
		if(len[pos] == len[cur] + 1) return fail[x] = pos,void();

		int clone = ++sz;
		len[clone] = len[cur] + 1;
		fail[clone] = fail[pos];
		memcpy(ch[clone],ch[pos],sizeof ch[pos]);

		fail[x] = fail[pos] = clone;
		while(cur && ch[cur][v] == pos) ch[cur][v] = clone,cur = fail[cur];
	}

	void radixSort(int n){
		for(int i = 1;i <= sz;i++) bin[len[i]]++;
		for(int i = 1;i <= n;i++) bin[i] += bin[i - 1];
		for(int i = 1;i <= sz;i++) rnk[bin[len[i]]--] = i;
	}

	void getSize(int typ){
		for(int i = sz;i >= 1;i--){
			int x = rnk[i];
			if(typ == 0) rsize[x] = 1;
			else rsize[fail[x]] += rsize[x];
		}
		for(int i = sz;i >= 1;i--){
			int x = rnk[i];
			size[x] = rsize[x];
			for(int j = 0;j < 26;j++) size[x] += size[ch[x][j]];
		}
	}
	
	void dfs(int kth,int typ){
		if(size[rt] < kth) return puts("-1"),void();
		int x = rt;
		while(kth){
			for(int i = 0;i < 26;i++){
				if(!ch[x][i]) continue;
				int v = ch[x][i];
				if(kth <= size[v]){
					putchar('a' + i);
					kth -= rsize[v];
					x = ch[x][i];
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
	read(typ),read(kth);

	int len = strlen(str);
	for(int i = 0;i < len;i++) SAM.insert(str[i] - 'a');

	SAM.radixSort(len);
	SAM.getSize(typ);

	SAM.dfs(kth,typ);
	
	return 0;
}
