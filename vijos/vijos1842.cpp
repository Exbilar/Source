#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;
static const int mod = 99999997;

template <class T> void read(T &in){
	in = 0; int f = 1; char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

struct node{
	int id,val;
	bool operator < (const node &N) const {
		return val == N.val ? id < N.id : val < N.val;
	}
}A[maxm],B[maxm];

int tr[maxm],tmp[maxm];
int n;

int lowbit(int x){
	return x & -x;
}

void Upt(int k,int v){
	for(int i = k;i <= n;i += lowbit(i)) tr[i] = (tr[i] + v) % mod;
}

int Qry(int k){
	int res = 0;
	for(int i = k;i;i -= lowbit(i)) res = (res + tr[i]) % mod;
	return res;
}

int main(){
	read(n);
	for(int i = 1;i <= n;i++) read(A[i].val),A[i].id = i;
	for(int i = 1;i <= n;i++) read(B[i].val),B[i].id = i;

	std :: sort(A + 1,A + n + 1);
	std :: sort(B + 1,B + n + 1);

	for(int i = 1;i <= n;i++) tmp[B[i].id] = A[i].id;
	
	int ans = 0;
	for(int i = n;i >= 1;i--){
		ans = (ans + Qry(tmp[i] - 1)) % mod;
		Upt(tmp[i],1);
	}	

	printf("%d\n",ans);

	return 0;
}
