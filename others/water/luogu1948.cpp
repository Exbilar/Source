#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)

using std :: max;
using std :: min;
using std :: set;
using std :: pair;
using std :: make_pair;
using std :: vector;
using std :: queue;
using std :: multiset;
using std :: priority_queue;

typedef long long LL;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const int maxm = 1e6 + 10;

template <class T> void read(T &in){
	in = 0; int f = 1 ;char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

template <class T> inline bool chkmax(T &x,T y){
	return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
	return x > y ? x = y,true : false;
}

int fst[maxm],nxt[maxm],to[maxm],val[maxm];
int que[maxm],dis[maxm],inq[maxm];
int cnt,n,m,k;

struct Edge{
	int x,y,v;
}E[maxm];

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,val[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,val[cnt] = v,fst[t] = cnt;
}

void build(int x){
	memset(fst,0,sizeof fst); cnt = 0;
	for(int i = 1;i <= m;i++){
		if(E[i].v <= x) ins(E[i].x,E[i].y,0);
		else ins(E[i].x,E[i].y,1);
	}
}

bool chk(int x){
	build(x);
	
	for(int i = 1;i <= n;i++) dis[i] = INF,inq[i] = 0;
	int head = 1,tail = 0;
	que[++tail] = 1,inq[1] = 1;
	dis[1] = 0;

	while(head <= tail){
		int x = que[head++]; inq[x] = 0;
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(dis[v] > dis[x] + val[u]){
				dis[v] = dis[x] + val[u];
				if(!inq[v]) inq[que[++tail] = v] = 1;
			}
		}
	}

	return dis[n] <= k;	
}

int main(){
	int maxv = 0;
	read(n),read(m),read(k);
	for(int i = 1;i <= m;i++)
		read(E[i].x),read(E[i].y),read(E[i].v),chkmax(maxv,E[i].v);
	
	int l = 1,r = maxv,ans = -1;
	
	while(l <= r){
		int mid = (l + r) >> 1;
		if(chk(mid)) ans = mid,r = mid - 1;
		else l = mid + 1;
	}
	
	printf("%d\n",ans);
	
	return 0;
}
