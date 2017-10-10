#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

static const int maxm = 1e6 + 10;

int A[maxm],B[maxm];
int n;

priority_queue<pii> queA;
priority_queue< pii,vector<pii>,greater<pii> > queB;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]);
	for(int i = 1;i <= n;i++) scanf("%d",&B[i]);
	
	for(int i = 1;i <= n;i++) queA.push(make_pair(A[i],i));
	for(int i = 1;i <= n;i++) queB.push(make_pair(B[i],i));

	while(!queA.empty()){
		pii topA = queA.top(); queA.pop();
		pii topB = queB.top(); queB.pop();
		A[topB.second] = topA.first;
	}

	for(int i = 1;i <= n;i++) printf("%d ",A[i]);
	putchar(10);
	
	return 0;
}
