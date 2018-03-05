#include <cstdio>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 29;

struct edge{
	int x,y,vala,valb;
	bool operator < (const edge &E) const {
		return vala == E.vala ? valb < E.valb : vala < E.vala;
	}
}E[maxm];

int ch[maxm][2],rev[maxm],ftr[maxm],father[maxm],v[maxm],maxb[maxm],stk[maxm];
int top,cnt,n,m,ans = INF;
	
int find(int x){
	return x == father[x] ? x : father[x] = find(father[x]);
}

int get(int x){
	return ch[ftr[x]][1] == x;
}

int isrt(int x){
	return ch[ftr[x]][0] != x && ch[ftr[x]][1] != x;
}

void upt(int x){
	int lc = ch[x][0],rc = ch[x][1];
	maxb[x] = x;
	if(v[maxb[lc]] > v[maxb[x]]) maxb[x] = maxb[lc];
	if(v[maxb[rc]] > v[maxb[x]]) maxb[x] = maxb[rc];
}

void rotate(int x){
	int fa = ftr[x],gnd = ftr[fa],f = get(x);
	if(!isrt(fa)) ch[gnd][get(fa)] = x;
	ch[fa][f] = ch[x][f ^ 1],ftr[ch[x][f ^ 1]] = fa;
	ch[x][f ^ 1] = fa,ftr[fa] = x,ftr[x] = gnd;
	upt(fa),upt(x);
}

void pushdown(int x){
	if(!rev[x]) return;
	int lc = ch[x][0],rc = ch[x][1];
	rev[lc] ^= 1,rev[rc] ^= 1,rev[x] ^= 1;
	std :: swap(ch[x][0],ch[x][1]);
}

void pushtag(int x){
	top = 0,stk[++top] = x;
	for(int i = x;!isrt(i);i = ftr[i])
		stk[++top] = ftr[i];
	for(int i = top;i;i--) pushdown(stk[i]);
}

void splay(int x){
	pushtag(x);
	for(x;!isrt(x);rotate(x))
		if(!isrt(ftr[x])) rotate(get(x) == get(ftr[x]) ? ftr[x] : x);
}

void access(int x){
	for(int y = 0;x;y = x,x = ftr[x])
		splay(x),ch[x][1] = y,upt(x);
}

void makert(int x){
	access(x),splay(x),rev[x] ^= 1;
}

void split(int x,int y){
	makert(x),access(y),splay(y);
}

void link(int x,int y){
	makert(x),ftr[x] = y;
}

void cut(int x,int y){
	split(x,y),ch[y][0] = ftr[x] = 0,upt(y);
}

int Qry(int x,int y){
	split(x,y);
	return maxb[y];
}
  
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) father[i] = i;
	for(int i = 1;i <= m;i++) scanf("%d%d%d%d",&E[i].x,&E[i].y,&E[i].vala,&E[i].valb);
	std :: sort(E + 1,E + m + 1);
	
	for(int i = 1;i <= m;i++){
		int dx = find(E[i].x),dy = find(E[i].y);
		if(dx == dy){
			int mx = Qry(E[i].x,E[i].y);
			if(v[mx] > E[i].valb){
				cut(mx,E[mx - n].x),cut(mx,E[mx - n].y);
				v[n + i] = E[i].valb,maxb[n + i] = n + i;
				link(E[i].x,n + i),link(E[i].y,n + i);
			}
		}
		if(dx != dy){
			v[n + i] = E[i].valb,maxb[n + i] = n + i;
			link(E[i].x,n + i),link(E[i].y,n + i),father[dx] = dy;
		}
		if(find(1) == find(n)) ans = std :: min(ans,E[i].vala + v[Qry(1,n)]);
	}

	printf("%d\n",ans == INF ? -1 : ans);
	
	return 0;
}
