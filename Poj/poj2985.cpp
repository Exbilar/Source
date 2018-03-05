#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 2e6 + 10;

int size[maxm],cnt[maxm],ch[maxm][2],v[maxm],rnk[maxm];
int ftr[maxm],sizef[maxm];
int sz,rt,n,m,opt;

int chk(int x,int y){
	return x == y ? 233 : x > y;
}

void upt(int x){
	size[x] = size[ch[x][0]] + size[ch[x][1]] + cnt[x];
}

void rotate(int &x,int f){
	int t = ch[x][f];
	ch[x][f] = ch[t][f ^ 1];
	ch[t][f ^ 1] = x;
	size[t] = size[x];
	upt(x),x = t;
}

void insert(int &x,int val){
	if(!x) return x = ++sz,v[x] = val,rnk[x] = rand(),size[x] = cnt[x] = 1,void();
	size[x]++;
	if(v[x] == val) return cnt[x]++,void();
	int f = chk(val,v[x]);
	insert(ch[x][f],val);
	if(rnk[x] < rnk[ch[x][f]]) rotate(x,f);
}

void del(int &x,int val){
	if(!x) return;
	if(v[x] != val) size[x]--,del(ch[x][chk(val,v[x])],val);
	if(v[x] == val){
		if(cnt[x] > 1) return cnt[x]--,upt(x),void();
		if(ch[x][0] * ch[x][1] == 0) return x = ch[x][0] ^ ch[x][1],void();
		int f = chk(rnk[ch[x][0]],rnk[ch[x][1]]);
		rotate(x,f),del(x,val);
	}
}

int Qrank(int x,int rank){
	if(!x) return 0;
	if(rank <= size[ch[x][0]]) return Qrank(ch[x][0],rank);
	if(rank > size[ch[x][0]] + cnt[x]) return Qrank(ch[x][1],rank - size[ch[x][0]] - cnt[x]);
	else return x;
}

int find(int x){
	return x == ftr[x] ? x : ftr[x] = find(ftr[x]);
}

void Union(int x,int y){
	x = find(x),y = find(y);
	ftr[x] = y;
	if(x == y) return;
	del(rt,sizef[x]),del(rt,sizef[y]);
	sizef[y] += sizef[x];
	insert(rt,sizef[y]);
}

int main(){
	int x,y,k;
	
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) ftr[i] = i,sizef[i] = 1;
	for(int i = 1;i <= n;i++) insert(rt,sizef[i]);
	while(m--){
		scanf("%d",&opt);
		if(opt == 0) scanf("%d%d",&x,&y),Union(x,y);
		if(opt == 1) scanf("%d",&k),printf("%d\n",k <= size[rt] ? v[Qrank(rt,size[rt] - k + 1)] : 1);
	}
	
	return 0;
}
