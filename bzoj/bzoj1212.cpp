#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: pair;
using std :: queue;
using std :: stack;
using std :: make_pair;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1000000 + 10;
static const int maxn = 1000 + 10;

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

int n,m;
int f[maxm];

struct AC_Automaton{
	int val[maxn],fail[maxn],ch[maxn][26];
	int sz;

	queue<int> que;
	

    void insert(char *str){
        int len = strlen(str),cur = 0;
        for(int i = 0;i < len;i++){
            int v = str[i] - 'a';
            if(!ch[cur][v]) ch[cur][v] = ++sz;
            cur = ch[cur][v];
        }
        val[cur] = len;
    }

    void getFail(){
        for(int i = 0;i < 26;i++)
            if(ch[0][i]) que.push(ch[0][i]),fail[ch[0][i]] = 0;
        
        while(!que.empty()){
            int x = que.front(); que.pop();
            for(int i = 0;i < 26;i++){
                int v = ch[x][i];
                if(ch[x][i]) fail[v] = ch[fail[x]][i],que.push(v);
                else ch[x][i] = ch[fail[x]][i];
            }
        }
    }

	int solve(char *str){
		clr(f),f[0] = 1;
		int len = strlen(str + 1),cur = 0,res = 0;
		
		for(int i = 1;i <= len;i++){
			cur = ch[cur][str[i] - 'a'];
			for(int v = cur;v;v = fail[v]){
				if(!val[v]) continue;
				if(i >= val[v]) f[i] |= f[i - val[v]];
				if(f[i]) chkmax(res,i);
			}
		}
		
		return res;
	}
	
}AC;

char str[maxm];

int main(){   
	
	read(n),read(m);
	for(int i = 1;i <= n;i++) scanf("%s",str),AC.insert(str);
	AC.getFail();   
	
	while(m--){
		scanf("%s",str + 1);
		printf("%d\n",AC.solve(str));
	}
	
	return 0;
}
