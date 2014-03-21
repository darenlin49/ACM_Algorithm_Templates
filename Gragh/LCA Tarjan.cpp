/*
	LCA Tarjan.
	[���÷���]����G(����or����).ѯ�ʴ��Q(����).Ȼ�������root����LCA(root)���ɵó�����ѯ�ʵĴ�.��i��ѯ�ʶ�Ӧ��2i-1��2i-2��ѯ�ʱ�.
	[ע��]������Ϊ�˷����G��Q�Ľṹ��һ�����.��ʱͼ�Ľ��������Ҫ����һЩ,��Ҫ��G��Q�ֿ�(���߲��ֿ�,����������Ҫ�����Զ�һ�������,���Լ��ٴ�����,�������ӿռ�)
*/

/*  ��GΪ�����  */
const int MAXV = 10005;
const int MAXE = 10005;
struct Gragh{
    struct Gragh_Node{
        int u, v;
        int opp;
        int next;
        int res;        //��Query�Ľ��
    }arc[MAXE];
    int cnt, head[MAXV];
    void init(){
        cnt = 0;
        memset(head, -1, sizeof(head));
    }
    void g_insert(int u, int v){		//����� or �����
        arc[cnt].u = u;
        arc[cnt].v = v;
        arc[cnt].res = 0;
        arc[cnt].next = head[u];
        head[u] = cnt ++;
    }
    void q_insert(int u, int v){		//�����
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
    Gragh G, Q;         //G��ͼ(��); Q���ѯ,���԰�ÿ��ѯ�ʵ���һ������ߴ洢
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
        printf("%d\n", L.Q.arc[1].res);     //��i��ѯ�ʶ�Ӧ��2i-1��Query��
    }
    return 0;
}


/*
	[POJ 1986]�������������ڵ�ľ���.
	��������΢����һ�����룬���Ǳ��ʻ���һ���Ķ���һ��ѯ��d[u,v]=dis[u]+dis[v]-dis[LCA(u,v)]����һ��LCAһ�߶�̬�޸ĵ�ǰ�㵽���ľ��롣
	PS:����ע���������Ĵ���~
*/

/*  ��GΪ����� */
const int MAXV = 50005;
const int MAXE = 100005;
struct Gragh{
    struct Gragh_Node{
        int u, v, w;
        int opp;
        int next;
        int res;        //��Query�Ľ��
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
        //��,ͬ��
    }
};
struct Disjoint_Sets{
    //��,ͬ��
};
struct LCA{
    Gragh G, Q;         //G��ͼ(��); Q���ѯ,���԰�ÿ��ѯ�ʵ���һ������ߴ洢
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
