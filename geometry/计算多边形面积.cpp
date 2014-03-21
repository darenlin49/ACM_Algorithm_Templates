#include<cstdio>
#include<cmath>
struct point
{
	double x,y;
}p[1000];

double area_polygon(int n,point* p)
{
	double s1=0.0,s2=0.0;
	int i;
	for(i=1;i<=n;i++)
	{
		s1+=p[(i+1)%n].y*p[i].x;
		s2+=p[(i+1)%n].y*p[(i+2)%n].x;
	}
	return fabs(s1-s2)/2.0;
}

int main()
{
	int n;
	while(scanf("%d",&n)!=EOF)
	{
		int i;
		for(i=1;i<=n;i++)
			scanf("%lf%lf",&p[i].x,&p[i].y);
		printf("%.4lf\n",area_polygon(n,p));
	}
	return 0;
}
