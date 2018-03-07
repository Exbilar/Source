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
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;

static const int INF = 1 << 30;
static const LL oo = 1LL << 60;
static const int maxm = 1e6 + 10;
static const double eps = 1e-8;

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
	double x, y;

	Point() {}
	Point(double _, double __) {x = _; y = __;}

	Point operator + (const Point &rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}

	Point operator - (const Point &rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}

	double operator * (const Point &rhs) const {
		return x * rhs.y - rhs.x * y;
	}

	double operator ^ (const Point &rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	double getDis(const Point &rhs) const {
		return sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y));
	}

	bool operator < (const Point &rhs) const {
		return fabs(x - rhs.x) < eps ? y < rhs.y : x < rhs.x;
	}
	
}pts[maxm], con[maxm];

int andrew(Point *pts, Point *con, const int n) {
	std :: sort(pts + 1, pts + n + 1);
	int top = 0;
	for(int i = 1; i <= n; i++) {
		while(top > 1 && (con[top] - con[top - 1]) * (pts[i] - con[top - 1]) <= 0) top--;
		con[++top] = pts[i];
	}
	int k = top;
	for(int i = n - 1; i >= 1; i--) {
		while(top > k && (con[top] - con[top - 1]) * (pts[i] - con[top - 1]) <= 0) top--;
		con[++top] = pts[i];
	}
	return top;
}

double dist(Point *pts, const int n) {
	double res = 0.0;
	for(int i = 1; i < n; i++) res += pts[i].getDis(pts[i + 1]);
	return res;
}

int n;

int main() {

	while(scanf("%d", &n) != EOF && n) {
		for(int i = 1; i <= n; i++) scanf("%lf%lf", &pts[i].x, &pts[i].y);
		int top = andrew(pts, con, n);
		double ans = dist(con, top);
		printf("%.2lf\n", n == 2 ? ans / 2 : ans);
	}

	return 0;
}
