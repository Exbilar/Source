#include <cstdio>
#include <cstring>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const int INF = 1 << 30;

char str[maxm],ch[10];
int n,m,pos,ans;

int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",str + 1);
	for(int i = 1;i < n;i++)
		if(str[i] == '.' && str[i + 1] == '.') ans++;
	
	while(m--){
		scanf("%d",&pos);
		scanf("%s",ch + 1);
		if(ch[1] == '.' && str[pos] == '.') goto nxt;
		if(ch[1] != '.' && str[pos] != '.') goto nxt;
		if(str[pos - 1] == '.' && ch[1] == '.') ans++;
		if(str[pos + 1] == '.' && ch[1] == '.') ans++;
		if(str[pos + 1] == '.' && ch[1] != '.') ans--;
		if(str[pos - 1] == '.' && ch[1] != '.') ans--;
		str[pos] = ch[1];
		
	nxt: printf("%d\n",ans);
	}

	return 0;
}
