/* 
	[POJ 2762]����һ������ͼ�����Ƿ�������������������x��y������������������֮һ�� x�ܵ���y ����y�ܵ���x;
	[Analysis]��Ȼ����������ͨ�ģ�����������Ҫ����ǿ��ͨ��������Ϊ��ǿ��ͨ�����д���˫��·������˿������㣬�����ͺô�����ˡ����Ҫ�������⣬��������������һ�������������бߵķ�����һ���ģ�������ַ�֧��������֤������ֲ��ɵ����һ�Ե㡣��ôʣ�µľ���������Ķ������Ƿ����ǿ��ͨ�����ĸ����ˡ���ô�Ϳ���ʹ���������򣬻���ֱ��DFS�����������У����ܳ���ͬʱ������������Ϊ0��DFS�����Ϊ0�Ķ��㿪ʼ�ѣ���������ѵĲ�������Ϊ�����Ļ������ǵ��ڶ�������
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
    //������Ψһ(һ����)����1��������Ψһ����0��������ì��(���ڻ�)����-1.
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
    int scc_num, scc[MAXV];         //ǿ��ͨ����������ÿ���ڵ�������ǿ��ͨ����
    int scc_acount[MAXV];           //ÿ��ǿ��ͨ�����Ľڵ����
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
        for (int i = 1; i <= n; i ++){   //ö�ٽڵ�
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
