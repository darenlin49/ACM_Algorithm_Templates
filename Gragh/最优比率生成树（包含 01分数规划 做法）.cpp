/*
	【POJ 2728】每条路径有一个 cost 和 dist，求图中 sigma(cost) / sigma(dist) 最小的生成树。
	【01分数规划】
	°定义：
		分数规划（fractional programming）的一般形式：
			Minimize  λ = f(x) = a(x) / b(x)   ( x∈S  && ?x∈S, b(x) > 0 )
		其中，解向量x在解空间S内， a(x)与b(x)都是连续的实值函数。
		分数规划的一个特例是0-1分数规划(0-1 fractional programming)，就是其解向量x满足?xi∈{0,1}（这就是所谓的0-1）。形式化定义如下：
			Minimize  λ = f(x) = a?x / b?x = sigma(a*x) / sigma(b*x) ( x∈{0,1}^n && b?x > 0 )
		并且对解向量x可能还有其他的组合限制，这些针对解向量x的不同限制也就有了01分数规划的不同模型：比如最优比率生成树、最优比率生成环、最优比率割……
	°解法
		假设我们已经知道了最终答案λ，那么方程就可以写为： sigma(ax*) = sigma(bx*)?λ， 即sigma(ax*) – sigma(bx*)?λ = 0
		令g(λ) = min(x∈S){ sigma(ax) – λ?sigma(bx) }， 易知该函数单调递减，且设*λ为该规划的最优解，则
			g(λ) = 0 ? λ = *λ； g(λ) > 0 ? λ < *λ； g(λ) < 0 ? λ > *λ
		所以我们就可以二分枚举λ，然后判断g(λ)是否等于0……而g(λ)的计算要根据不同模型（即对x的不同限制）具体解决。
	【Dinkelbach迭代算法】
		不同于刚才的二分枚举，算法采用牛顿迭代的方式来求λ。
			①初始设λ0 = 0
			②计算g(λ0)，并且得到最优解*x
			③计算*λ = a?*x / b?*x， 如果*λ = λ0，算法结束；否则令λ0 = *λ，继续步骤②.
		迭代比二分速度快很多，而且不用考虑二分的上界。
	【最优比率生成树解法】
		回到此题，就比如此题的最优比率生成树，二分枚举λ，那么就判断g(λ) = min(x∈S){ (cost-λ*dist)?x }是否等于0.
		而计算g(λ)就是把原图中的每条边的权值都改为cost-λ*dist，然后求最小生成树即可.
*/
#include <stdio.h>
#include <math.h>
//精度模板
const double eps = 1e-4;
bool dd(double x,double y)  {   return fabs( x - y ) < eps;}    // x == y
const int MAXV = 1003;
struct village{
    double x,y,z;
}v[MAXV];
double len[MAXV][MAXV];
double cost[MAXV][MAXV];
double dist[MAXV];
int pre[MAXV];
int n;
double prim(double r){
    bool vis[MAXV] = {0};
    double csum = 0.0, lsum = 0.0;
    dist[1] = 0.0;
    vis[1] = 1;
    for (int i = 2; i <= n; i ++){
        dist[i] = cost[1][i] - r * len[1][i];
        pre[i] = 1;
    }
    for (int p = 2; p <= n; p ++){
        double minx = 99999999.0;
        int u = -1;
        for (int i = 1; i <= n; i ++){
            if (!vis[i] && minx > dist[i]){
                minx = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        vis[u] = 1;
        csum += cost[pre[u]][u];
        lsum += len[pre[u]][u];
        for (int i = 2; i <= n; i ++){
            if (vis[i]) continue;
            double w = cost[u][i] - r * len[u][i];
            if (dist[i] > w){
                dist[i] = w;
                pre[i] = u;
            }
        }
    }
    return csum / lsum;
}
int main(){
	//freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);
    while(scanf("%d", &n), n){
        for (int i = 1; i <= n; i ++){
            scanf("%lf %lf %lf", &v[i].x, &v[i].y, &v[i].z);
        }
        for (int i = 1; i <= n; i ++){
            for (int j = i+1; j <= n; j ++){
                len[i][j] = len[j][i] = sqrt((v[i].x-v[j].x)*(v[i].x-v[j].x)+(v[i].y-v[j].y)*(v[i].y-v[j].y));
                cost[i][j] = v[i].z - v[j].z;
                cost[j][i] = cost[i][j] = cost[i][j] < 0 ? -cost[i][j] : cost[i][j];
            }
        }
        double a = 0, b;
        while(1){
            b = prim(a);
            if (dd(b, a)){
                break;
            }
            a = b;
        }
        printf("%.3f\n", a);
    }
	return 0;
}