#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef set<int> :: iterator itr;

static const int maxm = 1e6 + 10;

set<int> s[maxm];
int ftr[maxm],v[maxm];
int n,m,ans,opt;

void solve(int x,int y){
	for(itr it = s[x].begin();it != s[x].end();it++){
		if(v[*it + 1] == y) ans--;
		if(v[*it - 1] == y) ans--;
		s[y].insert(*it);
	}
	for(itr it = s[x].begin();it != s[x].end();it++) v[*it] = y;
	s[x].clear();
}

int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&v[i]);
	for(int i = 1;i <= n;i++){
		ftr[v[i]] = v[i];
		if(v[i] != v[i - 1]) ans++;
		s[v[i]].insert(i);
	}

	for(int i = 1;i <= m;i++){
		scanf("%d",&opt);
		if(opt == 1){
			scanf("%d%d",&x,&y);
			if(x == y) continue;
			if(s[ftr[x]].size() > s[ftr[y]].size()) std :: swap(ftr[x],ftr[y]);
			solve(ftr[x],ftr[y]);
		}
		if(opt == 2) printf("%d\n",ans);
	}

	return 0;
}
