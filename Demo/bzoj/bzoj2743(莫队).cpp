#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

static const int maxm = 1e6 + 10;

int block,n,c,m,tot;
int A[maxm],cnt[maxm],ans[maxm];

struct Query{
	int l,r,id;
	bool operator < (const Query &Q) const {
		return l / block == Q.l / block ? r < Q.r : l / block < Q.l / block;
	}
}ask[maxm];

inline void read(int &in){
	in = 0; int f = 1;char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

void Del(int pos){
	--cnt[A[pos]];
	if(cnt[A[pos]] == 1) --tot;
}

void Add(int pos){
	++cnt[A[pos]];
	if(cnt[A[pos]] == 2) ++tot;
}

int main(){
	read(n);read(c);read(m); 
	for(int i = 1;i <= n;i++) read(A[i]);
	for(int i = 1;i <= m;i++) read(ask[i].l),read(ask[i].r),ask[i].id = i;
	block = sqrt(n);
	
	sort(ask + 1,ask + m + 1);
	
	int L = 1,R = 0;
	
	for(int i = 1;i <= m;i++){
		while(L < ask[i].l) Del(L++);
		while(L > ask[i].l) Add(--L);
		while(R < ask[i].r) Add(++R);
		while(R > ask[i].r) Del(R--);
		ans[ask[i].id] = tot;
	}
	
	for(int i = 1;i <= m;i++) printf("%d\n",ans[i]);
	
	return 0;
}
