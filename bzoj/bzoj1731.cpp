#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: max;
using std :: min;

typedef long long LL;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;
static const LL oo = 1LL << 62;

template <class T> inline bool chkmax(T &x,T y){
	return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
	return x > y ? x = y,true : false;
}

template <typename T> inline void read (T &in){
	in = 0; char ch = getchar(); T f = 1;
	for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
	for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

int fst[maxm],nxt[maxm],to[maxm],que[maxm],inq[maxm],vis[maxm];
LL val[maxm],dis[maxm];
int cnt,n,m1,m2;

void ins(int f,int t,LL v){
	nxt[++cnt] = fst[f],to[cnt] = t,val[cnt] = v,fst[f] = cnt;
}

LL spfa(int S){
	for(int i = 1;i <= n;i++) dis[i] = INF,inq[i] = 0;
	int head = 1,tail = 0;
	vis[S] = inq[S] = 1,dis[S] = 0;
	que[++tail] = S;
	
	while(head <= tail){
		int x = que[head++]; inq[x] = 0;
		for(int u = fst[x];u;u = nxt[u]){
			int v = to[u];
			if(dis[v] > dis[x] + val[u]){
				dis[v] = dis[x] + val[u];
				if(!inq[v]){
					if(vis[v] == n) return -1;
					inq[que[++tail] = v] = 1;
					vis[v]++;
				}
			}
		}
	}
	return dis[n] >= INF ? -2 : dis[n];
}

int main(){
	
	int x,y;LL L;
	
	read(n); read(m1); read(m2);
	
	for(int i = 1;i <= m1;i++){
		read(x),read(y),read(L);
		if(x < y) std :: swap(x,y);
		ins(y,x,L);
	}
	
	for(int i = 1;i <= m2;i++){
		read(x),read(y),read(L);
		if(x < y) std :: swap(x,y);
		ins(x,y,-L);
	}
	
	printf("%lld\n",spfa(1));
	
	return 0;
}
