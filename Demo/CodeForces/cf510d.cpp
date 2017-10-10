#include <bits/stdc++.h>

using std :: max;
using std :: min;
using std :: pair;
using std :: map;

typedef long long LL;
typedef pair<int,int> pii;
typedef map<int,int> :: iterator itr;

static const int maxm = 1e6 + 10;

map<int,int> f;
pii A[maxm];
int n;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i].first);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i].second);

	f[0] = 0;
	for(int i = 1;i <= n;i++){
		int d = A[i].first,c = A[i].second;
		for(itr it = f.begin();it != f.end();it++){
			int _d = (*it).first;
			int Gcd = std :: __gcd(d,_d);
			if(f[Gcd]) f[Gcd] = std :: min(f[Gcd],f[_d] + c);
			else f[Gcd] = f[_d] + c;
		}
	}
	
	printf("%d\n",f[1] ? f[1] : -1);

	return 0;
}
