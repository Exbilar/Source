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

struct Suffix_Automaton{
	int len[maxm],fail[maxm],ch[maxm][26];
	int bin[maxm],rnk[maxm];
	
	LL sum[maxm],size[maxm];
	
	int sz,rt,lst;

	Suffix_Automaton(){
		sz = 0; rt = lst = ++sz;
		len[rt] = 0,fail[rt] = 0;
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

	void radixSort(int n){
		for(int i = 1;i <= sz;i++) bin[len[i]]++;
		for(int i = 1;i <= n;i++) bin[i] += bin[i - 1];
		for(int i = 1;i <= sz;i++) rnk[bin[len[i]]--] = i;
	}

	LL getAns(){
		LL res = 0;
		for(int i = sz;i >= 1;i--){
			int x = rnk[i],y = fail[rnk[i]];
			res += 1LL * len[y] * size[y] * size[x];
			size[y] += size[x];
		}
		return res;
	}

	void solve(int n){
		LL ans = 0;
		for(int i = 1;i <= n;i++) sum[i] = sum[i - 1] + i;
		for(int i = 1;i <= n;i++) ans += 1LL * (n - i) * i + (sum[n] - sum[i]);
		printf("%lld\n",ans - (getAns() << 1));
	}

}SAM;

int main(){

	scanf("%s",str);
	int len = strlen(str);

	for(int i = len - 1;i >= 0;i--) SAM.insert(str[i] - 'a');

	SAM.radixSort(len);
	SAM.solve(len);

	return 0;
}
