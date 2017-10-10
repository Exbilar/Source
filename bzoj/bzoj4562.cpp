#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

static const int maxm = 1e6 + 10;

int fst[maxm],to[maxm],nxt[maxm],ind[maxm];
int f[maxm],inq[maxm];
int n,m,cnt,ans;

queue<int> Q;

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
	ind[t]++;
}

int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++) scanf("%d%d",&x,&y),ins(x,y);
	for(int i = 1;i <= n;i++)
		if(!ind[i] && fst[i]) f[i] = 1,Q.push(i);
	
	while(!Q.empty()){
		int top = Q.front();Q.pop();
		for(int u = fst[top];u;u = nxt[u]){
			int v = to[u];
			ind[v]--;
			f[v] += f[top];
			if(!ind[v]) Q.push(v);
		}		
	}
	for(int i = 1;i <= n;i++)
		if(!fst[i]) ans += f[i];
	
	printf("%d\n",ans);
	
	return 0;
}
