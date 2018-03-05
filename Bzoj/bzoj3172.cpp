#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1000000 + 10;

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
int idx[maxm],que[maxm];
int n;

struct AC_Automaton{
	int fail[maxm],ch[maxm][26],val[maxm];
	int sz;
	
	void insert(char *str,int pos){
		int len = strlen(str),x = 0;
		for(int i = 0;i < len;i++){			
			int v = str[i] - 'a';
			if(!ch[x][v]) ch[x][v] = ++sz;
			x = ch[x][v];
			val[x]++;
		}
		idx[pos] = x;
	}

	void getFail(){
		int head = 1,tail = 0;
		for(int i = 0;i < 26;i++)
			if(ch[0][i]) que[++tail] = ch[0][i],fail[ch[0][i]] = 0;
		
		while(head <= tail){
			int x = que[head++];
			for(int i = 0;i < 26;i++){
				int v = ch[x][i];
				if(ch[x][i]) fail[v] = ch[fail[x]][i],que[++tail] = v;
				else ch[x][i] = ch[fail[x]][i];
			}
		}

		for(int i = tail;i >= 1;i--) val[fail[que[i]]] += val[que[i]];
	}
	
}AC;

int main(){
	
	read(n);
	for(int i = 1;i <= n;i++) scanf("%s",str),AC.insert(str,i);

	AC.getFail();

	for(int i = 1;i <= n;i++) printf("%d\n",AC.val[idx[i]]);
	
	return 0;
}
