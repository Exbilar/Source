#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 100000 + 10;

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

int fst[maxm],nxt[maxm << 1],to[maxm << 1],ddf[maxm],fnl[maxm],ans[maxm];
char str[maxm];
int cnt,sz,m;

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
}

struct Opt{
	int x,y,id;
	bool operator < (const Opt &opt) const {
		return y < opt.y;
	}
}opt[maxm];

struct BIT{
	int bit[maxm];
	int n;
	
	int lowbit(int x){
		return x & -x;
	}

	void Upt(int k,int v){
		for(int i = k;i <= n;i += lowbit(i)) bit[i] += v;
	}

	int Qry(int k){
		int res = 0;
		for(int i = k;i;i -= lowbit(i)) res += bit[i];
		return res;
	}
	
}Bit;

struct AC_Automaton{
	int ch[maxm][26],fail[maxm],que[maxm],ftr[maxm],idx[maxm];
	int sz,cnt;
	
	void build(char *str){
		memset(ftr,-1,sizeof ftr);
		int len = strlen(str),x = 0;
		
		for(int i = 0;i < len;i++){
			if(str[i] == 'B') x = ftr[x];
			if(str[i] == 'P') idx[++cnt] = x;
			if(str[i] != 'B' && str[i] != 'P'){
				int v = str[i] - 'a';
				if(!ch[x][v]) ch[x][v] = ++sz;
				ftr[ch[x][v]] = x;
				x = ch[x][v];
			}
		}
	}
	
	void getFail(){
		int head = 1,tail = 0;
		for(int i = 0;i < 26;i++)
			if(ch[0][i]) que[++tail] = ch[0][i],fail[ch[0][i]] = 0;
		
		while(head <= tail){
			int x = que[head++];
			for(int i = 0;i < 26;i++){
				int v = ch[x][i];
				if(ch[x][i]) fail[que[++tail] = v] = ch[fail[x]][i];
				else ch[x][i] = ch[fail[x]][i];
			}
		}
		for(int i = 1;i <= sz;i++) ins(i,fail[i]);
	}
	
	void solve(char *str){
		int len = strlen(str),x = 0,cur = 0,pos = 1;
		for(int i = 0;i < len;i++){
			if(str[i] == 'B') Bit.Upt(ddf[x],-1),x = ftr[x];
			if(str[i] == 'P'){
				cur++;
				while(cur == opt[pos].y){
					ans[opt[pos].id] = Bit.Qry(fnl[idx[opt[pos].x]]) - Bit.Qry(ddf[idx[opt[pos].x]] - 1);
					pos++;
				}
			}
			if(str[i] != 'B' && str[i] != 'P'){
				int v = str[i] - 'a';
				x = ch[x][v];
				Bit.Upt(ddf[x],1);
			}
		}
	}
	
}AC;

void dfs(int x,int fa){
	ddf[x] = ++sz;
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(v == fa) continue;
		dfs(v,x);
	}
	fnl[x] = sz;
}

void solve(){
	AC.build(str);
	AC.getFail();
	dfs(0,-1);
	
	Bit.n = strlen(str) + 1;
	
	AC.solve(str);
	
	for(int i = 1;i <= m;i++) printf("%d\n",ans[i]);
}

int main(){
	
	scanf("%s",str);
	read(m);

	for(int i = 1;i <= m;i++)
		read(opt[i].x),read(opt[i].y),opt[i].id = i;

	std :: sort(opt + 1,opt + m + 1);

	solve();
	
	return 0;
}
