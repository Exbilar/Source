#include <bits/stdc++.h>
using namespace std;

using std :: max;
using std :: min;

typedef long long LL;

static const int INF = 1 << 30;

template <class T> void read(T &in){
    in = 0; int f = 1; char ch = getchar();
    for(;ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) in = in * 10 + ch - '0';
    in = in * f;
}

template <class T> bool chkmax(T &x,T y){
    return x < y ? x = y,true : false;
}

template <class T> bool chkmin(T &x,T y){
    return x > y ? x = y,true : false;
}

int main(){
    srand(time(NULL));

    system("g++ -o my my.cpp -g");
    system("g++ -o make make.cpp -g");
    system("g++ -o std std.cpp -g");

    int tot = 0;
    while(1){
		system("./make > make.in");
		system("./std <make.in>std.out");
		system("./my <make.in>my.out");
		int f = system("diff my.out std.out");
		if(f) return puts("x"),0;
		printf("testdata : %d Accepted\n",++tot);
    }

    return 0;
}
