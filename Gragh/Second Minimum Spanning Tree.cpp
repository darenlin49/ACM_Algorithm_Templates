/*
次小生成树(The second MST, 2-MST)

基本思想：首先求出最小生成树，记录权值之和为MST_NUM。然后枚举添加边(u,v)，加上以后一定形成一个环，找到环上非(u,v)边的权值最大的边，把它删掉，计算当前生成树的权值之和，取所有枚举加边后生成树权值之和的最小值，就是次小生成树。

算法：

1.求出最小生成树T及其权值和MST_NUM，并标注在最小生成树上的边。

2.从每个顶点i为根，DFS遍历最小生成树，求出从i到j的路径上最大边的权值P(i, j)。

3.遍历每条不在最小生成树中的边(i,j)，加上这条边，并删除环上最大边(P(i,j))，新的生成树权值之和为MST_NUM + w(i,j) - P[i][j]，记录其最小值即可，时间复杂度为O(N^2)。求最小生成树可以用最简单的Prim即可，算法的瓶颈在第二步DFS遍历求路径上最大边需要O(n^2)，用更好的算法是没有意义的。(PS：对于每个边，实际上可以用LCA和预处理来得到环内最大边，这样复杂度就是O(ElogV)，然后配合Kruskal复杂度可以降到O(ElogV), 留待以后学习。)

-----------------------------------------------------------
POJ 1679 The Unique MST  (MST是否唯一)

求出次小生成树，然后判断权值和是否等于最小生成树即可。

*/
const int MAXN = 103;
const int MAXE = 30003;
/* 链式前向星 */
struct node{        //gragh node
    int u, v, w;
    int op;         //无向边拆成两个有向边对应的另一个编号
    bool in_MST;    //是否在最小生成树中;
    int next;
}edge[MAXE];
int cnt, head[MAXN];
void Init(){
    cnt = 0;
    mem(head, -1);
}
void Add_edge(int u, int v, int w){     //添加无向边
    edge[cnt].in_MST = false;
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    edge[cnt].op = cnt + 1;
    head[u] = cnt ++;
 
    edge[cnt].in_MST = false;
    edge[cnt].u = v;
    edge[cnt].v = u;
    edge[cnt].w = w;
    edge[cnt].next = head[v];
    edge[cnt].op = cnt - 1;
    head[v] = cnt ++;
}
/* 链式前向星 */
 
struct prim_node{   //prim node
    int t;      //状态节点标号
    int id;     //第几个边
    int w;      //权值
    friend bool operator < (prim_node n1, prim_node n2){
        return n1.w > n2.w;
    }
    void Init(int n){
        id = -1;
        t = n;
        w = sup;
    }
}dist[MAXN];
bool vis[MAXN];
priority_queue <prim_node, vector<prim_node> > Q;
int MST_NUM;
void Prim(int start, int n){    	//初始MST_NUM=0，则对于不连通的图MST_NUM=0;
    mem(vis, 0);
    for (int i = 0; i <= n; i ++)
        dist[i].Init(i);
    while(!Q.empty())
        Q.pop();
    dist[start].w = 0;
    Q.push(dist[start]);
    while(!Q.empty()){
        prim_node tmp = Q.top();
        Q.pop();
        int u = tmp.t;
        int w = tmp.w;
        int id = tmp.id;
        if (vis[u]) continue;
        vis[u] = true;
        if (id != -1){      //确定最小生成树的边和权值和
            edge[id].in_MST = true;
            edge[edge[id].op].in_MST = true;
            MST_NUM += w;
        }
        for (int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].v;
            int cost = edge[i].w;
            if (!vis[v] && dist[v].w > cost){
                dist[v].w = cost;
                dist[v].id = i;
                Q.push(dist[v]);
            }
        }
    }
}
int max_cost_on_MST[MAXN][MAXN];
bool used[MAXN];
void dfs(int s, int t, int maxnum){
    max_cost_on_MST[s][t] = maxnum;
    used[t] = 1;
    for (int i = head[s]; i != -1; i = edge[i].next){
        if (edge[i].in_MST == false)
            continue;
        int v = edge[i].v;
        if (!used[v])   dfs(s, v, max(maxnum, edge[i].w));
    }
}
int n, m;
void Second_MST(){
    Prim(1, n);
    int res = sup;
    //枚举不在最小生成树中的边
    for (int i = 1; i <= n; i ++){
        mem(used, 0);
        dfs(i, i, 0);
        for (int j = head[i]; j != -1; j = edge[j].next){
            int v = edge[j].v;
            if (edge[j].in_MST == false)
                res = min(res, MST_NUM + edge[j].w - max_cost_on_MST[i][v]);
        }
    }
    if (res == MST_NUM){
        printf("Not Unique!\n");
    }
    else{
        printf("%d\n", MST_NUM);
    }
}
int main(){
    int t;
    scanf("%d", &t);
    while(t --){
        MST_NUM = 0;
        Init();
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i ++){
            int a, b, l;
            scanf("%d %d %d", &a, &b, &l);
            Add_edge(a, b, l);
        }
        Second_MST();
    }
	return 0;
}
