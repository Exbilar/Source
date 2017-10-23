#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

int m;
int opt,x;

int main(){
    tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>bbt;
    tree<int,null_type,less<int>,splay_tree_tag,tree_order_statistics_node_update>splay;
    scanf("%d",&m);

    while(m--){
	scanf("%d",&opt);
	if(opt==1)scanf("%d",&x),bbt.insert(x);
	else if(opt==2)scanf("%d",&x),bbt.erase(x);
	else if(opt==3)scanf("%d",&x),printf("%d\n",bbt.order_of_key(x)+1);
	else if(opt==4)scanf("%d",&x),printf("%d\n",*bbt.lower_bound(x));
	else if(opt==5)scanf("%d",&x),printf("%d\n",*bbt.find_by_order(x-1));
    }
    
    return 0;
}
