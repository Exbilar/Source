#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define id first
#define val second

typedef pair<int,int> pii;

static const int maxm=1e3+10;
static const int INF=~(1<<31);

int v[maxm][maxm],mx[maxm][maxm],mn[maxm][maxm],Max[maxm],Min[maxm];
pii Q[maxm];
int head,tail,A,B,n;

int main(){
	scanf("%d%d%d",&A,&B,&n);
	for(int i=1;i<=A;i++)
		for(int j=1;j<=B;j++)
			scanf("%d",&v[i][j]);
	
	for(int i=1;i<=A;i++){
		head=1,tail=1;
		for(int j=1;j<=B;j++){
			while(head<=tail&&Q[tail].val<=v[i][j])tail--;
			Q[++tail].val=v[i][j];Q[tail].id=j;
			while(head<=tail&&Q[head].id<j-n+1)head++;
			if(j>=n)mx[i][j]=Q[head].val;
		}
		head=1,tail=1;
		for(int j=1;j<=B;j++){
			while(head<=tail&&Q[tail].val>=v[i][j])tail--;
			Q[++tail].val=v[i][j];Q[tail].id=j;
			while(head<=tail&&Q[head].id<j-n+1)head++;
			if(j>=n)mn[i][j]=Q[head].val;
		}
	}
	int ans=INF;
	for(int i=n;i<=B;i++){
		head=1,tail=1;
		for(int j=1;j<=A;j++){
			while(head<=tail&&Q[tail].val>=mn[j][i])tail--;
			Q[++tail].val=mn[j][i];Q[tail].id=j;
			while(head<=tail&&Q[head].id<j-n+1)head++;
			if(j>=n)Min[j]=Q[head].val;
		}
		head=1,tail=1;
		for(int j=1;j<=A;j++){
			while(head<=tail&&Q[tail].val<=mx[j][i])tail--;
			Q[++tail].val=mx[j][i];Q[tail].id=j;
			while(head<=tail&&Q[head].id<j-n+1)head++;
			if(j>=n)Max[j]=Q[head].val;
		}
		for(int j=n;j<=A;j++)ans=min(ans,Max[j]-Min[j]);
	}
	
	printf("%d\n",ans);
	
	return 0;
}
