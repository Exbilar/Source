#include <bits/stdc++.h>
using namespace std;

int main(){
	int tot = 0;
	system("g++ -o my my.cpp");
	system("g++ -o rand rand.cpp");
	system("g++ -o std std.cpp");
	while(1){
		system("./rand>rand.in");
		system("./my<rand.in>my.out");
		system("./std<rand.in>std.out");
		int f = system("diff std.out my.out");
		if(f) return printf("testdata : %d Wrong Answer\n",++tot),0;
		else printf("testdata : %d Accepted\n",++tot);
	}

	return 0;
}
