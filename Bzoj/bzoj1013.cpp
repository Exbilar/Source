#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;
static const LL oo = 1LL << 62;
static const int maxm = 200 + 10;

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

double A[maxm][maxm],fst[maxm];
int n;

double sqr(double x){
	return x * x;
}

void print(){
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n + 1;j++){
			printf("%lf ",A[i][j]);
		}
		putchar(10);
	}
	putchar(10);
}

void gauss(){
	for(int i = 1;i <= n;i++){
		int pos = i;
		for(int j = i + 1;j <= n;j++){
			if(fabs(A[j][i]) > fabs(A[pos][i])) pos = j;
		}
		double cur = A[pos][i];
		for(int j = i;j <= n + 1;j++) std :: swap(A[i][j],A[pos][j]);
		for(int j = i;j <= n + 1;j++) A[i][j] /= cur;
		for(int k = 1;k <= n;k++){
			if(k == i) continue;
			cur = A[k][i];
			for(int j = i;j <= n + 1;j++) A[k][j] -= A[i][j] * cur;
		}
	}
}

int main(){

	read(n);

	for(int i = 1;i <= n;i++) scanf("%lf",&fst[i]);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			double tmp;
			scanf("%lf",&tmp);
			A[i][j] = 2 * (tmp - fst[j]);
			A[i][n + 1] += sqr(tmp) - sqr(fst[j]);
		}
	}
	
	gauss();

	for(int i = 1;i <= n - 1;i++) printf("%.3lf ",A[i][n + 1]);
	printf("%.3lf\n",A[n][n + 1]);

	return 0;
}
