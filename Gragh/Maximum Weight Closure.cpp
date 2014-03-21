/**
°最大权闭合图定义

	一个有向图G(V, E)的闭合图(closure(闭包?))是该有向图的一个点集，且该点集的所有出边也在该点集中。即闭合图内的任意点的后继也一定在闭合图中。给每一个点v分配一个点权Wv（任意实数，可正可负）。最大权闭合图(Maximum weight closure)，是一个点权最大的闭合图，即最大化Σv∈V’ Wv。

°构图&&解法

	将原图G(V, E)转化为流网络GN(VN,EN)。在原图点集的基础上增加源点S和汇点T；将原图每条有向边<u,v>∈E替换成容量为c(u,v) = ∞的有向边<u, v, ∞>∈EN；增加连接源点S到原图每个正权点v(Wv>0)的有向边<S, v, Wv>；增加连接原图每个负权点v(Wv<0)到汇点T的有向边<v, T, -Wv>。

	则最大权 = 正权和 – GN的最小割。证明参考胡伯涛论文《最小割模型在信息学竞赛中的应用》。

	且最小割把原图划分为S集和T集，S点集的点即为最大权闭合图中的点。
	
°时间复杂度 ：O(MAXFLOW(N))
**/
const int MAXV = 5005;
const int MAXE = 60005;
const int oo = 0x3fffffff;
 
/** Dinic最大流 **/
template <typename T>
struct Dinic{
    struct flow_node{
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
Dinic <long long> dinic;
 
/** 最大权闭合图 **/
int weight[MAXV];               //点权
struct Edge{
    int u, v;
}e[MAXE];
vector <int> ans_node;          //最大权闭合图中的点
bool vis[MAXV];
void find_nodes(int u, int s){
    vis[u] = 1;
    if (u != s)
        ans_node.push_back(u);
    for (int i = dinic.head[u]; i != -1; i = dinic.arc[i].next){
        if (dinic.arc[i].flow <= 0) continue;
        int v = dinic.arc[i].v;
        if (!vis[v]){
            find_nodes(v, s);
        }
    }
}
void MaximumWeightClosureOfaGragh(int nodes_num, int edges_num, long long &res, int &res_node_num){
    /* 求最大权和,返回res */
    long long positive_sum = 0;   //正权和
    dinic.init(nodes_num+2);
    for (int i = 1; i <= nodes_num; i ++){
        if (weight[i] >= 0){
            positive_sum += weight[i];
            dinic.insert_flow(nodes_num+1, i, weight[i]);
        }
        else{
            dinic.insert_flow(i, nodes_num+2, -weight[i]);
        }
    }
    for (int i = 0; i < edges_num; i ++){
        dinic.insert_flow(e[i].u, e[i].v, oo);
    }
    res = positive_sum - dinic.solve(nodes_num+1, nodes_num+2);
    /* 求最大权闭合图中的点 */
    ans_node.clear();
	mem(vis, 0);
    find_nodes(nodes_num+1, nodes_num+1);
    res_node_num = (int)ans_node.size();
    return ;
}
 
int main(){
	//freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);
    int n, m;
    while(scanf("%d %d", &n, &m) != EOF){
        for (int i = 1; i <= n; i ++){
            scanf("%d", &weight[i]);
        }
        for (int i = 0; i < m; i ++){
            scanf("%d %d", &e[i].u, &e[i].v);
        }
        long long res;
        int res_node;
        MaximumWeightClosureOfaGragh(n, m, res, res_node);
        printf("%d %I64d\n", res_node, res);
    }
	return 0;
}