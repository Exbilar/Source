#include <cstdio>
#include <cstring>
#include <algorithm>

using std :: min;
using std :: max;

static const int maxm = 1e3 + 10;
static const int maxn = 1e4 + 10;
static const int INF = 1 << 30;

template <class T> void read(T &in){
	in = 0; int f = 1; char ch = getchar();
	for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
	for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

struct node{
	int P,L,H;
	bool operator < (const node &N) const {
		return P < N.P;
	}
}pts[maxm];

int f[maxn][maxm],X[maxn],Y[maxn],get[maxn];
int n,m,k;

int main(){		
	read(n),read(m),read(k);
	for(register int i = 0;i < n;i++) read(X[i]),read(Y[i]);
	for(register int i = 1;i <= k;i++)
		read(pts[i].P),read(pts[i].L),read(pts[i].H);
    
	std :: sort(pts + 1,pts + k + 1);
	for(register int i = 1;i <= k;i++) get[pts[i].P] = i;
	
	for(register int i = 0;i <= n;i++)
		for(register int j = 0;j <= m;j++) f[i][j] = INF;
	
	for(register int i = 1;i <= m;i++) f[0][i] = 0;
	
	int tot = 0;
	
	/*
	for(register int i = 0;i < n;i++){
		if(get[i]){
			tot++;
			for(register int j = pts[get[i]].L + 1;j <= pts[get[i]].H - 1;j++){
				if(j - Y[i] <= 0) continue;
				f[i + 1][j - Y[i]] = min(f[i][j],f[i + 1][j - Y[i]]);
			}
			
			for(register int j = pts[get[i]].L + 1;j <= pts[get[i]].H - 1;j++){
				for(int k = 1;k >= 0;k++){
					if(j + k * X[i] <= m)
						f[i + 1][j + k * X[i]] = min(f[i][j] + k,f[i + 1][j + k * X[i]]);
					else f[i + 1][m] = min(f[i][j] + k,f[i + 1][m]);
					
					if(j + k * X[i] > m) break;
				}
			}
			int fl = 0;
			for(register int j = 1;j <= m;j++){
				if(f[i + 1][j] < INF){
					fl = 1;
					break;
				}
			}
			if(!fl) return printf("%d\n%d\n",0,tot - 1),0;
		}
		else{
			for(register int j = 1;j <= m;j++){
				if(j - Y[i] <= 0) continue;
				f[i + 1][j - Y[i]] = min(f[i][j],f[i + 1][j - Y[i]]);
			}
			
			for(register int j = 1;j <= m;j++){
				for(register int k = 1;k >= 0;k++){
					if(j + k * X[i] <= m)
						f[i + 1][j + k * X[i]] = min(f[i][j] + k,f[i + 1][j + k * X[i]]);
					else f[i + 1][m] = min(f[i][j] + k,f[i + 1][m]);
					
					if(j + k * X[i] > m) break;
				}
			}
		}
	}
	*/
	
	for(int i = 1;i <= n;i++){
		if(get[i]){
			tot++;						
			for(int j = 1;j <= m;j++){
				if(j - X[i - 1] >= 1) f[i][j] = min(f[i][j],f[i - 1][j - X[i - 1]] + 1),
										  f[i][j] = min(f[i][j],f[i][j - X[i - 1]] + 1);
				if(j == m){
					for(int k = m - X[i - 1] + 1;k <= m;k++)
						f[i][j] = min(f[i][j],f[i - 1][k] + 1),
							f[i][j] = min(f[i][j],f[i][k] + 1);
				}
			}
			
			for(int j = 1;j <= m;j++){
				if(j + Y[i - 1] <= m) f[i][j] = min(f[i - 1][j + Y[i - 1]],f[i][j]);
			}
			
			int fl = 0;
			for(int j = pts[get[i]].L + 1;j <= pts[get[i]].H - 1;j++){
				if(f[i][j] < INF){
					fl = 1;
					break;
				}
			}
			if(!fl) return printf("%d\n%d\n",0,tot - 1),0;
			
			for(int j = 0;j <= pts[get[i]].L;j++) f[i][j] = INF;
			for(int j = pts[get[i]].H;j <= m;j++) f[i][j] = INF;
		}
		else{			
			for(int j = 1;j <= m;j++){
				if(j - X[i - 1] >= 1)
					f[i][j] = min(f[i][j],f[i - 1][j - X[i - 1]] + 1),
						f[i][j] = min(f[i][j],f[i][j - X[i - 1]] + 1);
				if(j == m){
					for(int k = m - X[i - 1] + 1;k <= m;k++)
						f[i][j] = min(f[i][j],f[i - 1][k] + 1),
							f[i][j] = min(f[i][j],f[i][k] + 1);
				}
			}
			for(int j = 1;j <= m;j++){
				if(j + Y[i - 1] <= m) f[i][j] = min(f[i - 1][j + Y[i - 1]],f[i][j]);
			}
		}
	}
	
	int ans = INF;
	for(register int i = 1;i <= m;i++)
		ans = min(ans,f[n][i]);

	if(ans < INF) printf("%d\n%d\n",1,ans);
	
	/*	
	for(int i = 0;i <= n;i++){
		for(int j = 1;j <= m;j++){
			printf("%d ",f[i][j]);
		}
		putchar(10);
	}
	*/
	
	return 0;
}
