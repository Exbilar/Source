#include <bitset>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

static const int maxm = 1e5 + 10;

bitset<maxm> r,f,g;

int num[maxm],A[maxm],ans[maxm];
int block,n,m,smax,L = 1,R = 0;

struct Qry{
	int l,r,x,id,opt;
	bool operator < (const Qry &Q) const {
		return l / block == Q.l / block ? r < Q.r : l / block < Q.l / block;
	}
}ask[maxm];

int calc(int opt,int x){
	if(opt == 1){
		g = f,g >>= x,g &= f;
		if(g.count()) return 1;
		return 0;
	}
	if(opt == 2){
		g = r,g >>= (smax - x),g &= f;
		if(g.count()) return 1;
		return 0;
	}
	if(opt == 3){
		int up = sqrt(x);
		for(int i = 1;i <= up;i++)
			if(x % i == 0 && f[i] && f[x / i]) return 1;
		return 0;
	}
}

void Upt(int pos,int val){
	if(val == 1) {
		num[A[pos]]++;
		if(num[A[pos]] == 1) f[A[pos]] = 1,r[smax - A[pos]] = 1;
	}
	if(val == -1) {
		num[A[pos]]--;
		if(!num[A[pos]]) f[A[pos]] = 0,r[smax - A[pos]] = 0;
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
		scanf("%d",&A[i]),smax = std :: max(smax,A[i]);
	block = std :: sqrt(n);
	for(int i = 1;i <= m;i++){
		scanf("%d%d%d%d",&ask[i].opt,&ask[i].l,&ask[i].r,&ask[i].x),ask[i].id = i;
		smax = std :: max(smax,ask[i].x);
	}
	sort(ask + 1,ask + m + 1);
		
	for(int i = 1;i <= m;i++){
		while(R < ask[i].r) Upt(++R,1);
		while(R > ask[i].r) Upt(R--,-1);
		while(L < ask[i].l) Upt(L++,-1);
		while(L > ask[i].l) Upt(--L,1);
		ans[ask[i].id] = calc(ask[i].opt,ask[i].x);
	}

	for(int i = 1;i <= m;i++) puts(ans[i] ? "yuno" : "yumi");
	
	return 0;
}
