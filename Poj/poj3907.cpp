#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

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
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;

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

struct Point {
	double x,y;

	Point(double x = 0, double y = 0) : x(x), y(y) {}

	Point operator + (const Point &rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}

	Point operator - (const Point &rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}

	double operator * (const Point &rhs) const {
		return x * rhs.y - y * rhs.x;
	}

	double operator ^ (const Point &rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	void get() {
		scanf("%lf%lf",&x,&y);
	}
	
}pts[maxm];

int n;

int main() {
	
	while(scanf("%d",&n) != EOF) {
		if(!n) return 0;
		
		double ans = 0.0;
		for(int i = 0;i < n;i++) pts[i].get();
		
		pts[n] = pts[0];
		for(int i = 0;i < n;i++) ans += pts[i] * pts[i + 1];
		printf("%d\n",abs((int) round(ans / 2 + 1e-6)));
	}

	return 0;
}
