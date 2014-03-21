/*
	����(֤���㵼P339)��
		�ٶ�ͼG��һ��DFS�������ÿ���ڵ�Ľ���ʱ���f[u];
		�ڼ���ͼG��ת��GT;
		�۶�GT����DFS����ѭ���а�f[u]�����˳����ʽڵ㣬�����õ���ɭ�־���SCC�ļ���
		order[]�ǽ���ʱ���Ϊi�Ľڵ��ţ������Ͳ����ٶ�f[]������.
	
	���㷨���ŵ����ڣ����õ��Ľڵ��ǰ�����������֯�õģ������2-SAT�Ĺ�����ʮ�ַ��㡣
	
	�����
		scc[]�洢ÿ���ڵ�������ǿ��ͨ��֧���,scc_numΪǿ��ͨ��֧����
	
	POJ1236:���⣺N(2<N<100)��ѧУ֮���е�������磬ÿ��ѧУ�õ�һ������󣬿���ͨ�������������ܱߵ�ѧУ���䣬����1����ʼ������Ҫ����ٸ�ѧУ���������ʹ�����������е�ѧУ���ն��ܵõ������2��������Ҫ��Ӽ��������߱ߣ�ʹ������һ��ѧУ��������󣬾������ɴδ��ͣ����������е�ѧУ���ն��ܵõ������
	˼·�������ͼ��ǿ��ͨ���������õ�Korasaju��Ҳ������Tarjan����Ȼ�����е�ǿ��ͨ��������һ����(����)������ԭ��������ͼ��������һ��DAGͼ(�����޻�ͼ)������1���������Ϊ0�ĵ�ĸ���������2����������Ҫ���Ӷ������߲ſ���ʹͼΪһ��ǿ��ͨͼ����Ϊ����ǿ��ͨ�ϲ���Ȼ�ǳ���Ϊ0���������Ϊ0�ĵ㣬����Ҫ��������Ϊ0���ͳ���Ϊ0�ĵ㣬���Դ��������������ֵ����ָ���㣩��
*/
const int MAXV = 105;
const int MAXE = 20005;
/* ----------- ǿ��ͨ����Kosaraju�㷨 ----------- */
struct node{
    int u, v;
    int next;
}arc[MAXE], t_arc[MAXE];	//arc��G�Ļ�,t_arc��GT�Ļ����ӱ�ʱ����һ�����.
int cnt, head[MAXV], t_head[MAXV];
int d[MAXV], f[MAXV];       //����ʱ���(��ʵ����û��)
int order[MAXV];            //����ʱ���Ϊi�Ľڵ���
int scc[MAXV], scc_num;     //ÿ���ڵ�����ǿ��ͨ������ţ�ǿ��ͨ��������
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
    for (int u = 1; u <= n; u ++){   //ע��ͼ�нڵ��ŴӼ���ʼ
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
/* ----------- ǿ��ͨ����Kosaraju�㷨 ----------- */
int ans1, ans2;

//����
int indeg[MAXV], outdeg[MAXV];      //�������ȡ�����,������Ϊǿ��ͨ��֧�ı��.
void solve(int n){
    mem(indeg, 0);
    mem(outdeg, 0);
    for (int u = 1; u <= n; u ++){
        for (int i = head[u]; i != -1; i = arc[i].next){
            int v = arc[i].v;
            if (scc[u] != scc[v]){
                indeg[scc[v]] ++;       //�������
                outdeg[scc[u]] ++;      //�������
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
