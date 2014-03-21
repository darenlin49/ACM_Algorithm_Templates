/**
	��POJ 2676������һ����Ȩ����ͼ�������Ҹ��ƽ����Ȩ��С���������߼���
	����С���㷨����㼯����߼���
		ͨ������˵����С�����С�߸��Ӧ���Ҳ������С�߸�����Ҫ����С��������ת��Ϊ�߸�����ˡ�
		���㼯��������
			(��)���������������ڵõ������f��Ĳ�������Gf�У���s��ʼDFS�����б��������ĵ㣬�����ɵ㼯S������ĵ㼴���ɵ㼯T������Ҫ�ٴ�T������ͦ�鷳����
		ע�⣺(��)��Ȼ��С��[S,T]�еı߶��������ߣ��������߲�һ��������С���еıߡ�
		���߼���
			(��)�������㼯��Ȼ��ö�������ߣ�����ߵ������˵�ֱ���S����T���У���ñ��Ǹ�ߡ�
	������˼·��01�����滮��
		�ȳ������ø�һ�����ʽ�������������⡣������w��ʾ�ߵ�Ȩֵ��������c=(1, 1, 1, ����, 1)��ʾѡ�ߵĴ��ۣ�����ԭ����ȼ�Ϊ��
			Minimize   �� = f(x) = sigma(wexe)/sigma(1*xe) = w?x / c?x
		���У� x��ʾһ����������xe��{0, 1} ��������ÿ���߶���ѡ�벻ѡ���־��ߣ�����ѡ���ı߼����һ��s-t�߸��
		��ϵ���е�֪ʶ������һ��0-1�����滮���ں����Ρ���С��ģ������Ϣѧ�����е�Ӧ�á����Ѿ�����������滮���ձ�ת������������һ���º���g(��) = min {(w-��c)?x}
		����ÿ���ߡ�e �� E �������ظ�Ȩ��we�� = we �C ce?�� = we - �ˡ�g(��)������������¸�Ȩ��ͼ�ϣ���һ����С������s-t�߸��ע��һЩϸ�ڣ���we�� < 0��������Ŀ�꺯���ǼӺ�ȡ��С�Ĳ�������ñ߱�Ȼ���ڱ߸�ڡ�����ʣ�µ�����we�� > 0�ıߣ�ֱ��������С��ģ�����s-t��ɡ�
		�������㷨���Ƕ����Ž�*�˵Ķ��ֲ��ң�ÿ�β�������С��ģ�����ж���������С���ҷ�Χ��ֱ�����㾫��Ҫ��
**/
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#define MID(x,y) ((x+y)/2)
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
const int MAXV = 105;
const int MAXE = 1005;
const int oo = 0x3fffffff;
const double eps = 1e-2;
bool dy(double x,double y)  {   return x > y + eps;} 		// x > y
bool xy(double x,double y)  {   return x < y - eps;} 		// x < y
bool dyd(double x,double y) {   return x > y - eps;} 		// x >= y
bool xyd(double x,double y) {   return x < y + eps;}     	// x <= y
bool dd(double x,double y)  {   return fabs( x - y ) < eps;}    // x == y

template <typename T>
struct Dinic{
    struct node{
        int u, v;
        T flow;
        int opp;
        int next;
    }arc[2*MAXE];
    int vn, en, head[MAXV];
    int cur[MAXV];
    int q[MAXV];
    int path[2*MAXE], top;
    int dep[MAXV];
    void init(int n){
        vn = n;
        en = 0;
        mem(head, -1);
    }
    void insert_flow(int u, int v, T flow){
        arc[en].u = u;
        arc[en].v = v;
        arc[en].flow = flow;
        arc[en].next = head[u];
        head[u] = en ++;
 
        arc[en].u = v;
        arc[en].v = u;
        arc[en].flow = 0;
        arc[en].next = head[v];
        head[v] = en ++;
    }
    bool bfs(int s, int t){
        mem(dep, -1);
        int lq = 0, rq = 1;
        dep[s] = 0;
        q[lq] = s;
        while(lq < rq){
            int u = q[lq ++];
            if (u == t){
                return true;
            }
            for (int i = head[u]; i != -1; i = arc[i].next){
                int v = arc[i].v;
                if (dep[v] == -1 && arc[i].flow > 0){
                    dep[v] = dep[u] + 1;
                    q[rq ++] = v;
                }
            }
        }
        return false;
    }
    T solve(int s, int t){
        T maxflow = 0;
        while(bfs(s, t)){
            int i, j;
            for (i = 1; i <= vn; i ++)  cur[i] = head[i];
            for (i = s, top = 0;;){
                if (i == t){
                    int mink;
                    T minflow = 0x3fffffff;
                    for (int k = 0; k < top; k ++)
                        if (minflow > arc[path[k]].flow){
                            minflow = arc[path[k]].flow;
                            mink = k;
                        }
                    for (int k = 0; k < top; k ++)
                        arc[path[k]].flow -= minflow, arc[path[k]^1].flow += minflow;
                    maxflow += minflow;
                    top = mink;
                    i = arc[path[top]].u;
                }
                for (j = cur[i]; j != -1; cur[i] = j = arc[j].next){
                    int v = arc[j].v;
                    if (arc[j].flow && dep[v] == dep[i] + 1)
                        break;
                }
                if (j != -1){
                    path[top ++] = j;
                    i = arc[j].v;
                }
                else{
                    if (top == 0)   break;
                    dep[i] = -1;
                    i = arc[path[-- top]].u;
                }
            }
        }
        return maxflow;
    }
};
Dinic <double> dinic;
 
int n, m;
struct path{
    int u, v;
    double cost;
}p[MAXE];
int st[MAXV];
bool vis[MAXV];
void dfs(int u, int p){
    st[u] = p;
    vis[u] = 1;
    for (int i = dinic.head[u]; i != -1; i = dinic.arc[i].next){
        if (dinic.arc[i].flow <= 0) continue;
        int v = dinic.arc[i].v;
        if (!vis[v]){
            dfs(v, p);
        }
    }
    return ;
}
double min_cut(double r){
    double res = 0.0;
    dinic.init(n);
    for (int i = 0; i < m; i ++){
        if (p[i].cost - r < 0){
            res += p[i].cost - r;
        }
        else{
            dinic.insert_flow(p[i].u, p[i].v, p[i].cost - r);
            dinic.insert_flow(p[i].v, p[i].u, p[i].cost - r);
        }
    }
    res += dinic.solve(1, n);
    return res;
}
int main(){
	//freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);
    int ca = 1;
    while(scanf("%d %d", &n, &m) != EOF){
        if (ca > 1)
            printf("\n");
        double max_cost = 0.0;
        for (int i = 0; i < m; i ++){
            scanf("%d %d %lf", &p[i].u, &p[i].v, &p[i].cost);
            max_cost = max(max_cost, p[i].cost);
        }
        double l = 0, r = max_cost;
        while(xy(l, r)){
            double mid = MID(l, r);
            double cut = min_cut(mid);
            if (xy(cut, 0)){
                r = mid;
            }
            else{
                l = mid;
            }
        }
        mem(st, 0);
        mem(vis, 0);
        dfs(1, 1);
        int counts = 0;
        vector <int> cuts;
        cuts.clear();
        for (int i = 0; i < m; i ++){
            if (p[i].cost - r < 0 || st[p[i].u] != st[p[i].v]){
                cuts.push_back(i+1);
                counts ++;
            }
        }
        printf("%d\n", counts);
        for (int i = 0; i < counts; i ++){
            if (i == 0) printf("%d", cuts[i]);
            else    printf(" %d", cuts[i]);
        }
        printf("\n");
        ca ++;
    }
	return 0;
}