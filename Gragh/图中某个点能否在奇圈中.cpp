/*
	POJ 2942 : 找出图中不可能在奇圈中的点.
	[分析]注意到，在不同点双连通分量中的两个点，显然是不会存在圈的.那么这样，问题就划归为在点双连通分量中去找奇圈。
	[重要性质]在一个点双连通分量中,只要有任意一个奇圈，那么所有的点都可以在一个奇圈内(证明看《算法竞赛入门经典 训练指南》).
	[重要定理]一个图含奇圈当且仅当图不是二分图.
	[解题思路]先求出图的点双连通分量(块),然后对每一个块染色判断二分图,统计出不可能在奇圈中的点的个数
	[注意]染色判定二分图的算法要写对
*/
const int N = 1002;
const int E = 2000002;
struct node{
    int u, v;
    int next;
}arc[E];
int cnt, head[N];
void init(){
    mem(head, -1);
    cnt = 0;
}
void add(int u, int v){
    arc[cnt].u = u;
    arc[cnt].v = v;
    arc[cnt].next = head[u];
    head[u] = cnt ++;
    arc[cnt].u = v;
    arc[cnt].v = u;
    arc[cnt].next = head[v];
    head[v] = cnt ++;
}

/* 求点双连通分量 */
int dfn[N], low[N];
set <int> bcc[N];
int id, bcc_num;
stack <node> st;
void addbcc(int u, int v){
    bcc[bcc_num].insert(u);
    bcc[bcc_num].insert(v);
}
void dfs(int u, int father){
    dfn[u] = low[u] = ++id;
    for (int i = head[u]; i != -1; i = arc[i].next){
        int v = arc[i].v;
        if (v == father)    continue;
        if (dfn[v] < dfn[u]){
            st.push(arc[i]);
            if (!dfn[v]){
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (dfn[u] <= low[v]){
                    ++ bcc_num;
                    while(!st.empty()){
                        int a = st.top().u;
                        int b = st.top().v;
                        st.pop();
                        addbcc(a, b);
                        if ((a == u && b == v) || (b == u && a == v) )
                            break;
                    }
                }
            }
            else{
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
}
void bcc_tarjan(int n){
    id = bcc_num = 0;
    mem(dfn, 0);
    mem(low, 0);
    while(!st.empty())
        st.pop();
    for (int i = 0; i <= n; i ++)
        bcc[i].clear();

    for (int i = 1; i <= n; i ++)
        dfs(i, 0);
}
/* 求点双连通分量 */

/* 染色判定二分图 */
int col[N];
bool not_bigragh[N];    //标记某个点双连通分量是不是二分图
void dfs_color(int bcc_id, int u, int color){
    col[u] = color;
    for (int i = head[u]; i != -1; i = arc[i].next){
        if (not_bigragh[bcc_id])
            return;
        int v = arc[i].v;
        if (bcc[bcc_id].find(v) == bcc[bcc_id].end())
            continue;
        if (col[v] == col[u]){
            not_bigragh[bcc_id] = 1;
            return;
        }
        else if (col[v] == -1){
            dfs_color(bcc_id, v, (color+1)&1);
        }
    }
}
bool fill(int bcc_id){      //对某个点双连通分量染色判断二分图
    set <int> ::iterator it;
    for (it = bcc[bcc_id].begin(); it != bcc[bcc_id].end(); it ++){
        not_bigragh[bcc_id] = 0;
        int u = *it;
        mem(col, -1);
        dfs_color(bcc_id, u, 0);
        if (not_bigragh[bcc_id])
            return false;
    }
    return true;
}
/* 染色判定二分图 */

int res;
bool can[N];        //存某个点能否在一个奇圈中
int solve(int n){
    res = 0;
    mem(can, 0);
    for (int i = 1; i <= bcc_num; i ++){
        if (!fill(i)){
            set <int> ::iterator it;
            for (it = bcc[i].begin(); it != bcc[i].end(); it ++){
                can[*it] = 1;
            }
        }
    }
    for (int i = 1; i <= n; i ++){
        if (!can[i])
            res ++;
    }
    return res;
}
bool mat[N][N];     //表示i憎恨j的关系矩阵
int main(){
    int n, m;
    while(scanf("%d %d", &n, &m) != EOF){
        if (n == 0 && m == 0)
            break;
        init();
        mem(mat, 0);
        for (int i = 0; i < m; i ++){
            int a, b;
            scanf("%d %d", &a, &b);
            mat[a][b] = 1;
            mat[b][a] = 1;
        }
        for (int i = 1; i <= n; i ++){
            for (int j = i+1; j <= n; j ++){
                if (!mat[i][j]){
                    add(i, j);
                }
            }
        }
        bcc_tarjan(n);
        printf("%d\n", solve(n));
    }
	return 0;
}
