#include <bits/stdc++.h>

using namespace std;

static const int maxm = 1e6 + 10;

int A[maxm],n,m;

int main(){
	srand(time(NULL));

	n = 20 + 1;
	m = 1000 + 1;

	printf("%d %d\n",n,m);

	for(int i = 1;i <= n;i++){
		printf("%d %d\n",rand() % 50 + 1,rand() % 50 + 1);
	}

	while(m--){
		int opt = rand() % 2 + 1;
		if(opt == 1){
			int p = rand() % n + 1;
			int x = rand() % 50 + 1;
			int y = rand() % 50 + 1;
			printf("%d %d %d %d\n",opt,p,x,y);
		}
		if(opt == 2){
			int r = rand() % n + 1;
			int l = rand() % r + 1;
			printf("%d %d %d\n",opt,l,r);
		}
		
	}
	
	return 0;
}
