#include <set>
#include <queue>
#include <cstdio>
#include <algorithm>

using std :: multiset;
using std :: queue;

static const int maxm = 1e6 + 10;
static const int INF = 1 << 29;

multiset<int> S;
queue<int> Q;

int lc[maxm],rc[maxm],v[maxm],ftr[maxm],tag[maxm],A[maxm],stk[maxm];
char ch[10];
int n,m,ALL,tp;

int findx(int x){
	while(ftr[x]) x = ftr[x];
	return x;
}

void pushdown(int x){
	if(!tag[x]) return ;
	if(lc[x]) v[lc[x]] += tag[x],tag[lc[x]] += tag[x];
	if(rc[x]) v[rc[x]] += tag[x],tag[rc[x]] += tag[x];
	tag[x] = 0;
}

void pushtag(int x){
	while(x) stk[++tp] = x,x = ftr[x];
	while(tp) pushdown(stk[tp--]);
}

int top(int x){
	return v[findx(x)];
}

int merge(int x,int y){
	if(!x || !y) return x ^ y;
	if(v[x] < v[y]) std :: swap(x,y);
	pushdown(x);
	rc[x] = merge(rc[x],y);
	ftr[rc[x]] = x;
	std :: swap(lc[x],rc[x]);
	return x;
}

int del(int x){
	pushtag(x);
	int t = merge(lc[x],rc[x]),fa = ftr[x];
	lc[x] = rc[x] = ftr[x] = 0;
	if(x == lc[fa]) lc[fa] = t;
	else rc[fa] = t;
	ftr[t] = fa;
	return findx(t);
}

void add(int x,int val){
	pushtag(x);
	S.erase(S.find(v[findx(x)]));
	v[x] += val;
	S.insert(v[merge(x,del(x))]);
}

void heap_add(int x,int val){
	int rt = findx(x);
	S.erase(S.find(v[rt]));
	tag[rt] += val,v[rt] += val;
	S.insert(v[rt]);
}

void add_edge(int x,int y){
	int rt1 = findx(x),rt2 = findx(y);
	if(rt1 != rt2){
		if(merge(rt1,rt2) == rt1) S.erase(S.find(v[rt2]));
		else S.erase(S.find(v[rt1]));
	}
}

int main(){
	int x,y,val;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&A[i]),S.insert(A[i]),v[i] = A[i];
	scanf("%d",&m);

	while(m--){
		scanf("%s",ch + 1);
		if(ch[1] == 'A')
			if(ch[2] == '1') scanf("%d%d",&x,&val),add(x,val);
			else if(ch[2] == '2') scanf("%d%d",&x,&val),heap_add(x,val);
			else if(ch[2] == '3') scanf("%d",&val),ALL += val;
		if(ch[1] == 'F')
			if(ch[2] == '1') scanf("%d",&x),pushtag(x),printf("%d\n",v[x] + ALL);
			else if(ch[2] == '2') scanf("%d",&x),printf("%d\n",top(x) + ALL);
			else if(ch[2] == '3') printf("%d\n",*--S.find(INF) + ALL);
		if(ch[1] == 'U') scanf("%d%d",&x,&y),add_edge(x,y);
	}
	
	return 0;
}
