/*
	[Dinic]先用bfs在残量网络上构造层次图(层次图上任意路径都是最短增广路),然后在层次图上dfs多路增广.
	[时间复杂度]理论上界：O(V^2*E)，实际远达不到，VN <= 10000，EN <= 100000 可以考虑
	PS:本模板参考了dd_engi大牛的Dinic代码, 用PKU的1459 Power Network(多源多汇模板题)来测模版:79MS
*/

/** Dinic-2.0-2013.07.21: adds template.  double & int 转换方便多了，也不易出错 ~**/
const int MAXV = 105;
const int MAXE = 30005;
const int oo = 0x3fffffff;

template <typename T>
struct Dinic{
    struct flow_node{
        int u, v;
        T flow;
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
        MEM(head, -1);
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
        MEM(dep, -1);
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
                    T minflow = 0x7fffffff;						//要比容量的oo大
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
Dinic <int> dinic;

int main(){
    int n, np, nc, m;
    while(scanf("%d %d %d %d", &n, &np, &nc, &m) != EOF){
        dinic.init(n+2);
        for (int i = 0; i < m; i ++){
            int u, v, f;
            scanf("%*1s%d%*1s%d%*1s%d", &u, &v, &f);
            dinic.insert_flow(u+1, v+1, f);
        }
        for (int i = 0; i < np; i ++){
            int u, p;
            scanf("%*1s%d%*1s%d", &u, &p);
            dinic.insert_flow(n+1, u+1, p);     //超级源点
        }
        for (int i = 0; i < nc; i ++){
            int u, c;
            scanf("%*1s%d%*1s%d", &u, &c);
            dinic.insert_flow(u+1, n+2, c);     //超级汇点
        }
        printf("%d\n", dinic.solve(n+1, n+2));
    }
	return 0;
	return 0;
}
