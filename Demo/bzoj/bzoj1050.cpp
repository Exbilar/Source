#include <cstdio>
#include <algorithm>

static const int maxm = 2e6 + 10;
static const double INF = 2147483647.0;

struct edge{
	int x,y,v;
	bool operator  < (const edge &E) const {
		return v < E.v;
	}
}E[maxm];

int ftr[maxm];
int n,m,s,t,ans1,ans2;
double smin = INF;

int find(int x){
	return x == ftr[x] ? x : ftr[x] = find(ftr[x]);
}

void Union(int x,int y){
	x = find(x),y = find(y);
	if(x != y) ftr[x] = y;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++) scanf("%d%d%d",&E[i].x,&E[i].y,&E[i].v);
	scanf("%d%d",&s,&t);
	std :: sort(E + 1,E + m + 1);

	for(int i = 1;i <= m;i++){
		for(int j = 1;j <= n;j++) ftr[j] = j;
		for(int j = i;j <= m;j++){
			Union(E[j].x,E[j].y);
			if(find(s) == find(t)){
				if(smin > (double)E[j].v / (double)E[i].v)
					smin = (double)E[j].v / (double)E[i].v,
						ans1 = E[j].v,ans2 = E[i].v;
				break;
			}
		}
	}

	if(smin == INF) return puts("IMPOSSIBLE"),0;

	int GCD = std :: __gcd(ans1,ans2);
	ans1 /= GCD,ans2 /= GCD;
	if(ans2 != 1) printf("%d/%d\n",ans1,ans2);
	else printf("%d\n",ans1);
	
	return 0;
}
