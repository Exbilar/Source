#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 1e6 + 10;

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

LL fst[maxm],nxt[maxm],to[maxm],val[maxm],vis[maxm];
LL dis[maxm],bin[maxm],cir[maxm],bas[maxm];
LL cnt,sz,n,m;

void ins(LL f,LL t,LL v){
	nxt[++cnt] = fst[f],to[cnt] = t,val[cnt] = v,fst[f] = cnt;
	nxt[++cnt] = fst[t],to[cnt] = f,val[cnt] = v,fst[t] = cnt;
}

void dfs(LL x){
	vis[x] = 1;
	for(LL u = fst[x];u;u = nxt[u]){
		LL v = to[u];
		if(!vis[v]) dis[v] = dis[x] ^ val[u],dfs(v);
		else cir[++sz] = dis[x] ^ dis[v] ^ val[u];
	}
}

int main(){

	read(n),read(m);
	
	LL u,v,w;
	for(LL i = 1;i <= m;i++){
		read(u),read(v),read(w);
		ins(u,v,w);
	}
	
	bin[0] = 1;
	for(LL i = 1;i <= 62;i++) bin[i] = bin[i - 1] << 1;

	dfs(1);

	LL ans = dis[n];
	
	for(LL i = 1;i <= sz;i++){
		for(LL j = 62;j >= 0;j--){
			if(!(cir[i] & bin[j])) continue;
			if(!bas[j]){
				bas[j] = i;
				break;
			}
			cir[i] ^= cir[bas[j]];
		}
	}
	
	for(LL i = 62;i >= 0;i--){
		chkmax(ans,ans ^ cir[bas[i]]);
	}

	printf("%lld\n",ans);
	
	return 0;
}
