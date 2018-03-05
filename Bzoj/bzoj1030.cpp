#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: queue;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 6000 + 10;
static const int maxn = 100 + 10;
static const int mod = 10007;

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

int add(int x,int y){
	x += y; if(x >= mod) x -= mod;
	return x;
}

int minus(int x,int y){
	x -= y; if(x < 0) x += mod;
	return x;
}

int mul(int x,int y){
	x = (x + mod) % mod;
	y = (y + mod) % mod;
	return (x * y) % mod;
}

struct AC_Automaton{
	int val[maxm],ch[maxm][26],fail[maxm],f[maxn][maxm];
	int sz;

	queue<int> que;
	
	void insert(char *str){
		int len = strlen(str),cur = 0;
		for(int i = 0;i < len;i++){
			int v = str[i] - 'A';
			if(!ch[cur][v]) ch[cur][v] = ++sz;
			cur = ch[cur][v];
		}
		val[cur] = 1;
	}

	void getFail(){
        for(int i = 0;i < 26;i++){
            if(ch[0][i]) que.push(ch[0][i]),fail[ch[0][i]] = 0;
			else ch[0][i] = ++sz,que.push(ch[0][i]),fail[ch[0][i]] = 0;
        }
		
        while(!que.empty()){
            int x = que.front(); que.pop();
			val[x] |= val[fail[x]];
            for(int i = 0;i < 26;i++){
                int v = ch[x][i];
                if(ch[x][i]) fail[v] = ch[fail[x]][i],que.push(v);
                else ch[x][i] = ch[fail[x]][i];
            }
        }
    }
	
	void solve(){
		int ans1 = 1,ans2 = 0;
		f[0][0] = 1;
		
		for(int i = 1;i <= m;i++){
			for(int j = 0;j <= sz;j++){
				if(!val[j] && f[i - 1][j] != 0){
					for(int k = 0;k < 26;k++){
						if(!val[ch[j][k]]) f[i][ch[j][k]] = add(f[i][ch[j][k]],f[i - 1][j]);
					}
				}
			}
		}
		
		for(int i = 1;i <= m;i++) ans1 = mul(ans1,26);
		
		for(int i = 0;i <= sz;i++)
			if(!val[i]) ans2 = add(ans2,f[m][i]);
		
		printf("%d\n",minus(ans1,ans2));
	}
	
}AC;

char str[maxn];

int main(){
	read(n),read(m);
	for(int i = 1;i <= n;i++) scanf("%s",str),AC.insert(str);
	AC.getFail();
	AC.solve();

	return 0;
}
