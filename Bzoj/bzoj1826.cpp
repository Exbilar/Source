#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;

static const int maxm = 1e6 + 10;

priority_queue<pii> Q;

int nxt[maxm],lst[maxm],A[maxm],vis[maxm];
map<int,int> cnt;
int n,k,p,ans,in;

int main(){
	scanf("%d%d",&p,&k);
	for(int i = 1;i <= p;i++){
		scanf("%d",&in);
		if(!cnt[in]) cnt[in] = ++n;
		A[i] = cnt[in];
	}
	for(int i = 1;i <= n;i++) lst[i] = p + 1; 
	for(int i = p;i;i--){
		nxt[i] = lst[A[i]];
		lst[A[i]] = i;
	}

	for(int i = 1;i <= p;i++){
		if(vis[A[i]]){
			Q.push(make_pair(nxt[i],A[i]));
			continue;
		}
		if(k){
			vis[A[i]] = 1;
			Q.push(make_pair(nxt[i],A[i]));
			ans++,k--;
		}else{
			while(!vis[Q.top().second]) Q.pop();
			vis[Q.top().second] = 0;Q.pop();
			vis[A[i]] = 1;
			Q.push(make_pair(nxt[i],A[i]));
			ans++;
		}
	}

	printf("%d\n",ans);
	
	return 0;
}
