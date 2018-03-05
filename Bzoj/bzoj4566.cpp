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
LL ans;

struct Suffix_Automaton{
	int len[maxm],size[maxm],ch[maxm][26],fail[maxm];
	int rnk[maxm],bin[maxm],ddf[maxm],f[maxm];
	int sz,rt,lst;

	Suffix_Automaton(){
		sz = 0; rt = lst = ++sz;
		fail[rt] = 0,len[rt] = 0;
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
		for(int i = sz;i >= 1;i--) size[fail[rnk[i]]] += size[rnk[i]];
	}

	void dfs(char *str,int n){
		int x = rt,sum = 0;
		for(int i = 0;i < n;i++){
			int v = str[i] - 'a';
			if(ch[x][v]) x = ch[x][v],sum++;
			else{
				while(x && !ch[x][v]) x = fail[x];
				if(!x) x = rt;
				else sum = len[x] + 1,x = ch[x][v];
			}
			ans += 1LL * (sum - len[fail[x]]) * size[x];
			ddf[x]++;
		}
		
		for(int i = sz;i >= 1;i--){
			f[fail[rnk[i]]] += f[rnk[i]] + ddf[rnk[i]];
		}
		
		for(int i = 2;i <= sz;i++){
			ans += 1LL * size[i] * f[i] * (len[i] - len[fail[i]]);
		}
		
		printf("%lld\n",ans);
	}
	
}SAM;

int main(){

	scanf("%s",str);
	int len = strlen(str);
	for(int i = 0;i < len;i++) SAM.insert(str[i] - 'a');

	SAM.radixSort(len);

	scanf("%s",str);
	len = strlen(str);

	SAM.dfs(str,len);
	
	return 0;
}
