#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;

int fst[maxm],nxt[maxm],to[maxm],val[maxm];
int stk[maxm],ddf[maxm],ind[maxm],oud[maxm];
double f[maxm];
int cnt,top,sz,n,m;

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,val[cnt] = v,fst[f] = cnt;
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
	for(int i = n;i >= 1;i--){
		int x = ddf[i];
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			f[x] += (f[v] + val[u]) / oud[x];
		}
	}
}

int main(){
	
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++)
		scanf("%d%d%d",&x,&y,&z),ins(x,y,z),ind[y]++,oud[x]++;

	topsort(); DP();

	printf("%.2lf\n",f[1]);


	return 0;
}
