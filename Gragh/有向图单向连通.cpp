/* 
	[POJ 2762]给定一个有向图，问是否对于任意给定的两个点x，y，满足以下两个条件之一： x能到达y 或者y能到达x;
	[Analysis]虽然本题是求单连通的，但是我们需要先求强连通分量，因为，强连通分量中存在双向路径，因此可以缩点，缩点后就好处理多了。如果要满足题意，缩点后的树必须是一条链，而且所有边的方向都是一样的，如果出现分支，很容易证明会出现不可到达的一对点。那么剩下的就是求最长链的顶点数是否等于强连通分量的个数了。那么就可以使用拓扑排序，或者直接DFS。拓扑排序中，不能出现同时有两个点的入度为0。DFS从入度为0的顶点开始搜，是求出深搜的层数，因为单链的话层数是等于顶点数的
*/
const int MAXV = 1002;
const int MAXE = 10002;
struct Toposort{
    int ind[MAXV];
    vector <int> top_res;
    priority_queue <int , vector<int> , greater<int> > PQ;
    struct node{
        int u, v;
        int next;
    }arc[MAXE];
    int head[MAXV], cnt;
    void init(){
        cnt = 0;
        mem(head, -1);
    }
    void add(int u, int v){
        arc[cnt].u = u;
        arc[cnt].v = v;
        arc[cnt].next = head[u];
        head[u] = cnt ++;
    }
    void cal_indegree(){
        mem(ind, 0);
        for (int i = 0; i < cnt; i ++){
            ind[arc[i].v] ++;
        }
        return ;
    }
    //拓扑序唯一(一条链)返回1，拓扑序不唯一返回0，拓扑序矛盾(存在环)返回-1.
    bool topsort(int n){
        while(!PQ.empty())
            PQ.pop();
        top_res.clear();
        cal_indegree();
        for (int i = 1; i <= n; i ++)
            if (ind[i] == 0)
                PQ.push(i);
        while(!PQ.empty()){
            if (PQ.size() > 1)
                return 0;
            int u = PQ.top();
            PQ.pop();
            top_res.push_back(u);
            for (int i = head[u]; i != -1; i = arc[i].next){
                if ((-- ind[arc[i].v]) == 0)
                    PQ.push(arc[i].v);
            }
        }
        if (top_res.size() < n)
            return -1;
        return 1;
    }
}T;
struct SCC{
    int scc_num, scc[MAXV];         //强连通分量总数、每个节点所属的强连通分量
    int scc_acount[MAXV];           //每个强连通分量的节点个数
    int dfn[MAXV], low[MAXV], id;
    stack <int> st;
    bool vis[MAXV], instack[MAXV];
    int cnt, head[MAXV];
 
    struct node{
        int u, v;
        int next;
    }arc[MAXE];
 
    void init(){
        cnt = 0;
        mem(head, -1);
        return ;
    }
    void add(int u, int v){
        arc[cnt].u = u;
        arc[cnt].v = v;
        arc[cnt].next = head[u];
        head[u] = cnt ++;
    }
    void dfs(int u){
        vis[u] = instack[u] = 1;
        st.push(u);
        dfn[u] = low[u] = ++ id;
        for (int i = head[u]; i != -1; i = arc[i].next){
            int v = arc[i].v;
            if (!vis[v]){
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if (instack[v]){
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]){
            ++ scc_num;
            while(st.top() != u){
                scc[st.top()] = scc_num;
                scc_acount[scc_num] ++;
                instack[st.top()] = 0;
                st.pop();
            }
            scc[st.top()] = scc_num;
            scc_acount[scc_num] ++;
            instack[st.top()] = 0;
            st.pop();
        }
        return ;
    }
    void tarjan(int n){
        mem(scc_acount, 0);
        mem(vis, 0);
        mem(instack, 0);
        mem(dfn, 0);
        mem(low, 0);
        mem(scc, 0);
        id = scc_num = 0;
        while(!st.empty())
            st.pop();
        for (int i = 1; i <= n; i ++){   //枚举节点
            if (!vis[i])
                dfs(i);
        }
        return ;
    }
}S;
void insert_to_topo(int l){
    T.init();
    for (int i = 0; i < l; i ++){
        int u = S.arc[i].u;
        int v = S.arc[i].v;
        if (S.scc[u] != S.scc[v])
            T.add(S.scc[u], S.scc[v]);
    }
    if (T.topsort(S.scc_num) == 1){
        puts("Yes");
    }
    else{
        puts("No");
    }
}
int main(){
    int t;
    scanf("%d", &t);
    for(int o = 1; o <= t; o ++){
        //printf("Case %d: ", o);
        int n, m;
        S.init();
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i ++){
            int u, v;
            scanf("%d %d", &u, &v);
            S.add(u, v);
        }
        S.tarjan(n);
        insert_to_topo(S.cnt);
    }
	return 0;
}
