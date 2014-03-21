/*
[POJ  3694]一个无向图可以有重边.q个操作,每次连接一条边，并询问整个无向图还剩下多少桥.

[分析]先把图求一次边双连通分量(BCC)然后缩点，因为同一双连通分量中没有桥，加边没有影响。一个很重要的性质就是｛一个图求一次边双连通分量缩点后将变成一颗树或者森林，并且树中的每条边都是桥｝。因为此题中说所有的点都有边连着，所以这里缩点后是一棵树。
显然，树中每添加一条边，就会形成一个环，而这个环中的边将不再是桥，并且他们构成新的边双连通分量，所以我们每次在桥中减去这些边，并把他们缩成一个点。
第一，怎么求在树中加边(u,v)后形成的环？
	我们可以求出u,v的LCA，然后环就是v->LCA(u,v)->u>(u,v)->v.
第二，怎么缩点？
	以前一直做的是“静态缩点”，就是求一遍边BCC后图的结构就不变了，此时我们可以在求出每个点所属的BCC(bcc[i])后以BCC的标号来代替缩后的点。如果我们动态地加边，则每次都要修改原BCC中所有的点成新BCC，所以直接这样改行不通。这里我们是不是发现它很像……并查集？对！就是用并查集维护bcc[]！这是我做这道题学到的最重要的姿势：用并查集维护动态加边的缩点。
当然此题中我们没有用到bcc[],因为在求LCA时我们用的朴素的方法：｛用level[]表示每个节点的深度，两个点同时向根爬，深度深的节点先爬（LCA(u,v) = LCA(u, father[v]) ），深度相同时两个点一起爬（LCA(u, v) = LCA(father[u], father[v]) ），直到两个点相同。｝这种方法的好处是可以一边求LCA一边缩点。那么我们就需要一个father[]来维护节点的父节点。这样我们就不需要bcc[]了，直接用并查集维护father[]，并用它表示缩点及所属BCC。
*/

const int MAXV = 100005;
const int MAXE = 400005;
struct node{
    int u, v;
    int next;
    int opp;                    //把一个无向边拆成两个有向边，对应反向边标号
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
int level[MAXV];
int father[MAXV];               //点的父节点,便于爬山坡(向根节点走),也用于并查集缩点
int bridge_num, bridge[MAXV];   //标记该边是不是桥,这里用桥的子节点表示
bool vis_arc[MAXE];             //一条边无向边(两个有向边)只访问一次，
int find(int u){                //并查集 + 路径压缩处理缩点, 缩点合并边时把子节点的父亲设为父节点
    if(father[u] != u)
        return father[u] = find(father[u]);
    else
        return u;
}
void tarjan(int u, int l){
    dfn[u] = low[u] = ++id;
    level[u] = l;
    for (int i = head[u]; i != -1; i = arc[i].next){
        int v = arc[i].v;
        if (vis_arc[i]) continue;
        vis_arc[i] = vis_arc[arc[i].opp] = 1;
        if (!dfn[v]){
            father[v] = u;
            tarjan(v, l+1);
            low[u] = min(low[u], low[v]);
        }
        else{
            low[u] = min(low[u], dfn[v]);
        }
        if (dfn[u] < low[v]){
            bridge[v] = 1;
            bridge_num ++;
        }
        else{
            int x = find(u);
            int y = find(v);
            if (x != y)
                father[y] = x;
        }
    }
}
void solve(int n){
    id  = bridge_num = 0;
    mem(dfn, 0);
    mem(low, 0);
    mem(level, 0);
    mem(bridge, 0);
    mem(vis_arc, 0);
    for (int i = 0; i <= n; i ++)
        father[i] = i;
    for (int i = 1; i <= n; i ++){
        if (!dfn[i])
            tarjan(1, 1);
    }
    return ;
}
vector <int> path;
int lca(int u, int v){
    path.clear();
    if (level[u] > level[v])    swap(u, v);
    while(u != v){
        while(level[u] != level[v]){
            if(level[v] > level[u]){
                if (bridge[v]){
                    bridge[v] = 0;
                    bridge_num --;
                }
                path.push_back(v);
                v = father[v];
            }
            else{
                if (bridge[u]){
                    bridge[u] = 0;
                    bridge_num --;
                }
                path.push_back(u);
                u = father[u];
            }
        }
        while(u != v){
            if (bridge[v]){
                bridge[v] = 0;
                bridge_num --;
            }
            if (bridge[u]){
                bridge[u] = 0;
                bridge_num --;
            }
            path.push_back(u);
            path.push_back(v);
            v = father[v];
            u = father[u];
        }
    }
    int lc = u;
    //把加边后的环用并查集缩成一个点
    for (int i = 0; i < (int)path.size(); i ++){
        int u = path[i];
        father[u] = lc;
    }
    return bridge_num;
}
int main(){
    int n, m, t = 1;
    while(scanf("%d %d", &n, &m) != EOF){
        if (n + m == 0)
            break;
        init();
        for (int i = 0; i < m; i ++){
            int u, v;
            scanf("%d %d", &u, &v);
            add(u, v);
        }
        solve(n);
        int q;
        scanf("%d", &q);
        printf("Case %d:\n", t);
        for (int i = 0; i < q; i ++){
            int u, v;
            scanf("%d %d", &u, &v);
            printf("%d\n", lca(u, v));
        }
        puts("");
        t ++;
    }
	return 0;
}