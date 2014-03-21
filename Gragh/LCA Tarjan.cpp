/*
	LCA Tarjan.
	[调用方法]树存G(有向or无向).询问存进Q(无向).然后对树根root调用LCA(root)即可得出所有询问的答案.第i的询问对应第2i-1和2i-2条询问边.
	[注意]这里我为了方便把G和Q的结构放一块儿了.有时图的结果可能需要复杂一些,则要把G和Q分开(或者不分开,把两个人需要的属性都一起放起来,可以减少代码量,但会增加空间)
*/

/*  树G为有向边  */
const int MAXV = 10005;
const int MAXE = 10005;
struct Gragh{
    struct Gragh_Node{
        int u, v;
        int opp;
        int next;
        int res;        //存Query的结果
    }arc[MAXE];
    int cnt, head[MAXV];
    void init(){
        cnt = 0;
        memset(head, -1, sizeof(head));
    }
    void g_insert(int u, int v){		//有向边 or 无向边
        arc[cnt].u = u;
        arc[cnt].v = v;
        arc[cnt].res = 0;
        arc[cnt].next = head[u];
        head[u] = cnt ++;
    }
    void q_insert(int u, int v){		//无向边
        arc[cnt].u = u;
        arc[cnt].v = v;
        arc[cnt].res = 0;
        arc[cnt].next = head[u];
        arc[cnt].opp = cnt + 1;
        head[u] = cnt ++;
        arc[cnt].u = v;
        arc[cnt].v = u;
        arc[cnt].res = 0;
        arc[cnt].next = head[v];
        arc[cnt].opp = cnt - 1;
        head[v] = cnt ++;
    }
};
struct Disjoint_Sets{
    struct Sets{
        int father, ranks;
    }S[MAXV];
    void Init(int n){
        for (int i = 0; i <= n; i ++)
            S[i].father = i, S[i].ranks = 0;
    }
    int Father(int x){
        if (S[x].father == x){
            return x;
        }
        else{
            S[x].father = Father(S[x].father);     		//Path compression
            return S[x].father;
        }
    }
    bool Union(int x, int y){
        int fx = Father(x), fy = Father(y);
        if (fx == fy){
            return false;
        }
        else{                                           //Rank merge
            if (S[fx].ranks > S[fy].ranks){
                S[fy].father = fx;
            }
            else{
                S[fx].father = fy;
                if (S[fx].ranks == S[fy].ranks){
                    ++ S[fy].ranks;
                }
            }
            return true;
        }
    }
};
struct LCA{
    Gragh G, Q;         //G存图(树); Q存查询,可以把每个询问当成一个无向边存储
    Disjoint_Sets DS;
    int ancestor[MAXV];
    int indegree[MAXV];
    bool vis[MAXV];
    void init(int n){
        memset(ancestor,0,sizeof(ancestor));
        memset(vis,0,sizeof(vis));
        G.init();
        Q.init();
        DS.Init(n);
    }
    void insert_gragh(int u, int v){
        G.g_insert(u, v);
    }
    void insert_query(int u, int v){
        Q.q_insert(u, v);
    }
    void lca(int u){
        ancestor[u] = u;
        for (int i = G.head[u]; i != -1; i = G.arc[i].next){
            int v = G.arc[i].v;
            lca(v);
            DS.Union(u, v);
            ancestor[DS.Father(u)] = u;
        }
        vis[u] = 1;
        for (int i = Q.head[u]; i != -1; i = Q.arc[i].next){
            int v = Q.arc[i].v;
            if (vis[v]){
                Q.arc[i].res = ancestor[DS.Father(v)];
                Q.arc[Q.arc[i].opp].res = ancestor[DS.Father(v)];
			}
        }
    }
    void solve(int n){
        memset(vis, 0, sizeof(vis));
        memset(indegree, 0, sizeof(indegree));
        for (int i = 0; i < G.cnt; i ++){
            indegree[G.arc[i].v] ++;
        }
        for (int i = 1; i <= n; i ++){
            if (indegree[i] == 0)
                lca(i);
        }
    }
}L;

int main(){
    //freopen("data.txt","r+",stdin);
    int t, n;
    scanf("%d",&t);
    while(t --){
        scanf("%d",&n);
        L.init(n);
        for (int i = 1; i < n; i ++){
            int u,v;
            scanf("%d %d",&u,&v);
            L.insert_gragh(u, v);
        }
        int u,v;
        scanf("%d %d",&u,&v);
        L.insert_query(u, v);
        L.solve(n);
        printf("%d\n", L.Q.arc[1].res);     //第i个询问对应第2i-1条Query边
    }
    return 0;
}


/*
	[POJ 1986]求无向树上两节点的距离.
	比上面稍微多了一个距离，但是本质还是一样的对于一个询问d[u,v]=dis[u]+dis[v]-dis[LCA(u,v)]可以一边LCA一边动态修改当前点到根的距离。
	PS:另外注意无向树的处理~
*/

/*  树G为无向边 */
const int MAXV = 50005;
const int MAXE = 100005;
struct Gragh{
    struct Gragh_Node{
        int u, v, w;
        int opp;
        int next;
        int res;        //存Query的结果
    }arc[MAXE];
    int cnt, head[MAXV];
    void init(){
        cnt = 0;
        memset(head, -1, sizeof(head));
    }
    void g_insert(int u, int v, int w){
        arc[cnt].u = u;
        arc[cnt].v = v;
        arc[cnt].w = w;
        arc[cnt].res = 0;
        arc[cnt].next = head[u];
        head[u] = cnt ++;

        arc[cnt].u = v;
        arc[cnt].v = u;
        arc[cnt].w = w;
        arc[cnt].res = 0;
        arc[cnt].next = head[v];
        head[v] = cnt ++;
    }
    void q_insert(int u, int v){
        //略,同上
    }
};
struct Disjoint_Sets{
    //略,同上
};
struct LCA{
    Gragh G, Q;         //G存图(树); Q存查询,可以把每个询问当成一个无向边存储
    Disjoint_Sets DS;
    int ancestor[MAXV];
    int indegree[MAXV];
    int dist[MAXV];
    bool vis[MAXV];
    bool flag[MAXV];
    void init(int n){
        memset(ancestor, 0, sizeof(ancestor));
        memset(vis, 0, sizeof(vis));
        memset(flag, 0, sizeof(flag));
        memset(dist, 0, sizeof(dist));
        G.init();
        Q.init();
        DS.Init(n);
    }
    void insert_gragh(int u, int v, int w){
        G.g_insert(u, v, w);
    }
    void insert_query(int u, int v){
        Q.q_insert(u, v);
    }
    void lca(int u, int dis){
        ancestor[u] = u;
        dist[u] = dis;
        flag[u] = 1;
        for (int i = G.head[u]; i != -1; i = G.arc[i].next){
            int v = G.arc[i].v;
            if (!flag[v]){
                lca(v, dis+G.arc[i].w);
                DS.Union(u, v);
                ancestor[DS.Father(u)] = u;
            }
        }
        vis[u] = 1;
        for (int i = Q.head[u]; i != -1; i = Q.arc[i].next){
            int v = Q.arc[i].v;
            if (vis[v]){
                Q.arc[i].res = dist[u] + dist[v] - 2*dist[ancestor[DS.Father(v)]];
                Q.arc[Q.arc[i].opp].res = dist[u] + dist[v] - 2*dist[ancestor[DS.Father(v)]];
            }
        }
    }
    void solve(int n){
        lca(1, 0);
    }
}L;
int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    L.init(n);
    for (int i = 0; i < m; i ++){
        int u, v, w;
        scanf("%d %d %d %*c", &u, &v, &w);
        L.insert_gragh(u, v, w);
    }
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i ++){
        int u, v;
        scanf("%d %d", &u, &v);
        L.insert_query(u, v);
    }
    L.solve(n);
    for (int i = 1; i <= q; i ++){
        printf("%d\n", L.Q.arc[2*i-1].res);
    }
	return 0;
}
