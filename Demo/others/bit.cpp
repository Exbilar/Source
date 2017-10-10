#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

static const int maxm=1e5+10;

int n,m;

namespace Exstream{
    
    const int L = 1<<15;
    char buffer[L],*S,*T;
    
    inline char Getchar(){
        if(S == T) T = (S=buffer)+fread(buffer,1,L,stdin);
        return S == T? EOF : *S++;
    }
    
    template <class T> inline void read(T &in){
        char ch;int f = 1;
        for(ch = Getchar();ch > '9' || ch < '0';ch = Getchar()) if(ch == '-') f = -1;
        for(in = 0;ch >= '0' && ch <= '9';ch = Getchar()) in = (in<<1) + (in<<3) + ch - '0';
        in *= f;
    }
    
}

struct BIT{
	LL tr1[maxm],tr2[maxm];
	BIT(){std::memset(tr1,0,sizeof tr1),memset(tr2,0,sizeof tr2);}
	
	int lowbit(int x){
		return x&-x;
	}
	
	void Upt(int k,int val){
		for(int i=k;i<=n;i+=lowbit(i))
			tr1[i]+=val,tr2[i]+=1LL*k*val;
	}
	LL Query(int k){
		LL ret=0;
		for(int i=k;i;i-=lowbit(i))
			ret+=(k+1)*tr1[i]-tr2[i];
		return ret;
	}
}bit;

int main(){
	using namespace Exstream;
	LL x;int l,r,opt;
	read(n);read(m);
	for(int i=1;i<=n;i++)read(x),bit.Upt(i,x),bit.Upt(i+1,-x);
	
	while(m--){
		read(opt);read(l);read(r);
		if(opt==1)
			read(x),bit.Upt(l,x),bit.Upt(r+1,-x);
		else
			printf("%lld\n",bit.Query(r)-bit.Query(l-1)); 
	}
	
	return 0;
}
