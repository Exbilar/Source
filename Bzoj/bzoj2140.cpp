#include <bits/stdc++.h>

using std :: string;
using std :: map;

static const int maxm = 1e6 + 10;

int vis[maxm],stk[maxm],low[maxm],dfn[maxm],fst[maxm],nxt[maxm],to[maxm],plc[maxm];
int top,cnt,sz,tot,n,m;
string boy_next_door,girl_next_door;

map<string,int> idx;

void ins(int f,int t){
	nxt[++cnt] = fst[f];
	to[cnt] = t;
	fst[f] = cnt;
}

void tarjan(int x){
	stk[++top] = x;
	vis[x] = 1;
	low[x] = dfn[x] = ++sz;
	
	for(int u = fst[x];u;u = nxt[u]){
		int v = to[u];
		if(!dfn[v])
			tarjan(v),low[x] = std :: min(low[x],low[v]);
		else if(vis[v])
			low[x] = std :: min(low[x],dfn[v]);
	}
	
	if(low[x] == dfn[x]){
		tot++;
		while(x != stk[top + 1])
			vis[stk[top]] = 0,plc[stk[top--]] = tot;
	}
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		std :: cin >> girl_next_door >> boy_next_door;
		idx[boy_next_door] = i << 1 | 1;
		idx[girl_next_door] = i << 1;
		ins(i << 1,i << 1 | 1);
	}

	scanf("%d",&m);
	for(int i = 1;i <= m;i++){
		std :: cin >> girl_next_door >> boy_next_door;
		ins(idx[boy_next_door],idx[girl_next_door]);
	}
	
	for(int i = 1;i <= 2 * n + 1;i++)
		if(!dfn[i]) tarjan(i);

	for(int i = 1;i <= n;i++)
		if(plc[i << 1] != plc[i << 1 | 1]) puts("Safe");
		else puts("Unsafe");
	
	return 0;
}
