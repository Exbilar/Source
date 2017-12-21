#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;
using std :: set;
using std :: pair;
using std :: make_pair;

typedef long long LL;
typedef pair<int,int> pii;

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

struct node{
    int len,id,num;
    node(){len = 0,id = 0,num = 0;}
    node(int ___,int ____,int _____){len = ___,id = ____,num = _____;}
    bool operator < (const node &N) const {
        return len == N.len ? id > N.id : len < N.len;
    }
};

int A[maxm],L[maxm],K[maxm];
pii nxt[maxm],lst[maxm];
int N;

void ins(int x,int y,int lenx,int leny){
    nxt[x] = make_pair(y,leny);
    lst[y] = make_pair(x,lenx);
}

set<node> S;

typedef set<node> :: iterator itr;

void solve(){
	
    int ans = 0;
    while(!S.empty()){
        itr it = --S.end();
        pii _lst = lst[(*it).id];
        pii _nxt = nxt[(*it).id];
        itr lstitr = S.lower_bound(node(_lst.second,_lst.first,0));
        itr nxtitr = S.lower_bound(node(_nxt.second,_nxt.first,0));

		bool f = true;
		if((*lstitr).len != _lst.second || (*lstitr).id != _lst.first) f = false;
		if((*nxtitr).len != _nxt.second || (*nxtitr).id != _nxt.first) f = false;
		
        if((*lstitr).num == (*nxtitr).num && f){
            node _new = (*lstitr);
            _new.len += (*nxtitr).len;			
            nxt[_new.id] = nxt[(*nxtitr).id];
			
			lst[nxt[(*nxtitr).id].first] = make_pair(_new.id,_new.len);
			nxt[lst[(*lstitr).id].first] = make_pair(_new.id,_new.len);
			
            S.erase(lstitr),S.erase(nxtitr);
            S.insert(_new);
        }
		else if(f){
			nxt[_lst.first] = nxt[(*it).id];
			lst[_nxt.first] = lst[(*it).id];
		}
		else{
			if((*lstitr).len != _lst.second || (*lstitr).id != _lst.first){
				lst[_nxt.first] = make_pair(0,0);
			}
			if((*nxtitr).len != _nxt.second || (*nxtitr).id != _nxt.first){
				nxt[_lst.first] = make_pair(0,0);
			}
		}
		
		S.erase(it);
        ans++;
    }   
	
    printf("%d\n",ans);
}

int main(){
	
    read(N);
    for(int i = 1;i <= N;i++) read(A[i]);

    int lstpos = 0,lstlen = 0,cnt = 0;
    for(int i = 1;i < N;i++){
        if(A[i] != A[i + 1]){
            ++cnt;
            ins(cnt - 1,cnt,lstlen,i - lstpos);
            L[cnt] = i - lstpos;
            K[cnt] = A[i];
            lstlen = i - lstpos;
            lstpos = i;
        }
    }
	
    ++cnt;
    ins(cnt - 1,cnt,lstlen,N - lstpos);
    L[cnt] = N - lstpos;
    K[cnt] = A[N];

    for(int i = 1;i <= cnt;i++){
        S.insert(node(L[i],i,K[i]));
    }

    solve();

    return 0;
}
