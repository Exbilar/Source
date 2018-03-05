#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: set;

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

int id[maxm],RL[maxm];
char str[maxm];
int n,ans;

set<int> S;
typedef set<int> :: iterator itr;

void manacher(){
	int maxR = 0,pos = 0;
	for(int i = 1;i <= n;i++){
		if(i <= maxR) RL[i] = min(maxR - i,RL[pos * 2 - i]);
		else RL[i] = 0;
		while(str[i + RL[i] + 1] == str[i - RL[i]]) RL[i]++;
		if(RL[i] + i > maxR) pos = i,maxR = RL[i] + i;
	}
}

bool cmp(const int &x,const int &y){
	return (x - RL[x]) < (y - RL[y]);
}

int main(){

	read(n);
	scanf("%s",str + 1);
	manacher();
	
	for(int i = 1;i <= n;i++) id[i] = i;

	std :: sort(id + 1,id + n + 1,cmp);
	
	int cur = 1,ans = 0;
	for(int i = 1;i <= n;i++){
		while(cur <= n && id[cur] - RL[id[cur]] <= i) S.insert(id[cur++]);
		itr it = S.upper_bound(i + RL[i] / 2);
		if(it != S.begin()){
			chkmax(ans,((*(--it)) - i) << 2);
		}
	}

	printf("%d\n",ans);

	return 0;
}
