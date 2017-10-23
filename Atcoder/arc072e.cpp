#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

static const int maxm = 2e6 + 10;
static const int INF = 1 << 30;

LL A[maxm],pre[maxm],suf[maxm];
LL N,D,Q,cur,x;

int main(){
	scanf("%lld%lld",&N,&D);
	
	for(int i = 1;i <= N;i++) scanf("%lld",&A[i]);
	
	pre[0] = D;
	for(int i = 1;i <= N;i++){
		if(cur < D && abs(D - cur) > abs(D - cur - A[i])){
			pre[i] = abs(D - cur - A[i]);
			cur += A[i];
		}
		else if(cur > D && abs(D - cur) > abs(cur - A[i] - D)){
			pre[i] = abs(cur - A[i] - D);
			cur -= A[i];
		}
		else pre[i] = pre[i - 1];
	}

	memset(suf,0x3f,sizeof suf);
	
	suf[N] = 1;
	for(int i = N - 1;i >= 1;i--){
		if(A[i + 1] / 2 >= suf[i + 1]) suf[i] = suf[i + 1];
		else suf[i] = suf[i + 1] + A[i + 1];
	}
	
	scanf("%lld",&Q);
	for(int i = 1;i <= Q;i++){
		scanf("%lld",&x);
		if(suf[x] <= pre[x - 1]) puts("YES");
		else puts("NO");
	}
	
	return 0;
}
