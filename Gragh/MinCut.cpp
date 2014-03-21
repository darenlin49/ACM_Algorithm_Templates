/**
	【POJ 2676】给出一个带权无向图，求割集，且割集的平均边权最小，并输出割边集。
	【最小割算法：割点集、割边集】
		通常我们说的最小割都是最小边割，对应求的也就是最小边割集。如果要求最小点割集，则拆点转换为边割就行了。
		求割点集分两步：
			(Δ)先求得最大流，再在得到最大流f后的残留网络Gf中，从s开始DFS，所有被遍历到的点，即构成点集S。其余的点即构成点集T（不需要再从T遍历，挺麻烦）。
		注意：(Δ)虽然最小割[S,T]中的边都是满流边，但满流边不一定都是最小割中的边。
		求割边集：
			(Δ)先求出割点集，然后枚举满流边，如果边的两个端点分别在S集和T集中，则该边是割边。
	【本题思路：01分数规划】
		先尝试着用更一般的形式重新叙述本问题。设向量w表示边的权值，令向量c=(1, 1, 1, ……, 1)表示选边的代价，于是原问题等价为：
			Minimize   λ = f(x) = sigma(wexe)/sigma(1*xe) = w?x / c?x
		其中， x表示一个解向量，xe∈{0, 1} ，即对于每条边都有选与不选两种决策，并且选出的边集组成一个s-t边割集。
		联系已有的知识，这是一个0-1分数规划。在胡伯涛《最小割模型在信息学竞赛中的应用》中已经给出了这类规划的普遍转化方法：构造一个新函数g(λ) = min {(w-λc)?x}
		即对每条边∨e ∈ E ，进行重赋权：we‘ = we – ce?λ = we - λ。g(λ)便是在这个重新赋权的图上，求一个最小容量的s-t边割集。注意一些细节：若we’ < 0，又由于目标函数是加和取最小的操作，则该边必然是在边割集内。对于剩下的所有we‘ > 0的边，直接利用最小割模型求出s-t割即可。
		于是主算法便是对最优解*λ的二分查找，每次查找用最小割模型来判定，进而缩小查找范围，直到满足精度要求
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