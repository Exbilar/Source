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

struct Node{
	int x,y,z,tot;
	
	bool operator < (const Node &N) const {
		return x == N.x ? y == N.y ? z < N.z : y < N.y : x < N.x;
	}

	bool operator != (const Node &N) const {
		return x != N.x || y != N.y || z != N.z;
	}
}A[maxm],B[maxm];

int bit[maxm],ans[maxm];
int n,m;

int lowbit(int x){
	return x & -x;
}

void Upt(int k,int v){
	for(int i = k;i <= m;i += lowbit(i)) bit[i] += v;
}

int Qry(int k){
	int res = 0;
	for(int i = k;i;i -= lowbit(i)) res += bit[i];
	return res;
}

void CDQ(int l,int r){
	if(l == r) return ;

	int mid = (l + r) >> 1;
	
	CDQ(l,mid),CDQ(mid + 1,r);
	
	int head = l,tail = mid + 1;
	
	for(int i = l;i <= r;i++){
		if((head <= mid && A[head].y <= A[tail].y) || tail > r){
			Upt(A[head].z,1);
			B[i] = A[head++];
		}
		else{
			A[tail].tot += Qry(A[tail].z);
			B[i] = A[tail++];
		}
	}

	for(int i = l;i <= mid;i++) Upt(A[i].z,-1);
	for(int i = l;i <= r;i++) A[i] = B[i];
}

int main(){

	read(n); read(m);
	for(int i = 1;i <= n;i++){
		read(A[i].x),read(A[i].y),read(A[i].z);
	}

	std :: sort(A + 1,A + n + 1);

	CDQ(1,n);

	std :: sort(A + 1,A + n + 1);

	int cur = 0,num = 0;
	for(int i = 1;i <= n;i++){
		num++;
		if(A[i] != A[i + 1]){
			chkmax(cur,A[i].tot);
			ans[cur] += num;
			cur = 0; num = 0;
		}
		else chkmax(cur,A[i].tot);
	}

	for(int i = 0;i < n;i++) printf("%d\n",ans[i]);
	
	return 0;
}
