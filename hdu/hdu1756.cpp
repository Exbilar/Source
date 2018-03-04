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
static const int maxm = 10000 + 10;

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
	int x, y;
	
    Point(int x = 0, int y = 0) : x(x), y(y) {}

	inline Point operator + (const Point &rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}

	inline Point operator - (const Point &rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}

	inline int operator * (const Point &rhs) const {
		return x * rhs.y - y * rhs.x;
	}

	inline int operator ^ (const Point &rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	inline void get() {
		read(x); read(y);
	}
	
};

bool isPointOnSegment(const Point &x,const Point &y,const Point &p) {
	return (x - p) * (y - p) == 0 &&
		p.x >= min(x.x,y.x) && p.x <= max(x.x,y.x) &&
		p.y >= min(x.y,y.y) && p.y <= max(x.y,y.y);
}

struct Polygon {
	Point pts[maxm];
	int n;

	Polygon(int n = 0) : n(n) {}

	int area() {
		int res = 0;
		for(int i = 0;i < n;i++) res += pts[i] * pts[i + 1];
		return res >> 1;
	}

	void fix() {
		pts[n] = pts[0];
		if(area() < 0) std :: reverse(pts,pts + n);
		pts[n] = pts[0];
	}

	inline bool contain(const Point &p) {
		int cnt = 0;
		for(int i = 0;i < n;i++) {
			if(isPointOnSegment(pts[i],pts[i + 1],p)) return true;
			int det = (pts[i] - p) * (pts[i + 1] - p);
			int d1 = pts[i].y - p.y,d2 = pts[i + 1].y - p.y;
			if((det >= 0 && d1 < 0 && d2 >= 0) ||
			   (det <= 0 && d1 >= 0 && d2 < 0)) cnt++;
		}
		return cnt & 1;
	}

	inline Point &operator [] (const int i) {
		return pts[i];
	}

}poly;

int main() {

	//freopen("hdu1756.in","r",stdin);
	
	int n,m; Point p;
	while(scanf("%d",&n) != EOF) {
		poly.n = n;
		for(int i = 0;i < n;i++) poly[i].get();
		poly.fix();
		read(m);
		while(m--) {
			p.get();
			if(poly.contain(p)) puts("Yes");
			else puts("No");
		}
	}

	return 0;
}
