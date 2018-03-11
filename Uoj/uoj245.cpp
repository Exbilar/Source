#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define clr(x) memset(x,0,sizeof x)
#define RG register

#define px first
#define py second

using std :: max;
using std :: min;
using std :: pair;
using std :: make_pair;

typedef long long LL;
typedef pair<LL, LL> pll;
typedef pair<int, int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 1e6 + 10;

template <class T> inline bool chkmax(T &x, T y) {
    return x < y ? x = y,true : false;
}

template <class T> inline bool chkmin(T &x, T y) {
    return x > y ? x = y,true : false;
}

template <class T> inline void read (T &in) {
    in = 0; char ch = getchar(); T f = 1;
    for (;ch > '9' || ch < '0';ch = getchar()) if (ch == '-') f = -1;
    for (;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

int qmax[maxm],qmin[maxm],ai[maxm],ans[maxm];
int n;

int calc(int x) {
	int maxhead = 1, maxtail = 0;
	int minhead = 1, mintail = 0;
	int res = 0, cur = 1;
	for(int i = 1;i <= n;i++) {
		while(maxhead <= maxtail && ai[qmax[maxtail]] < ai[i]) maxtail--;
		while(minhead <= mintail && ai[qmin[mintail]] > ai[i]) mintail--;
		qmax[++maxtail] = i; qmin[++mintail] = i;
		while(cur <= n && ai[qmax[maxhead]] - ai[qmin[minhead]] > x) {
			if(qmax[maxhead] == cur) maxhead++;
			if(qmin[minhead] == cur) minhead++;
			cur++;
		}
		chkmax(res, i - cur + 1);
	}
	return res;
}

int main() {

	read(n);
	for(int i = 1;i <= n;i++) read(ai[i]);

	for(int now = 0, l = 2; l <= n; now = max(now + 1, (int) (now * 1.05))) {
		int r = calc(now);
		while(l <= r) ans[l++] = now;
	}

	for(int i = 2;i <= n;i++) printf("%d\n", ans[i]);

	return 0;
}
