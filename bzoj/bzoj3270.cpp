#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 2000 + 10;

template <class T> inline bool chkmax(T &x,T y){
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in){
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

double mtx[maxm][maxm],P[maxm],ddf[maxm];
int fst[maxm],nxt[maxm],to[maxm],deg[maxm];
int n,m,A,B,cnt,tot;

int getPos(int x,int y){
	return (x - 1) * n + y;
}

void ins(int f,int t){
	nxt[++cnt] = fst[f],to[cnt] = t,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,fst[t] = cnt;
	deg[f]++,deg[t]++;
}

void build(int x,int y){
	mtx[getPos(x,y)][getPos(x,y)]--;
	for(int u1 = fst[x];u1;u1 = nxt[u1]){
		for(int u2 = fst[y];u2;u2 = nxt[u2]){
			int v1 = to[u1],v2 = to[u2];
			
			if(v1 == v2) continue;
			
			if(v1 == x && v2 == y){
				mtx[getPos(x,y)][getPos(v1,v2)] += P[v1] * P[v2];
			}
			else if(v1 != x && v2 != y){
				mtx[getPos(x,y)][getPos(v1,v2)] += ddf[v1] * ddf[v2];
			}
			else if(v1 == x && v2 != y){
				mtx[getPos(x,y)][getPos(v1,v2)] += P[x] * ddf[v2];
			}
			else if(v1 != x && v2 == y){
				mtx[getPos(x,y)][getPos(v1,v2)] += ddf[v1] * P[y];
			}
		}
	}
}

void print(){
	for(int i = 1;i <= tot;i++){
		for(int j = 1;j <= tot + 1;j++){
			printf("%lf ",mtx[i][j]);
		}
		putchar(10);
	}
	putchar(10);
}

void gauss(){
	for(int i = 1;i <= tot;i++){
		int pos = i;
		for(int j = i + 1;j <= tot;j++)
			if(fabs(mtx[j][i]) > fabs(mtx[pos][i])) pos = j;
		double cur = mtx[pos][i];
		for(int j = i;j <= tot + 1;j++) std :: swap(mtx[i][j],mtx[pos][j]);
		for(int j = i;j <= tot + 1;j++) mtx[i][j] /= cur;
		for(int k = 1;k <= tot;k++){
			if(k == i) continue;
			cur = mtx[k][i];
			for(int j = i;j <= tot + 1;j++) mtx[k][j] -= mtx[i][j] * cur;
		}
	}
}

int main(){
	
	read(n),read(m),read(A),read(B); tot = n * n;

	int u,v;
	for(int i = 1;i <= m;i++){
		read(u),read(v);
		ins(u,v);
	}

	for(int i = 1;i <= n;i++){
		scanf("%lf",&P[i]);
		ddf[i] = (double) (1 - P[i]) / (double) (deg[i]);
	}
	
	for(int i = 1;i <= n;i++) nxt[++cnt] = fst[i],to[cnt] = i,fst[i] = cnt;

	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++) build(i,j);

	mtx[getPos(A,B)][tot + 1] = -1.0;
	
	gauss();
	
	for(int i = 1;i <= n;i++){
		int pos = getPos(i,i);
		if(i != n) printf("%.6lf ",mtx[pos][tot + 1]);
		else printf("%.6lf",mtx[pos][tot + 1]);
	}
	
	return 0;
}
