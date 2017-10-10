#include <cstdio>

int in,cnt,lst,n;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&in);
		if(in==lst)cnt++;
		else if(!cnt)lst=in,cnt=1;
		else cnt--;
	}
	
	printf("%d\n",lst);
	
	return 0;
}
