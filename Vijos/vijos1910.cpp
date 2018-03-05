#include <cstdio>
#include <algorithm>

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;
static const int mod = 1e9 + 7;

template <class T> void read(T &in){
	in = 0; int f = 1; char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = (in * 10 + ch - '0') % mod;
	in = in * f;	
	in = (in + mod) % mod;
}

LL A[100 + 10],ans[maxm];
int n,m;

bool chk(LL x){
	LL res = 0,cur = 1;
	for(register int i = 0;i <= n;i++){
		res = (res + A[i] * cur) % mod;
		cur = (cur * x) % mod;
	}
	return res == 0;
}

int main(){
	scanf("%d%d",&n,&m);
	for(register int i = 0;i <= n;i++) read(A[i]);

	for(register int i = 1;i <= m;i++){
		if(chk(i)) ans[++ans[0]] = i;
	}	

	for(register int i = 0;i <= ans[0];i++) printf("%lld\n",ans[i]);
	
	return 0;
}
