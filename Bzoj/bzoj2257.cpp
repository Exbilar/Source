#include <bits/stdc++.h>

using std :: max;
using std :: min;
using std :: map;

const int maxm = 1e6 + 10;

template <class T> bool chkmax(T &x, const T y) {
	return x < y ? x = y, true : false;
}

template <class T> bool chkmin(T &x, const T y) {
	return x > y ? x = y, true : false;
}

template <class T> void read(T &in) {
	in = 0; T f = 1; char ch = getchar();
	for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for(; isdigit(ch); ch = getchar()) in = in * 10 + ch - '0';
	in = in * f;
}

map<int, int> mmp;

int ai[maxm];

int n, k;

int main() {
	read(n); read(k);
	for(int i = 1; i <= n; i++) read(ai[i]);

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j * j <= ai[i]; j++) {
			if(ai[i] % j == 0) {
				mmp[j]++;
				if(ai[i] / j != j && ai[i] % (ai[i] / j) == 0) {
					mmp[ai[i] / j]++;
				}
			}
		}
	}

	int ans = 0;
	
	for(map<int, int> :: iterator itr = mmp.begin(); itr != mmp.end(); itr++) {
		if(itr -> second >= k) chkmax(ans, itr -> first);
	}

	printf("%d\n", ans);

	return 0;
}
