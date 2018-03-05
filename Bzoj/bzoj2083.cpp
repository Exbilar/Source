#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;

vector<int>nxt[maxm];
int A[maxm],B[maxm];
int n,m,Q;

int solve(int num,int pos){
    int l=0;int r=nxt[num].size()-1;int ret=n+1;
    while(l<=r){
	int mid=(l+r)>>1;
	if(nxt[num][mid]>pos)ret=mid,r=mid-1;
	else l=mid+1;
    }
    return (ret==n+1?ret:nxt[num][ret]);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
	scanf("%d",&A[i]);
	nxt[A[i]].push_back(i);
    }
    scanf("%d",&Q);

    while(Q--){
	scanf("%d",&m);
	for(int i=1;i<=m;i++)scanf("%d",&B[i]);
	int pos=0;int f=1;int i=1;
	for(int i=1;i<=m;i++){
	    pos=solve(B[i],pos);
	    if(pos>n){f=0;break;}
	}
	if(f)puts("TAK");
	else puts("NIE");
    }

    return 0;
}
