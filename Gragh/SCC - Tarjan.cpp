/*
	POJ 2186, ���⣺���м�������������е㵽�
	��������ǿ��ͨ���������㣬�ҳ���Ϊ0�ĵ㡣���ֻ��һ�������ǿ��ͨ�����еĵ㶼�Ǵ𰸣�����ж��������Щ�㻥���ɴ��Ϊ0.
	
	Tarjan�㷨��ǿ��ͨ�������̣�
		
*/
const int MAXN = 4005;
const int MAXM = 205005;
struct SCC{
    int scc_num, scc[MAXN];         //ǿ��ͨ�����������ڵ�����ǿ��ͨ����
    vector <int> scc_node[MAXN];    //ǿ��ͨ�����еĽڵ�
    stack <int> st;
    int dfn[MAXN], low[MAXN], id;
    bool vis[MAXN], instack[MAXN];
    int cnt, head[MAXN];

    struct node{
        int u, v;
        int next;
    }arc[MAXM];

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
                scc_node[scc_num].push_back(st.top());
                instack[st.top()] = 0;
                st.pop();
            }
            scc[st.top()] = scc_num;
            scc_node[scc_num].push_back(st.top());
            instack[st.top()] = 0;
            st.pop();
        }
        return ;
    }
    void tarjan(int n){
        mem(vis, 0);
        mem(instack, 0);
        mem(dfn, 0);
        mem(low, 0);
        mem(scc, 0);
        id = scc_num = 0;
        for (int i = 0; i <= n; i ++)	scc_node[i].clear();
        while(!st.empty())				st.pop();
        for (int i = 1; i <= n; i ++){   //ö�ٽڵ�
            if (!vis[i])
                dfs(i);
        }
        return ;
    }
}S;
/* ------------------------------ Tarjan ------------------------- */

int odeg[MAXN];
void solve(int n){
    //�����ǿ��ͨͼ��ÿ���㶼�Ǵ�
    if (S.scc_num == 1){
        printf("%d\n", n);
        return ;
    }
    //����
    int num = 0, res;
    mem(odeg, 0);
    S.tarjan(n);
    for (int u = 1; u <= n; u ++){
        for (int i = S.head[u]; i != -1; i = S.arc[i].next){
            int v = S.arc[i].v;
            if (S.scc[u] != S.scc[v]){
                odeg[S.scc[u]] ++;
            }
        }
    }
    for (int i = 1; i <= S.scc_num; i ++){
        if (odeg[i] == 0){
            num ++;
            res = i;
        }
    }
    if (num == 1){
        printf("%d\n", S.scc_node[res].size());
    }
    else{
        puts("0");
    }
}
int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    S.init();
    for (int i = 0; i < m; i ++){
        int u, v;
        scanf("%d %d", &u, &v);
        S.add(u, v);
    }
    solve(n);
	return 0;
}
