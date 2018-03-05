#include <set>
#include <cstdio>
#include <algorithm>

using std :: set;

set<int> s;

int T,n,in;

int main(){
	scanf("%d",&T);
	
	while(T--){
		s.clear();
		scanf("%d",&n);
		scanf("%d",&in);
		printf("%d",in),s.insert(in);
		for(int i = 2;i <= n;i++){
			scanf("%d",&in);
			if(!s.count(in)) printf(" %d",in),s.insert(in);
		}
		putchar(10);
	}

	return 0;
}
