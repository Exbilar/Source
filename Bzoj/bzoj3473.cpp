#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: string;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 2e5 + 10;

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

int n,k;

struct Suffix_Automaton{
	int len[maxm],size[maxm],fail[maxm],ch[maxm][26];
	int rnk[maxm],bin[maxm],ddf[maxm],cnt[maxm],f[maxm];
	int sz,rt,lst;

	Suffix_Automaton(){
		sz = 0; rt = lst = ++sz;
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

	void radixSort(){
		for(int i = 1;i <= sz;i++) bin[len[i]]++;
		for(int i = 1;i <= sz;i++) bin[i] += bin[i - 1];
		for(int i = 1;i <= sz;i++) rnk[bin[len[i]]--] = i;
	}

	void dfs(int pos){
		int x = rt;
		for(int i = 0;i < str[pos].size();i++){
			x = ch[x][str[pos][i] - 'a'];
			int cur = x;
			while(cur && ddf[cur] != pos)
				ddf[cur] = pos,cnt[cur]++,cur = fail[cur];
		}
	}
	
	void solve(){
		for(int i = 1;i <= n;i++) dfs(i);
		for(int i = 1;i <= sz;i++){
			int x = rnk[i];
			f[x] = f[fail[x]] + (cnt[x] >= k ? len[x] - len[fail[x]] : 0);
		}
		for(int i = 1;i <= n;i++){
			int x = rt; LL ans = 0;
			for(int j = 0;j < str[i].size();j++){
				x = ch[x][str[i][j] - 'a'];
				ans += f[x];
			}
			printf("%lld ",ans);
		}
	}

}SAM;

int main(){

    read(n),read(k);

    for(int i = 1;i <= n;i++){
        scanf("%s",chr); str[i] = string(chr);
		SAM.lst = SAM.rt;
        for(int j = 0;j < strlen(chr);j++){
            SAM.insert(chr[j] - 'a');
        }
    }

	SAM.radixSort();
	SAM.solve();
	
	return 0;
}
