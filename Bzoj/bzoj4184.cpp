#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: set;
using std :: pair;
using std :: vector;
using std :: make_pair;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 2e6 + 10;

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

vector<int> sum[maxm];
int ans[maxm],bin[maxm],A[maxm];
int n;

set< pair<int,int> > S;
typedef set< pair<int,int> > :: iterator itr;

struct Liner_Basis{
	int Bas[100];
	Liner_Basis(){clr(Bas);}
	int operator [] (const int &pos) const {
		return Bas[pos];
	}
}bas;

void insert(Liner_Basis &bas,int v){
	for(int i = 30;i >= 0;i--){
		if(!(v & bin[i])) continue;
		if(!bas[i]) return bas.Bas[i] = v,void();
		else v ^= bas[i];
	}
}

void modify(int x,int l,int r,int L,int R,int v){
	if(l >= L && r <= R){
		sum[x].push_back(v);
		return ;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) modify(x << 1,l,mid,L,R,v);
	if(R > mid) modify(x << 1 | 1,mid + 1,r,L,R,v);
}

void Query(int x,int l,int r,Liner_Basis bas){
	for(unsigned int i = 0;i < sum[x].size();i++)
		insert(bas,sum[x][i]);
	
	if(l == r){
		int res = 0;
		for(int i = 30;i >= 0;i--) chkmax(res,res ^ bas[i]);
		printf("%d\n",res);
		return ;
	}
	
	int mid = (l + r) >> 1;
	Query(x << 1,l,mid,bas);
	Query(x << 1 | 1,mid + 1,r,bas);
}

int main(){

	bin[0] = 1;
	for(int i = 1;i <= 30;i++) bin[i] = bin[i - 1] << 1;
	
	read(n);
	for(int i = 1;i <= n;i++) read(A[i]);
	for(int i = 1;i <= n;i++){
		if(A[i] > 0) S.insert(make_pair(A[i],i));
		else{
			itr it = S.lower_bound(make_pair(-A[i],0));
			modify(1,1,n,(*it).second,i - 1,-A[i]);
			S.erase(it);
		}
	}

	while(!S.empty()){
		itr it = S.begin();
		modify(1,1,n,(*it).second,n,(*it).first);
		S.erase(it);
	}

	Query(1,1,n,bas);

	return 0;
}
