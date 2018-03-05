#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 2e5 + 10;
static const double eps = 1e-10;

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
	double A,B,x,y,k,rat;
	int id;
	bool operator < (const Node &rhs) const {
		if(x < rhs.x) return true;
		if(fabs(x - rhs.x) <= eps && y < rhs.y + eps) return true;
		return false;
	}
}Q[maxm],tmp[maxm];

bool cmp(const Node &lhs,const Node &rhs){
	return lhs.k > rhs.k;
}

double f[maxm];
int stk[maxm];
int n,m;

double slp(int i,int j){
	if(!i) return -1e20;
	if(fabs(Q[i].x - Q[j].x) < eps) return 1e20;
	return (Q[i].y - Q[j].y) / (Q[i].x - Q[j].x);
}

void solve(int L,int R){
	if(L == R){
		chkmax(f[L],f[L - 1]);
		Q[L].x = f[L] / (Q[L].rat * Q[L].A + Q[L].B) * Q[L].rat;
		Q[L].y = f[L] / (Q[L].rat * Q[L].A + Q[L].B);
		return ;
	}

	int mid = (L + R) >> 1;
	int head = L,tail = mid + 1;

	for(int i = L;i <= R;i++){
		if(Q[i].id <= mid) tmp[head++] = Q[i];
		else tmp[tail++] = Q[i];
	}

	for(int i = L;i <= R;i++) Q[i] = tmp[i];

	solve(L,mid);

	int top = 0,pos = 1;
	for(int i = L;i <= mid;i++){
		while(top >= 2 &&
			  slp(stk[top],i) + eps > slp(stk[top - 1],stk[top])) top--;
		stk[++top] = i;
	}

	for(int i = mid + 1;i <= R;i++){
		while(pos < top && slp(stk[pos],stk[pos + 1]) + eps > Q[i].k) pos++;
		int ddf = stk[pos];
		f[Q[i].id] = max(f[Q[i].id],Q[ddf].x * Q[i].A + Q[ddf].y * Q[i].B);
	}

	solve(mid + 1,R);

	head = L,tail = mid + 1;
	
	for(int i = L;i <= R;i++){
		if(head <= mid && (Q[head] < Q[tail] || tail > R)) tmp[i] = Q[head++];
		else tmp[i] = Q[tail++];
	}

	for(int i = L;i <= R;i++) Q[i] = tmp[i];
}

int main(){

	read(n); read(m);
	
	f[0] = m;
	
	for(int i = 1;i <= n;i++){
		scanf("%lf%lf%lf",&Q[i].A,&Q[i].B,&Q[i].rat);
		Q[i].id = i; Q[i].k = -Q[i].A / Q[i].B;
	}

	std :: sort(Q + 1,Q + n + 1,cmp);

	solve(1,n);

	printf("%.3lf\n",f[n]);

	return 0;
}
