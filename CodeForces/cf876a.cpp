#include <bits/stdc++.h>

using std :: max;
using std :: min;

int A,B,C,n;

int main(){
	scanf("%d%d%d%d",&n,&A,&B,&C);

	int smin = min(A,min(B,C));
	
	if(smin == A || smin == B){
		printf("%d\n",(n - 1) * smin);
	}
	else{
		if(n == 1) puts("0");
		else if(n == 2) printf("%d\n",min(A,B));
		else printf("%d\n",(n - 2) * smin + min(A,B));
	}
	
	return 0;
}
