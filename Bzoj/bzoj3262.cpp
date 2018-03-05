#include <cstdio>
#include <algorithm>

using std :: max;
using std :: min;
using std :: sort;

static const int maxm = 2e6 + 10;

int ch[maxm][2],size[maxm],cnt[maxm],rt[maxm],rnk[maxm],v[maxm],st[maxm],num[maxm];
int sz,k,n,top;

struct element{
	int x,y,z,ans;
	bool operator < (const element &ele) const{
		return (x < ele.x) || (x == ele.x && y < ele.y) || (x == ele.x && y == ele.y && z < ele.z);
	}
}ele[maxm];

int chk(int x,int y){
	return x == y ? 2333 : x > y;
}

void upt(int x){
	size[x] = size[ch[x][0]] + size[ch[x][1]] + cnt[x];
}

void rotate(int &x,int f){
	int t = ch[x][f];
	ch[x][f] = ch[t][f ^ 1];
	ch[t][f ^ 1] = x;
	size[t] = size[x];
	upt(x);x = t;
}

void insert(int &x,int val){
	if(!x) return x = ++sz,size[x] = cnt[x] = 1,rnk[x] = rand(),v[x] = val,void();
	size[x]++;
	if(v[x] == val) return cnt[x]++,void();
	int f = chk(val,v[x]);
	insert(ch[x][f],val);
	if(rnk[x] < rnk[ch[x][f]]) rotate(x,f);
}

int Qrank(int x,int val){
	if(!x) return 0;
	if(v[x] == val) return size[ch[x][0]] + cnt[x];
	return val < v[x] ? Qrank(ch[x][0],val) : Qrank(ch[x][1],val) + size[ch[x][0]] + cnt[x];
}

int lowbit(int x){
	return x & -x;
}

void Upt(int x,int y){
	for(int i = x;i <= k;i += lowbit(i))
		insert(rt[i],y);
}

int Qry(int x,int y){
	int ret = 0;
	for(int i = x;i;i -= lowbit(i))
		ret += Qrank(rt[i],y);
	return ret;
}

bool same(int i,int j){
	if(ele[i].x == ele[j].x && ele[i].y == ele[j].y && ele[i].z == ele[j].z) return true;
	return false;
}

int main(){
	
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;i++) scanf("%d%d%d",&ele[i].x,&ele[i].y,&ele[i].z);
	sort(ele + 1,ele + n + 1);
	for(int i = 1;i <= n;i++){
		if(same(i,i + 1)) st[++top] = i;
		else{
			ele[i].ans = Qry(ele[i].y,ele[i].z);
			while(top) ele[st[top--]].ans = ele[i].ans;
		}
		Upt(ele[i].y,ele[i].z);
	}

	for(int i = 1;i <= n;i++) num[ele[i].ans]++;

	for(int i = 0;i < n;i++) printf("%d\n",num[i]);
	
	return 0;
}
