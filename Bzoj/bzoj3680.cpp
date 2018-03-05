#include <cstdio>
#include <cmath>
#include <algorithm>

static const int maxm = 1e6 + 10;
static const double eps = 1e-8; 

struct point{
    double x,y;int w;
}pts[maxm];

int n;
double ansx,ansy;

double sqr(double x){
    return x*x;
}

double dis(double x,double y,point p){
    return std::sqrt(sqr(x-p.x)+sqr(y-p.y));
}

void climb(){
    double tmpt = 1000,x,y;
    
    for(int i = 1;i <= n;i++)
		ansx += pts[i].x * pts[i].w,ansy += pts[i].y * pts[i].w;
    
    ansx /= n; ansy /= n;
    
    while(tmpt > eps){
		x = y = 0;
		for(int i = 1;i <= n;i++){
			x += (pts[i].x - ansx) * pts[i].w / dis(ansx,ansy,pts[i]);
			y += (pts[i].y - ansy) * pts[i].w / dis(ansx,ansy,pts[i]);
		}
		ansx += x * tmpt,ansy += y * tmpt;
		if(tmpt>0.5) tmpt *= 0.5;
		else tmpt *= 0.97;
    }
    
    printf("%.3lf %.3lf\n",ansx,ansy);
}

int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++)
		scanf("%lf%lf%d",&pts[i].x,&pts[i].y,&pts[i].w);

    climb();  
    
    return 0;
}
