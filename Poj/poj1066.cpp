#include <cmath>
#include <cstdio>
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
static const int maxm = 100 + 10;
static const double eps = 1e-9;

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

struct Point{
	double x, y;

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
		scanf("%lf%lf", &x, &y);
	}
	
}pts[maxm], des;

struct Line {
	Point s, t;
	Line() {}
	Line(const Point &s, const Point &t) : s(s), t(t) {}

	inline bool isIntersect(const Line &rhs) const {
		double d1 = ((rhs.t - rhs.s) * (s - rhs.s)) * ((rhs.t - rhs.s) * (t - rhs.s));
		double d2 = ((t - s) * (rhs.s - s)) * ((t - s) * (rhs.t - s));
		return
			max(s.x, t.x) >= min(rhs.s.x, rhs.t.x) &&
			max(s.y, t.y) >= min(rhs.s.y, rhs.t.y) &&
			max(rhs.s.x, rhs.t.x) >= min(s.x, t.x) &&
			max(rhs.s.y, rhs.t.y) >= min(s.y, t.y) &&
			d1 < -eps && d2 < -eps;
	}
}L[maxm], tmp;

int n;

int main() {
	
	while(scanf("%d", &n) != EOF) {
		int tot = 0;
		for(int i = 0; i < n; i++) {
			pts[++tot].get(); pts[++tot].get();
			L[i].s = pts[tot - 1]; L[i].t = pts[tot];
		}

		pts[++tot].x = 0; pts[tot].y = 0;
		pts[++tot].x = 0; pts[tot].y = 100;
		pts[++tot].x = 100; pts[tot].y = 0;
		pts[++tot].x = 100; pts[tot].y = 100;

		des.get();

		int ans = 1000, cnt;
		for(int i = 1; i <= tot; i++) {
			tmp.s = des; tmp.t = pts[i]; cnt = 0;
			for(int j = 0; j < n; j++) {
				if(tmp.isIntersect(L[j])) cnt++;
			}
			chkmin(ans, cnt);
		}
		printf("Number of doors = %d\n", ans + 1);
	}
	
	return 0;
}
