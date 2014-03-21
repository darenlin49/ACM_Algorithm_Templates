/*
	��POJ 2728��ÿ��·����һ�� cost �� dist����ͼ�� sigma(cost) / sigma(dist) ��С����������
	��01�����滮��
	�㶨�壺
		�����滮��fractional programming����һ����ʽ��
			Minimize  �� = f(x) = a(x) / b(x)   ( x��S  && ?x��S, b(x) > 0 )
		���У�������x�ڽ�ռ�S�ڣ� a(x)��b(x)����������ʵֵ������
		�����滮��һ��������0-1�����滮(0-1 fractional programming)�������������x����?xi��{0,1}���������ν��0-1������ʽ���������£�
			Minimize  �� = f(x) = a?x / b?x = sigma(a*x) / sigma(b*x) ( x��{0,1}^n && b?x > 0 )
		���ҶԽ�����x���ܻ���������������ƣ���Щ��Խ�����x�Ĳ�ͬ����Ҳ������01�����滮�Ĳ�ͬģ�ͣ��������ű��������������ű������ɻ������ű��ʸ��
	��ⷨ
		���������Ѿ�֪�������մ𰸦ˣ���ô���̾Ϳ���дΪ�� sigma(ax*) = sigma(bx*)?�ˣ� ��sigma(ax*) �C sigma(bx*)?�� = 0
		��g(��) = min(x��S){ sigma(ax) �C ��?sigma(bx) }�� ��֪�ú��������ݼ�������*��Ϊ�ù滮�����Ž⣬��
			g(��) = 0 ? �� = *�ˣ� g(��) > 0 ? �� < *�ˣ� g(��) < 0 ? �� > *��
		�������ǾͿ��Զ���ö�٦ˣ�Ȼ���ж�g(��)�Ƿ����0������g(��)�ļ���Ҫ���ݲ�ͬģ�ͣ�����x�Ĳ�ͬ���ƣ���������
	��Dinkelbach�����㷨��
		��ͬ�ڸղŵĶ���ö�٣��㷨����ţ�ٵ����ķ�ʽ����ˡ�
			�ٳ�ʼ���0 = 0
			�ڼ���g(��0)�����ҵõ����Ž�*x
			�ۼ���*�� = a?*x / b?*x�� ���*�� = ��0���㷨�������������0 = *�ˣ����������.
		�����ȶ����ٶȿ�ܶ࣬���Ҳ��ÿ��Ƕ��ֵ��Ͻ硣
	�����ű����������ⷨ��
		�ص����⣬�ͱ����������ű���������������ö�٦ˣ���ô���ж�g(��) = min(x��S){ (cost-��*dist)?x }�Ƿ����0.
		������g(��)���ǰ�ԭͼ�е�ÿ���ߵ�Ȩֵ����Ϊcost-��*dist��Ȼ������С����������.
*/
#include <stdio.h>
#include <math.h>
//����ģ��
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