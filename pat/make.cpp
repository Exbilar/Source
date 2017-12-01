#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

#define FOR(i, a, b) for (int i = (a), i##_END_ = (b); i <= i##_END_; i++)
#define DNF(i, a, b) for (int i = (a), i##_END_ = (b); i >= i##_END_; i--)

template <typename Tp> void in(Tp &x) {
	char ch = getchar(), f = 1; x = 0;
	while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if (ch == '-') f = -1, ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= f;
}

template <typename Tp> bool chkmax(Tp &x, Tp y) {return x > y ? 0 : (x=y,1);}
template <typename Tp> bool chkmin(Tp &x, Tp y) {return x < y ? 0 : (x=y,1);}
template <typename Tp> Tp Max(Tp x, Tp y) {return x > y ? x : y;}
template <typename Tp> Tp Min(Tp x, Tp y) {return x < y ? x : y;}

const int MAXN = 300010;

int n,m;

int main(){

	srand(time(NULL));
	
	n = 1000,m = 1000;
	printf("%d %d\n",n,m);
	for(int i = 1;i <= n;i++) printf("%d ",rand() % n + 1);
	putchar(10);

	for(int i = 1;i <= n;i++) printf("%d ",rand() % 10000 + 1);
	putchar(10);

	for(int i = 1;i <= m;i++){
		int opt = rand() % 2 + 1;
		if(opt == 1){
			int p = rand() % n + 1;
			int c = rand() % n + 1;
			printf("%d %d %d\n",opt,p,c);
		}
		if(opt == 2){
			int r = rand() % n + 1;
			int l = rand() % r + 1;
			printf("%d %d %d\n",opt,l,r);
		}
	}
	
	return 0;
}
