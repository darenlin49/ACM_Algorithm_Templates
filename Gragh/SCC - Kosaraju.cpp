/*
	过程(证明算导P339)：
		①对图G做一遍DFS，计算出每个节点的结束时间戳f[u];
		②计算图G的转置GT;
		③对GT进行DFS，主循环中按f[u]降序的顺序访问节点，遍历得到的森林就是SCC的集合
		order[]是结束时间戳为i的节点标号，这样就不用再对f[]排序了.
	
	该算法的优点在于，最后得到的节点是按照拓扑序组织好的，在求解2-SAT的过程中十分方便。
	
	结果：
		scc[]存储每个节点所属的强连通分支编号,scc_num为强连通分支总数
	
	POJ1236:题意：N(2<N<100)个学校之间有单向的网络，每个学校得到一套软件后，可以通过单向网络向周边的学校传输，问题1：初始至少需要向多少个学校发放软件，使得网络内所有的学校最终都能得到软件。2，至少需要添加几条传输线边，使任意向一个学校发放软件后，经过若干次传送，网络内所有的学校最终都能得到软件。
	思路：先求出图的强连通分量（我用的Korasaju，也可以用Tarjan），然后将所有的强连通分量缩成一个点(缩点)，这样原来的有向图就缩成了一个DAG图(有向无环图)。问题1就是求入度为0的点的个数；问题2是问最少需要连接多少条边才可以使图为一个强连通图。因为两个强连通合并必然是出度为0的连接入度为0的点，所以要解决掉入度为0，和出度为0的点，所以答案是这两个的最大值（点指缩点）。
*/
const int MAXV = 105;
const int MAXE = 20005;
/* ----------- 强联通分量Kosaraju算法 ----------- */
struct node{
    int u, v;
    int next;
}arc[MAXE], t_arc[MAXE];	//arc是G的弧,t_arc是GT的弧，加边时可以一块儿加.
int cnt, head[MAXV], t_head[MAXV];
int d[MAXV], f[MAXV];       //深搜时间戳(其实这里没用)
int order[MAXV];            //结束时间戳为i的节点标号
int scc[MAXV], scc_num;     //每个节点所属强连通分量编号，强连通分量总数
void init(){
    cnt = 0;
    mem(head, -1);
    mem(t_head, -1);
}
void add(int u, int v){
    arc[cnt].u = u;
    arc[cnt].v = v;
    arc[cnt].next = head[u];
    head[u] = cnt;

    t_arc[cnt].u = v;
    t_arc[cnt].v = u;
    t_arc[cnt].next = t_head[v];
    t_head[v] = cnt ++;
    return ;
}
bool vis[MAXV];
int id, fid;
void dfs(int u){
    vis[u] = 1;
    d[u] = id ++;
    for (int i = head[u]; i != -1; i = arc[i].next){
        int v = arc[i].v;
        if (!vis[v]){
            dfs(v);
        }
    }
    f[u] = id;
    order[fid ++] = u;
    return ;
}
void dfs_t(int u){
    vis[u] = 1;
    scc[u] = scc_num;
    for (int i = t_head[u]; i != -1; i = t_arc[i].next){
        int v = t_arc[i].v;
        if (!vis[v]){
            dfs_t(v);
        }
    }
    return ;
}
void Kosaraju(int n){
    //init
    scc_num = 0;
    mem(scc, -1);
    mem(d, -1);
    mem(f, -1);
    mem(order, -1);

    mem(vis, 0);
    id = fid = 0;
    for (int u = 1; u <= n; u ++){   //注意图中节点编号从几开始
        if (!vis[u]){
            dfs(u);
        }
    }
    mem(vis, 0);
    for (int i = n - 1; i >= 0; i --){
        int u = order[i];
        if (!vis[u]){
            scc_num ++;
            dfs_t(u);
        }
    }
}
/* ----------- 强联通分量Kosaraju算法 ----------- */
int ans1, ans2;

//缩点
int indeg[MAXV], outdeg[MAXV];      //缩点的入度、出度,缩点编号为强连通分支的编号.
void solve(int n){
    mem(indeg, 0);
    mem(outdeg, 0);
    for (int u = 1; u <= n; u ++){
        for (int i = head[u]; i != -1; i = arc[i].next){
            int v = arc[i].v;
            if (scc[u] != scc[v]){
                indeg[scc[v]] ++;       //缩点入度
                outdeg[scc[u]] ++;      //缩点出度
            }
        }
    }
    ans1 = 0;
    int ans21 = 0, ans22 = 0;
    for (int i = 1; i <= scc_num; i ++){
        if (indeg[i] == 0){
            ans1 ++;
            ans21 ++;
        }
        if (outdeg[i] == 0){
            ans22 ++;
        }
    }
    ans2 = max(ans21, ans22);
}

int main(){
    int n;
    scanf("%d", &n);
    init();
    for (int i = 1; i <= n; i ++){
        int j;
        while(scanf("%d", &j), j){
            add(i, j);
        }
    }
    Kosaraju(n);
    solve(n);
    if (scc_num == 1)
        ans2 = 0;
    printf("%d\n%d\n", ans1, ans2);
	return 0;
}
