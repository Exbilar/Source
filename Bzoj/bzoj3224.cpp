#include <cstdio>
#include <algorithm>
using namespace std;

static const int maxm=1e6+10;
static const int INF=~(1<<31);

int rnk[maxm],v[maxm],cnt[maxm],size[maxm],ch[maxm][2];
int x,root,n,m,opt,ans,num;

void upt(int i){
    size[i]=size[ch[i][0]]+size[ch[i][1]]+cnt[i];
}

int chk(int a,int b){
    return a==b?11:a>b;
}

void rotate(int &i,int f){
    int t=ch[i][f];
    ch[i][f]=ch[t][f^1];
    ch[t][f^1]=i;
    size[t]=size[i];
    upt(i);i=t;
}

void insert(int &i,int x){
    if(!i){i=++num;v[i]=x;rnk[i]=rand();size[i]=cnt[i]=1;return;}
    size[i]++;
    if(v[i]==x){cnt[i]++;return;}
    int t=chk(x,v[i]);insert(ch[i][t],x);
    if(rnk[ch[i][t]]<rnk[i])rotate(i,t);
}

void remove(int &i,int x){
    if(!i)return;
    if(v[i]!=x)size[i]--,remove(ch[i][chk(x,v[i])],x);
    if(v[i]==x){
	if(cnt[i]>1){cnt[i]--;size[i]--;return;}
	if(ch[i][0]*ch[i][1]==0)i=ch[i][0]+ch[i][1];
	else rotate(i,chk(ch[i][0],ch[i][1])),remove(i,x);
    }
}

int Qrank(int i,int x){
    if(!i)return 0;
    if(v[i]==x)return size[ch[i][0]]+1;
    return x<v[i]?Qrank(ch[i][0],x):size[ch[i][0]]+cnt[i]+Qrank(ch[i][1],x);
}

int order(int i,int x){
    if(!i)return 0;
    if(x>cnt[i]+size[ch[i][0]])return order(ch[i][1],x-cnt[i]-size[ch[i][0]]);
    else return x<=size[ch[i][0]]?order(ch[i][0],x):v[i];
}

void Query(int i,int x,int f){
    if(!i)return ;
    if(chk(v[i],x)==f){ans=i;return Query(ch[i][f^1],x,f);}
    else return Query(ch[i][f],x,f);
}

int main(){
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&opt,&x);
        switch(opt){
        case 1:insert(root,x);break;
        case 2:remove(root,x);break;
        case 3:printf("%d\n",Qrank(root,x));break;
        case 4:printf("%d\n",order(root,x));break;
        case 5:ans=0;Query(root,x,0);printf("%d\n",v[ans]);break;
        case 6:ans=0;Query(root,x,1);printf("%d\n",v[ans]);break;
        }
    }

    return 0;
}
