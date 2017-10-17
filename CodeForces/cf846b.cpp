#include <bits/stdc++.h>

static const int INF = 1 << 30;
static const int maxm = 1e6 + 10;

template <class T> void read(T &in){
	in = 0; int f = 1 ;char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

using std :: vector;

vector<int> get[maxm];
int A[maxm],num[maxm];
int n,m,k;

int main(){
	read(n),read(k),read(m);
	for(int i = 1;i <= n;i++)
		read(A[i]),get[A[i] % m].push_back(A[i]),num[A[i] % m]++;
	
	for(int i = 0;i < m;i++){
		if(num[i] >= k){
			puts("Yes");
			for(int j = 0;j < k;j++) printf("%d ",get[i][j]);
			putchar(10);
			return 0;
		}
	}	
	puts("No");
	
	return 0;
}
