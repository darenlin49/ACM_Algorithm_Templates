/*
	POJ 2942 : �ҳ�ͼ�в���������Ȧ�еĵ�.
	[����]ע�⵽���ڲ�ͬ��˫��ͨ�����е������㣬��Ȼ�ǲ������Ȧ��.��ô����������ͻ���Ϊ�ڵ�˫��ͨ������ȥ����Ȧ��
	[��Ҫ����]��һ����˫��ͨ������,ֻҪ������һ����Ȧ����ô���еĵ㶼������һ����Ȧ��(֤�������㷨�������ž��� ѵ��ָ�ϡ�).
	[��Ҫ����]һ��ͼ����Ȧ���ҽ���ͼ���Ƕ���ͼ.
	[����˼·]�����ͼ�ĵ�˫��ͨ����(��),Ȼ���ÿһ����Ⱦɫ�ж϶���ͼ,ͳ�Ƴ�����������Ȧ�еĵ�ĸ���
	[ע��]Ⱦɫ�ж�����ͼ���㷨Ҫд��
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

/* ���˫��ͨ���� */
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
/* ���˫��ͨ���� */

/* Ⱦɫ�ж�����ͼ */
int col[N];
bool not_bigragh[N];    //���ĳ����˫��ͨ�����ǲ��Ƕ���ͼ
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
bool fill(int bcc_id){      //��ĳ����˫��ͨ����Ⱦɫ�ж϶���ͼ
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
/* Ⱦɫ�ж�����ͼ */

int res;
bool can[N];        //��ĳ�����ܷ���һ����Ȧ��
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
bool mat[N][N];     //��ʾi����j�Ĺ�ϵ����
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
