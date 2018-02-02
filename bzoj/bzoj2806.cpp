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
int n,m;

struct Suffix_Automaton{
	int ch[maxm][2],fail[maxm],size[maxm],len[maxm],ddf[maxm];
	int que[maxm],f[maxm];
	int lst,rt,sz;

	Suffix_Automaton(){
		sz = 0; lst = rt = ++sz;
		len[rt] = fail[rt] = 0;
	}

	void insert(int v){
		int x = ++sz,cur = lst;
		len[x] = len[lst] + 1; size[x] = 1;
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

	void dfs(char *str,int n){
		int x = rt,sum = 0;
		for(register int i = 1;i <= n;i++){
			int v = str[i] - '0';
			if(ch[x][v]) x = ch[x][v],sum++;
			else{
				while(x && !ch[x][v]) x = fail[x];
				if(!x) x = rt,sum = 0;
				else sum = len[x] + 1,x = ch[x][v];
			}
			ddf[i] = sum;
		}
	}

	bool cmp(int i,int j){
		return f[i] - i < f[j] - j;
	}

	bool chk(char *str,int n,int L){
		memset(f,0,sizeof f);
		int head = 1,tail = 0;

		for(register int i = 1;i <= n;i++){
			f[i] = f[i - 1];
			if(i - L < 0) continue;
			while(head <= tail && cmp(que[tail],i - L)) tail--;
			que[++tail] = i - L;
			while(head <= tail && que[head] < i - ddf[i]) head++;
			if(head <= tail) chkmax(f[i],f[que[head]] + i - que[head]);
		}

		return f[n] * 10 >= n * 9;
	}

	void solve(char *str,int n){
		int l = 1,r = n,res = 0;
		dfs(str,n);
		while(l <= r){
			int mid = (l + r) >> 1;
			if(chk(str,n,mid)) res = mid,l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n",res);
	}
	
}SAM;

int main(){

	freopen("bzoj2806.in","r",stdin);
	
	read(m); read(n);

	for(register int ovo = 1;ovo <= n;ovo++){
		scanf("%s",str + 1);
		int len = strlen(str + 1);
		
		SAM.lst = SAM.rt;
		for(int i = 1;i <= len;i++) SAM.insert(str[i] - '0');
	}

	while(m--){
		scanf("%s",str + 1);
		int len = strlen(str + 1);
		SAM.solve(str,len);
	}

	return 0;
}
