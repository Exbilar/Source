#include <bits/stdc++.h>

using std :: max;
using std :: min;
using std :: priority_queue;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

struct heap{
	int mrk[maxm];
	priority_queue<int> que;

	void clear(){
		while(!que.empty()) que.pop();
		memset(mrk,0,sizeof mrk);
	}

	void push(int x){
		if(mrk[x]) mrk[x]--;
		else que.push(x);
	}
	
	int top(){
		while(mrk[que.top()]) mrk[que.top()]--,que.pop();
		return que.top();
	}

	void pop(){
		que.pop();
	}
	
	void del(int x){
		mrk[x]++;
	}
	
}que;

int fst[maxm],nxt[maxm],to[maxm],_fst[maxm],_nxt[maxm],_to[maxm];
int ind[maxm],ddf[maxm],f[maxm][2],stk[maxm];
int n,m,cnt,_cnt,sz,top,ans,anslen = INF;

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt,ind[t]++;
	_nxt[++_cnt] = _fst[t],_to[_cnt] = f,_fst[t] = _cnt;
}

void topsort(){
	for(int i = 1;i <= n;i++)
		if(!ind[i]) stk[++top] = i,ddf[++sz] = i;
	
	while(top){
		int x = stk[top--];
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			ind[v]--;
			if(!ind[v]) stk[++top] = v,ddf[++sz] = v;
		}
	}
}

void DP(){
	
	for(int i = 1;i <= n;i++){
		int x = ddf[i];
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			f[v][0] = max(f[v][0],f[x][0] + 1);
		}
	}

	for(int i = n;i >= 1;i--){
		int x = ddf[i];
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			f[x][1] = max(f[x][1],f[v][1] + 1);
		}
	}
	
}

int main(){
	
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++) scanf("%d%d",&x,&y),ins(x,y);
	topsort(); DP();

	for(int i = 1;i <= n;i++) que.push(f[i][1]);
	que.push(0);
	
	for(int i = 1;i <= n;i++){
		int x = ddf[i];
		
		que.del(f[x][1]);
		for(int u = _fst[x];u;u = _nxt[u]){
			int v = _to[u];
			que.del(f[v][0] + f[x][1] + 1);
		}
		
		if(que.top() < anslen) anslen = que.top(),ans = x;
		
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			que.push(f[x][0] + f[v][1] + 1);
		}
		
		que.push(f[x][0]);
	}

	printf("%d %d\n",ans,anslen);
	
	return 0;
}
