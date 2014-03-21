/**
�����Ȩ�պ�ͼ����

	һ������ͼG(V, E)�ıպ�ͼ(closure(�հ�?))�Ǹ�����ͼ��һ���㼯���Ҹõ㼯�����г���Ҳ�ڸõ㼯�С����պ�ͼ�ڵ������ĺ��Ҳһ���ڱպ�ͼ�С���ÿһ����v����һ����ȨWv������ʵ���������ɸ��������Ȩ�պ�ͼ(Maximum weight closure)����һ����Ȩ���ıպ�ͼ������󻯦�v��V�� Wv��

�㹹ͼ&&�ⷨ

	��ԭͼG(V, E)ת��Ϊ������GN(VN,EN)����ԭͼ�㼯�Ļ���������Դ��S�ͻ��T����ԭͼÿ�������<u,v>��E�滻������Ϊc(u,v) = �޵������<u, v, ��>��EN����������Դ��S��ԭͼÿ����Ȩ��v(Wv>0)�������<S, v, Wv>����������ԭͼÿ����Ȩ��v(Wv<0)�����T�������<v, T, -Wv>��

	�����Ȩ = ��Ȩ�� �C GN����С�֤���ο����������ġ���С��ģ������Ϣѧ�����е�Ӧ�á���

	����С���ԭͼ����ΪS����T����S�㼯�ĵ㼴Ϊ���Ȩ�պ�ͼ�еĵ㡣
	
��ʱ�临�Ӷ� ��O(MAXFLOW(N))
**/
const int MAXV = 5005;
const int MAXE = 60005;
const int oo = 0x3fffffff;
 
/** Dinic����� **/
template <typename T>
struct Dinic{
    struct flow_node{
        int u, v;
        T flow;
        int opp;
        int next;
    }arc[2*MAXE];
    int vn, en, head[MAXV];
    int cur[MAXV];
    int q[MAXV];
    int path[2*MAXE], top;
    int dep[MAXV];
    void init(int n){
        vn = n;
        en = 0;
        mem(head, -1);
    }
    void insert_flow(int u, int v, T flow){
        arc[en].u = u;
        arc[en].v = v;
        arc[en].flow = flow;
        arc[en].next = head[u];
        head[u] = en ++;
 
        arc[en].u = v;
        arc[en].v = u;
        arc[en].flow = 0;
        arc[en].next = head[v];
        head[v] = en ++;
    }
    bool bfs(int s, int t){
        mem(dep, -1);
        int lq = 0, rq = 1;
        dep[s] = 0;
        q[lq] = s;
        while(lq < rq){
            int u = q[lq ++];
            if (u == t){
                return true;
            }
            for (int i = head[u]; i != -1; i = arc[i].next){
                int v = arc[i].v;
                if (dep[v] == -1 && arc[i].flow > 0){
                    dep[v] = dep[u] + 1;
                    q[rq ++] = v;
                }
            }
        }
        return false;
    }
    T solve(int s, int t){
        T maxflow = 0;
        while(bfs(s, t)){
            int i, j;
            for (i = 1; i <= vn; i ++)  cur[i] = head[i];
            for (i = s, top = 0;;){
                if (i == t){
                    int mink;
                    T minflow = 0x7fffffff;						//Ҫ��������oo��
                    for (int k = 0; k < top; k ++)
                        if (minflow > arc[path[k]].flow){
                            minflow = arc[path[k]].flow;
                            mink = k;
                        }
                    for (int k = 0; k < top; k ++)
                        arc[path[k]].flow -= minflow, arc[path[k]^1].flow += minflow;
                    maxflow += minflow;
                    top = mink;
                    i = arc[path[top]].u;
                }
                for (j = cur[i]; j != -1; cur[i] = j = arc[j].next){
                    int v = arc[j].v;
                    if (arc[j].flow && dep[v] == dep[i] + 1)
                        break;
                }
                if (j != -1){
                    path[top ++] = j;
                    i = arc[j].v;
                }
                else{
                    if (top == 0)   break;
                    dep[i] = -1;
                    i = arc[path[-- top]].u;
                }
            }
        }
        return maxflow;
    }
};
Dinic <long long> dinic;
 
/** ���Ȩ�պ�ͼ **/
int weight[MAXV];               //��Ȩ
struct Edge{
    int u, v;
}e[MAXE];
vector <int> ans_node;          //���Ȩ�պ�ͼ�еĵ�
bool vis[MAXV];
void find_nodes(int u, int s){
    vis[u] = 1;
    if (u != s)
        ans_node.push_back(u);
    for (int i = dinic.head[u]; i != -1; i = dinic.arc[i].next){
        if (dinic.arc[i].flow <= 0) continue;
        int v = dinic.arc[i].v;
        if (!vis[v]){
            find_nodes(v, s);
        }
    }
}
void MaximumWeightClosureOfaGragh(int nodes_num, int edges_num, long long &res, int &res_node_num){
    /* �����Ȩ��,����res */
    long long positive_sum = 0;   //��Ȩ��
    dinic.init(nodes_num+2);
    for (int i = 1; i <= nodes_num; i ++){
        if (weight[i] >= 0){
            positive_sum += weight[i];
            dinic.insert_flow(nodes_num+1, i, weight[i]);
        }
        else{
            dinic.insert_flow(i, nodes_num+2, -weight[i]);
        }
    }
    for (int i = 0; i < edges_num; i ++){
        dinic.insert_flow(e[i].u, e[i].v, oo);
    }
    res = positive_sum - dinic.solve(nodes_num+1, nodes_num+2);
    /* �����Ȩ�պ�ͼ�еĵ� */
    ans_node.clear();
	mem(vis, 0);
    find_nodes(nodes_num+1, nodes_num+1);
    res_node_num = (int)ans_node.size();
    return ;
}
 
int main(){
	//freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);
    int n, m;
    while(scanf("%d %d", &n, &m) != EOF){
        for (int i = 1; i <= n; i ++){
            scanf("%d", &weight[i]);
        }
        for (int i = 0; i < m; i ++){
            scanf("%d %d", &e[i].u, &e[i].v);
        }
        long long res;
        int res_node;
        MaximumWeightClosureOfaGragh(n, m, res, res_node);
        printf("%d %I64d\n", res_node, res);
    }
	return 0;
}