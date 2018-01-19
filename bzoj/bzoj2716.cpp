 #include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

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

int bit[maxm],ans[maxm];
int n,m,smax;

struct Query{
	int x,y,id,opt;
	bool operator < (const Query &rhs) const {
		return x == rhs.x ? y < rhs.y : x < rhs.x;
	}
}Q[maxm],tmp[maxm];

bool cmp(const Query &lhs,const Query &rhs){
	return lhs.x == rhs.x ? lhs.id < rhs.id : lhs.x < rhs.x;
}

bool _cmp(const Query &lhs,const Query &rhs){
	return lhs.id < rhs.id;
}

int lowbit(int x){
	return x & -x;
}

void Upt(int k,int v){
	for(int i = k;i <= smax;i += lowbit(i)) chkmax(bit[i],v);
}

int Qry(int k){
	int res = 0;
	for(int i = k;i;i -= lowbit(i)) chkmax(res,bit[i]);
	return res;
}

void clear(int k){
	for(int i = k;i <= smax;i += lowbit(i)) bit[i] = 0;
}

void solve(int L,int R){
	if(L == R) return ;

	int mid = (L + R) >> 1;
	int head = L,tail = mid + 1;
	
	for(int i = L;i <= R;i++){
		if(Q[i].id <= mid) tmp[head++] = Q[i];
		else tmp[tail++] = Q[i];
	}

	for(int i = L;i <= R;i++) Q[i] = tmp[i];

	solve(L,mid);

	int cur = L;
	
	for(int i = mid + 1;i <= R;i++){
		if(Q[i].opt == 2){
			while(cur <= mid && Q[cur].x <= Q[i].x){
				if(Q[cur].opt == 1) Upt(Q[cur].y,Q[cur].x + Q[cur].y);
				cur++;
			}
			int ddf = Qry(Q[i].y);
			if(ddf) chkmin(ans[Q[i].id],Q[i].x + Q[i].y - ddf);
		}
	}

	for(int i = L;i <= R;i++){
		if(Q[i].id <= mid && Q[i].opt == 1) clear(Q[i].y); 
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

	read(n),read(m);
	for(int i = 1;i <= n;i++){
		read(Q[i].x),read(Q[i].y);
		Q[i].x++,Q[i].y++;
		chkmax(smax,Q[i].x),chkmax(smax,Q[i].y);
		Q[i].id = i,Q[i].opt = 1;
	}

	for(int i = n + 1;i <= n + m;i++){
		read(Q[i].opt),read(Q[i].x),read(Q[i].y);
		Q[i].x++,Q[i].y++;
		chkmax(smax,Q[i].x),chkmax(smax,Q[i].y);
		Q[i].id = i;
	}

	smax++; n += m;

	for(int i = 1;i <= n;i++) ans[i] = INF;
 
    std :: sort(Q + 1,Q + n + 1,cmp);
    solve(1,n);
 
    for(int i = 1;i <= n;i++) Q[i].x = smax - Q[i].x;
    std :: sort(Q + 1,Q + n + 1,cmp);
    solve(1,n);
 
    for(int i = 1;i <= n;i++) Q[i].y = smax - Q[i].y;
    std :: sort(Q + 1,Q + n + 1,cmp);
    solve(1,n);
 
    for(int i = 1;i <= n;i++) Q[i].x = smax - Q[i].x;
    std :: sort(Q + 1,Q + n + 1,cmp);
    solve(1,n);
 
    std :: sort(Q + 1,Q + n + 1,_cmp);
     
    for(int i = 1;i <= n;i++)
        if(Q[i].opt == 2) printf("%d\n",ans[i]);
	
	return 0;
}
