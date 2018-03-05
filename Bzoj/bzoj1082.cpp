#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__);

using std :: max;
using std :: min;

typedef long long LL;

static const int maxm = 1000 + 11;
static const int INF = 1 << 30;
static const LL oo = 1LL << 62;

template <class T> inline bool chkmax(T &x,T y){
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x,T y){
    return x > y ? x = y,true : false;
}

template <typename T> inline void read (T &in){
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if(ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

int A[maxm],B[maxm],W[maxm],sum[maxm];
int n,m,wst,tot;

bool dfs(int pos,int tar,int cur){
    if(!pos) return true;
    if(wst + sum[tar] > tot) return false;
    int res = 0;
    for(int i = cur;i <= n;i++){
        if(W[i] >= B[pos]){
            W[i] -= B[pos];
            if(W[i] < B[1]) wst += W[i];
            if(B[pos] == B[pos - 1]) res |= dfs(pos - 1,tar,i);
            else res |= dfs(pos - 1,tar,1);
			
			if(res) return res;
			
            if(W[i] < B[1]) wst -= W[i];
            W[i] += B[pos];
        }
    }
    return res;
}

int main(){
	
    read(n);
    for(int i = 1;i <= n;i++) read(A[i]),tot += A[i];
    read(m);
    for(int i = 1;i <= m;i++) read(B[i]);
    
    std :: sort(A + 1,A + n + 1);
    std :: sort(B + 1,B + m + 1);

    for(int i = 1;i <= m;i++)
        sum[i] = sum[i - 1] + B[i];
    
    while(B[m] > A[n]) m--;   
    
    int l = 1,r = m,ans = 0;
    
    while(l <= r){
        int mid = (l + r) >> 1;
        for(int i = 1;i <= n;i++) W[i] = A[i];
        wst = 0;
        if(dfs(mid,mid,1)) ans = mid,l = mid + 1;
        else r = mid - 1;
    }
    
    printf("%d\n",ans);
    
    return 0;
}
