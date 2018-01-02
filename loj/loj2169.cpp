#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: vector;

typedef unsigned long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 3e5 + 10;

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

LL bit[maxm],num[maxm],nd[maxm],cur[maxm];
int L[maxm],R[maxm],idx[maxm],ans[maxm],tmp[maxm];
int n,m,k;

vector<int> vec[maxm];

int lowbit(int x){
	return x & -x;
}

void Upt(int k,LL v){
	for(register int i = k;i <= m;i += lowbit(i)) bit[i] += v;
}

LL Qry(int k){
	LL res = 0;
	for(register int i = k;i;i -= lowbit(i)) res += bit[i];
	return res;
}

void modify(int l,int r,LL v){
	Upt(l,v),Upt(r + 1,-v);
}

void solve(int l,int r,int ql,int qr){
	if(ql > qr) return ;
	if(l == r){
		for(register int i = ql;i <= qr;i++) ans[idx[i]] = l;
		return ;
	}
	
	int mid = (l + r) >> 1;
	
	for(register int i = l;i <= mid;i++){
		if(L[i] <= R[i]) modify(L[i],R[i],num[i]);
		else modify(L[i],m,num[i]),modify(1,R[i],num[i]);
	}
	
	int pos1 = ql,pos2 = qr;
	
	for(register int i = ql;i <= qr;i++){
		register LL sum = 0;
		for(register int j = 0;j < vec[idx[i]].size();j++) sum += Qry(vec[idx[i]][j]);
		if(cur[idx[i]] + sum >= nd[idx[i]]) tmp[pos1++] = idx[i];
		else cur[idx[i]] += sum,tmp[pos2--] = idx[i];
	}

	for(register int i = ql;i <= qr;i++) idx[i] = tmp[i];

	for(register int i = l;i <= mid;i++){
		if(L[i] <= R[i]) modify(L[i],R[i],-num[i]);
		else modify(L[i],m,-num[i]),modify(1,R[i],-num[i]);
	}
	
	solve(l,mid,ql,pos1 - 1),solve(mid + 1,r,pos2 + 1,qr);
}

int main(){

	int u;
	read(n),read(m);
	for(register int i = 1;i <= m;i++) read(u),vec[u].push_back(i);

	for(register int i = 1;i <= n;i++) read(nd[i]),idx[i] = i;

	read(k);
	for(register int i = 1;i <= k;i++) read(L[i]),read(R[i]),read(num[i]);
	L[++k] = 1,R[k] = n,num[k] = INF;

	solve(1,k,1,n);

	for(register int i = 1;i <= n;i++){
		if(ans[i] != k) printf("%d\n",ans[i]);
		else puts("NIE");
	}

	return 0;
}
