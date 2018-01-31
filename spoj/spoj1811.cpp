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

char str1[maxm],str2[maxm];

struct Suffix_Automaton{
	int len[maxm],size[maxm],fail[maxm],ch[maxm][26];
	int sz,rt,lst;

	Suffix_Automaton(){sz = 0,lst = 0,rt = 0; fail[0] = -1,len[0] = 0;}

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
	
}SAM;

int main(){
	
	scanf("%s",str1);
	scanf("%s",str2);

	int len1 = strlen(str1);
	int len2 = strlen(str2);
	
	for(int i = 0;i < len1;i++) SAM.insert(str1[i] - 'a');

	int ans = 0,sum = 0,x = SAM.rt;
	
	for(int i = 0;i < len2;i++){
		int v = str2[i] - 'a';
		if(SAM.ch[x][v]) chkmax(ans,++sum),x = SAM.ch[x][v];
		else{
			while(x != -1 && !SAM.ch[x][v]) x = SAM.fail[x];
			if(x == -1) x = SAM.rt,sum = 0;
			else sum = SAM.len[x] + 1,x = SAM.ch[x][v],chkmax(ans,sum);
		}
	}

	printf("%d\n",ans);

	return 0;
}
