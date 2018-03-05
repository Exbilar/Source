#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

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

char str[maxm],opt[10];
int mask,n,m;

struct LinkCutTree{
	int ch[maxm][2],ftr[maxm],val[maxm],tag[maxm];
	
	int isrt(int x){
		return ch[ftr[x]][0] != x && ch[ftr[x]][1] != x;
	}

	int get(int x){
		return ch[ftr[x]][1] == x;
	}

	void rotate(int x){
		int fa = ftr[x],gnd = ftr[fa],f = get(x);
		if(!isrt(fa)) ch[gnd][get(fa)] = x;
		ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
		ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
	}

	void pushtag(int x,int v){
		val[x] += v,tag[x] += v;
	}

	void pushdown(int x){
		if(tag[x]){
			if(ch[x][0]) pushtag(ch[x][0],tag[x]);
			if(ch[x][1]) pushtag(ch[x][1],tag[x]);
			tag[x] = 0;
		}
	}
	
	void pushbtm(int x){
		if(!isrt(x)) pushbtm(ftr[x]);
		pushdown(x);
	}

	void splay(int x){
		pushbtm(x);
		for(int fa = x;!isrt(x);rotate(x))
			if(!isrt(fa = ftr[x])) rotate(get(fa) == get(x) ? fa : x);
	}

	void access(int x){
		for(int y = 0;x;y = x,x = ftr[x])
			splay(x),ch[x][1] = y;
	}

	void link(int x,int y){
		ftr[x] = y;
		access(y),splay(y);
		pushtag(y,val[x]);
	}

	void cut(int x){
		access(x),splay(x);
		pushtag(ch[x][0],-val[x]);
		ftr[ch[x][0]] = 0,ch[x][0] = 0;
	}

	void setv(int x,int v){
		val[x] = v;
	}

	int getv(int x){
		return val[x];
	}
	
}LCT;

struct Suffix_Automaton{
	int len[maxm],size[maxm],fail[maxm],ch[maxm][26];
	int sz,rt,lst;

	Suffix_Automaton(){
		sz = 0; rt = lst = ++sz;
		len[rt] = 0; fail[rt] = 0;
	}
	
	void insert(int v){
		int x = ++sz,cur = lst;
		len[x] = len[lst] + 1; size[x] = 1;
		lst = x;
		
		LCT.setv(x,1);

		while(cur && !ch[cur][v]) ch[cur][v] = x,cur = fail[cur];
		if(!cur) return fail[x] = rt,LCT.link(x,rt),void();

		int pos = ch[cur][v];
		if(len[pos] == len[cur] + 1)
			return fail[x] = pos,LCT.link(x,pos),void();
		
		int clone = ++sz;
		fail[clone] = fail[pos];
		LCT.link(clone,fail[pos]);
		len[clone] = len[cur] + 1;
		memcpy(ch[clone],ch[pos],sizeof ch[pos]);
		
		fail[x] = fail[pos] = clone;
		LCT.cut(pos); LCT.link(pos,clone); LCT.link(x,clone);
		while(cur && ch[cur][v] == pos)
			ch[cur][v] = clone,cur = fail[cur];
	}

	int Query(char *str,int n){
		int x = rt;
		for(int i = 0;i < n;i++){
			int v = str[i] - 'A';
			if(ch[x][v]) x = ch[x][v];
			else return 0;
		}
		LCT.pushbtm(x);
		return LCT.getv(x);
	}

	void insertStr(char *str,int n){
		for(int i = 0;i < n;i++) insert(str[i] - 'A');
	}
	
}SAM;

void decodeStr(char *str,int mask,int n){
	for(int i = 0;i < n;i++){
		mask = (mask * 131 + i) % n;
		std :: swap(str[i],str[mask]);
	}
}

int main(){

	read(m); scanf("%s",str);
	SAM.insertStr(str,strlen(str));

	int lstans = 0;
	
	while(m--){
		scanf("%s%s",opt,str);
		int len = strlen(str);
		decodeStr(str,mask,len);
		if(opt[0] == 'A') SAM.insertStr(str,len);
		else printf("%d\n",lstans = SAM.Query(str,len)),mask ^= lstans;
	}
	
	return 0;
}
