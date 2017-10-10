#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long LL;

typedef pair<LL,int>pli;

static const int maxm=2e6+10;
static const LL INF=~(1<<31);

priority_queue< pli,vector<pli>,greater<pli> >Q;

int l[maxm],r[maxm];
bool vis[maxm];
LL val[maxm],d[maxm];
int n,k,m,cnt;
LL ans;

int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%lld",&d[i]);
    for(int i=1;i<n;i++){
	val[++cnt]=d[i+1]-d[i];
	Q.push(make_pair(val[cnt],cnt));
	l[cnt]=cnt-1;
	r[cnt]=cnt+1;
    }

    l[cnt+1]=cnt;val[0]=INF;
    r[0]=1;val[cnt+1]=INF;
    cnt++;
    
    for(int i=1;i<=k;i++){
	while(vis[Q.top().second])Q.pop();
	pli now=Q.top();Q.pop();
	int id=now.second;
	ans+=now.first;
	int rc=r[id];int lc=l[id];
	l[id]=l[lc];r[id]=r[rc];
	r[l[id]]=id;l[r[id]]=id;
	val[id]=val[rc]+val[lc]-now.first;
	vis[lc]=1;vis[rc]=1;
	Q.push(make_pair(val[id],id));
    }

    printf("%lld\n",ans);
    
    return 0;
}
