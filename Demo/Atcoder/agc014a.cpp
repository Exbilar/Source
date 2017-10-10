#include <cstdio>
#include <algorithm>

using std :: max;
using std :: min;

typedef long long LL;

LL A,B,C,ans;

int main(){
	scanf("%lld%lld%lld",&A,&B,&C);
	if(A == B && B == C){
		if(~A & 1 && ~B & 1 && ~C & 1) return puts("-1"),0;
		else return puts("0"),0;
	}
	
	while(1){
		if((A % 2 == 1) || (B % 2 == 1) || (C % 2 == 1)) return printf("%lld\n",ans),0;
		int _A = B / 2 + C / 2;
		int _B = A / 2 + C / 2;
		int _C = A / 2 + B / 2;
		A = _A,B = _B,C = _C;
		ans++;
	}
	
	return 0;
}
