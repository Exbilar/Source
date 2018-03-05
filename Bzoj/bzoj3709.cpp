#include <cstdio>
#include <algorithm>

typedef long long LL;

static const LL maxm = 2e5 + 10;

struct object{
	LL x,y,id;
}A[maxm],B[maxm];

LL n,cnt1,cnt2;
LL rem;

bool cmp1(const object &a,const object &b){
	return a.x < b.x;
}

bool cmp2(const object &a,const object &b){
	return a.y > b.y;
}

void calc(LL x,LL y){
	rem -= x;
	if(rem <= 0) puts("NIE"),exit(0);
	rem += y;
}

int main(){
	LL dx,dy;
	scanf("%lld%lld",&n,&rem);
	for(LL i = 1;i <= n;i++){
		scanf("%lld%lld",&dx,&dy);
		if(dx < dy){
			A[++cnt1].x = dx;
			A[cnt1].y = dy;
			A[cnt1].id = i;
		}else{
			B[++cnt2].x = dx;
			B[cnt2].y = dy;
			B[cnt2].id = i;
		}
	}

	std :: sort(A + 1,A + cnt1 + 1,cmp1);
	std :: sort(B + 1,B + cnt2 + 1,cmp2);

	for(LL i = 1;i <= cnt1;i++) calc(A[i].x,A[i].y);
	for(LL i = 1;i <= cnt2;i++) calc(B[i].x,B[i].y);

	puts("TAK");

	for(LL i = 1;i <= cnt1;i++) printf("%lld ",A[i].id);
	for(LL i = 1;i <= cnt2;i++) printf("%lld ",B[i].id);

	putchar(10);
	
	return 0;
}
