/**
	POJ 3352 && POJ 3177 题意：加几条边原图才能变成边双连通分量
	[求割边]对图深度优先搜索，定义DFS(u)为u在搜索树（以下简称为树）中被遍历到的次序号。定义Low(u)为u或u的子树中能通过非父子边追溯到的最早的节点，即DFS序号最小的节点。根据定义，则有：Low(u)=Min {DFS(u),DFS(v)|(u,v)为后向边(等价于DFS(v)<DFS(u)且v不为u的父亲节点),Low(v)|(u,v)为树枝边}
	
	[条件]一条无向边(u,v)是桥，当且仅当(u,v)为树枝边，且满足DFS(u)<Low(v)
	[求点双连通分支]只需在求出所有的桥以后，把桥边删除，原图变成了多个连通块，则每个连通块就是一个边双连通分支。桥不属于任何一个边双连通分支，其余的边和每个顶点都属于且只属于一个边双连通分支。
	
	[注]重边对求割边和边连通分量有影响，重边处理方法是在DFS时标记每条边及其反向边是否被访问过（即按边访问），而不是判断顶点（按点访问）。
**/

/* 无重边 */
const int MAXV = 5005;
const int MAXE = 20005;
struct node{
    int u, v;
    int next;
    int opp;        //把一个无向边拆成两个有向边，对应反向边标号
}arc[MAXE];
int cnt, head[MAXV];
void init(){
    cnt = 0;
    mem(head, -1);
    return ;
}
void add(int u, int v){
    arc[cnt].u = u;
    arc[cnt].v = v;
    arc[cnt].next = head[u];
    arc[cnt].opp = cnt + 1;
    head[u] = cnt ++;
    arc[cnt].u = v;
    arc[cnt].v = u;
    arc[cnt].next = head[v];
    arc[cnt].opp = cnt - 1;
    head[v] = cnt ++;
    return ;
}

int id, dfn[MAXV], low[MAXV];
int bridge[MAXE];                //标记该边是不是桥
void tarjan(int u, int father){
    dfn[u] = low[u] = ++id;
    for (int i = head[u]; i != -1; i = arc[i].next){
        int v = arc[i].v;
        if (v == father)    continue;
        if (!dfn[v]){
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v]){
                bridge[i] = 1;					//两个反向的有向边表示无向边
                bridge[arc[i].opp] = 1;
            }
        }
        else{
            low[u] = min(low[u], dfn[v]);
        }
    }
}
bool vis[MAXV];
int bcc_num;					//边双连通分量数
int bcc[MAXV];                  //标记点属于哪个边双连通分支
void fill(int u){				//在删除桥的图中对每个点染色，确定他所属的边双联通分量
    vis[u] = 1;
    bcc[u] = bcc_num;
    for (int i = head[u]; i != -1; i = arc[i].next){
        if (bridge[i])  continue;
        int v = arc[i].v;
        if (!vis[v])
            fill(v);
    }
}
int deg[MAXV];                  //缩点后的新图节点度数，便于计算叶子结点数
bool vis_arc[MAXE];             //某无向边(两个有向边)只访问一次，
int find_bcc(int n){			//返回还需添加几条边才能成为边双连通图
    mem(vis, 0);
    mem(deg, 0);
    //确定每个点所属边双联通分量
    for (int i = 1; i <= n; i ++){
        if (!vis[i]){
            ++ bcc_num;
            fill(i);
        }
    }
    mem(vis_arc, 0);
    //计算还需连几条边才能构成双联通图
    for (int i = 0; i < cnt; i ++){
        if (!vis_arc[i]){
			//这里一定要注意计算度数时一条无向边只能算一次
            vis_arc[i] = vis_arc[arc[i].opp] = 1;
            int u = arc[i].u;
            int v = arc[i].v;
            if (bcc[u] != bcc[v]){
                deg[bcc[u]] ++;
                deg[bcc[v]] ++;
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= bcc_num; i ++){
        if (deg[i] == 1)
            res ++;
    }
    return (res+1)/2;
}
void solve(int n){
    id = bcc_num =0;
    mem(dfn, 0);
    mem(low, 0);
    mem(bridge, 0);
    for (int i = 1; i <= n; i ++){
        if (!dfn[i])
            tarjan(1, 0);
    }
    printf("%d\n", find_bcc(n));
    return ;
}

int main(){
    int F,R;
    while(scanf("%d %d", &F, &R) != EOF){
        init();
        for (int i = 0; i < R; i ++){
            int u, v;
            scanf("%d %d", &u, &v);
            add(u, v);
        }
        solve(F);
    }
	return 0;
}


/* 有重边BCC，按边DFS */
const int MAXV = 200005;
const int MAXE = 2000005;
struct node{
    int u, v;
    int next;
    bool bridge;
}arc[MAXE];
int cnt, head[MAXV];
void init(){
    cnt = 0;
    mem(head, -1);
    return ;
}
void add(int u, int v){
    arc[cnt].u = u;
    arc[cnt].v = v;
    arc[cnt].next = head[u];
    arc[cnt].bridge = false;
    head[u] = cnt ++;
    arc[cnt].u = v;
    arc[cnt].v = u;
    arc[cnt].next = head[v];
    arc[cnt].bridge = false;
    head[v] = cnt ++;
    return ;
}
int id, dfn[MAXV], low[MAXV];
int bridge_num;
bool vis_arc[MAXE];              			//一条边无向边(两个有向边)只访问一次，
void tarjan(int u){
    dfn[u] = low[u] = ++ id;
    for (int i = head[u]; i != -1; i = arc[i].next){
        if (vis_arc[i]) continue;
        int v = arc[i].v;
        vis_arc[i] = vis_arc[i^1] = 1;		//判重边
        if (!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v]){
                arc[i].bridge = true;
                arc[i^1].bridge = true;
                bridge_num ++;
            }
        }
        else{
            low[u] = min(low[u], dfn[v]);
        }
    }
}
int bcc_num;
bool vis[MAXV];
int mark[MAXV];                  //标记点属于哪个边双连通分支
vector <int> bcc[MAXV];

void fill(int u){
    bcc[bcc_num].push_back(u);
    mark[u] = bcc_num;
    for (int i = head[u]; i != -1; i = arc[i].next){
        if (arc[i].bridge)  continue;
        int v = arc[i].v;
        if (mark[v] == 0)
            fill(v);
    }
}
void find_bcc(int n){
    mem(vis, 0);
    mem(mark, 0);
    //确定每个点所属边双联通分量
    for (int i = 1; i <= n; i ++){
        if (mark[i] == 0){
            ++ bcc_num;
            bcc[bcc_num].clear();
            fill(i);
        }
    }
    return ;
}
void solve(int n){
    id = bcc_num = bridge_num = 0;
    mem(dfn, 0);
    mem(low, 0);
    mem(vis_arc, 0);
    for (int i = 1; i <= n; i ++){
        if (!dfn[i])
            tarjan(i);
    }
    find_bcc(n);
    return ;
}
int main(){
	return 0;
}