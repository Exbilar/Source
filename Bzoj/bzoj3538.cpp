#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: max;
using std :: min;

typedef long long LL;

static const int maxm = 2e6 + 10;
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

int fst[maxm],nxt[maxm],to[maxm],val[maxm];
int que[maxm],dis[maxm],inq[maxm];
int cnt,n,m,S,T;

struct Edge{
	int x,y,P,Q,W;
	Edge(){x = 0,y = 0,P = 0,Q = 0,W = 0;}
}E[maxm];

void ins(int f,int t,int v){
	nxt[++cnt] = fst[f],to[cnt] = t,val[cnt] = v,fst[f] = cnt;
}

void spfa(){
	for(int i = 1;i <= n;i++) dis[i] = INF,inq[i] = 0;
	int head = 1,tail = 0;
	dis[S] = 0,inq[S] = 1;
	que[++tail] = S;
	
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
}

int main(){
	
	read(n),read(m);
	for(int i = 1;i <= m;i++)
		read(E[i].x),read(E[i].y),read(E[i].P),read(E[i].Q);
	
	memset(fst,0,sizeof fst),cnt = 0;
	
	for(int i = 1;i <= m;i++) ins(E[i].y,E[i].x,E[i].P);
	
	S = n,T = 1; spfa();
	
	for(int i = 1;i <= m;i++){
		int xx = E[i].x,yy = E[i].y;
		if(dis[yy] != dis[xx] - E[i].P) E[i].W++;
	}
	
	memset(fst,0,sizeof fst),cnt = 0; 
	
	for(int i = 1;i <= m;i++) ins(E[i].y,E[i].x,E[i].Q);
	
	S = n,T = 1; spfa();
	
	for(int i = 1;i <= m;i++){
		int xx = E[i].x,yy = E[i].y;
		if(dis[yy] != dis[xx] - E[i].Q) E[i].W++;
	}
	
	memset(fst,0,sizeof fst),cnt = 0;   
	
	for(int i = 1;i <= m;i++) ins(E[i].x,E[i].y,E[i].W);
	
	S = 1,T = n; spfa();
	
	printf("%d\n",dis[T]);
	
	return 0;
}
