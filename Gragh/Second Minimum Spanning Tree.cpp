/*
��С������(The second MST, 2-MST)

����˼�룺���������С����������¼Ȩֵ֮��ΪMST_NUM��Ȼ��ö����ӱ�(u,v)�������Ժ�һ���γ�һ�������ҵ����Ϸ�(u,v)�ߵ�Ȩֵ���ıߣ�����ɾ�������㵱ǰ��������Ȩֵ֮�ͣ�ȡ����ö�ټӱߺ�������Ȩֵ֮�͵���Сֵ�����Ǵ�С��������

�㷨��

1.�����С������T����Ȩֵ��MST_NUM������ע����С�������ϵıߡ�

2.��ÿ������iΪ����DFS������С�������������i��j��·�������ߵ�ȨֵP(i, j)��

3.����ÿ��������С�������еı�(i,j)�����������ߣ���ɾ����������(P(i,j))���µ�������Ȩֵ֮��ΪMST_NUM + w(i,j) - P[i][j]����¼����Сֵ���ɣ�ʱ�临�Ӷ�ΪO(N^2)������С��������������򵥵�Prim���ɣ��㷨��ƿ���ڵڶ���DFS������·����������ҪO(n^2)���ø��õ��㷨��û������ġ�(PS������ÿ���ߣ�ʵ���Ͽ�����LCA��Ԥ�������õ��������ߣ��������ӶȾ���O(ElogV)��Ȼ�����Kruskal���Ӷȿ��Խ���O(ElogV), �����Ժ�ѧϰ��)

-----------------------------------------------------------
POJ 1679 The Unique MST  (MST�Ƿ�Ψһ)

�����С��������Ȼ���ж�Ȩֵ���Ƿ������С���������ɡ�

*/
const int MAXN = 103;
const int MAXE = 30003;
/* ��ʽǰ���� */
struct node{        //gragh node
    int u, v, w;
    int op;         //����߲����������߶�Ӧ����һ�����
    bool in_MST;    //�Ƿ�����С��������;
    int next;
}edge[MAXE];
int cnt, head[MAXN];
void Init(){
    cnt = 0;
    mem(head, -1);
}
void Add_edge(int u, int v, int w){     //��������
    edge[cnt].in_MST = false;
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    edge[cnt].op = cnt + 1;
    head[u] = cnt ++;
 
    edge[cnt].in_MST = false;
    edge[cnt].u = v;
    edge[cnt].v = u;
    edge[cnt].w = w;
    edge[cnt].next = head[v];
    edge[cnt].op = cnt - 1;
    head[v] = cnt ++;
}
/* ��ʽǰ���� */
 
struct prim_node{   //prim node
    int t;      //״̬�ڵ���
    int id;     //�ڼ�����
    int w;      //Ȩֵ
    friend bool operator < (prim_node n1, prim_node n2){
        return n1.w > n2.w;
    }
    void Init(int n){
        id = -1;
        t = n;
        w = sup;
    }
}dist[MAXN];
bool vis[MAXN];
priority_queue <prim_node, vector<prim_node> > Q;
int MST_NUM;
void Prim(int start, int n){    	//��ʼMST_NUM=0������ڲ���ͨ��ͼMST_NUM=0;
    mem(vis, 0);
    for (int i = 0; i <= n; i ++)
        dist[i].Init(i);
    while(!Q.empty())
        Q.pop();
    dist[start].w = 0;
    Q.push(dist[start]);
    while(!Q.empty()){
        prim_node tmp = Q.top();
        Q.pop();
        int u = tmp.t;
        int w = tmp.w;
        int id = tmp.id;
        if (vis[u]) continue;
        vis[u] = true;
        if (id != -1){      //ȷ����С�������ıߺ�Ȩֵ��
            edge[id].in_MST = true;
            edge[edge[id].op].in_MST = true;
            MST_NUM += w;
        }
        for (int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].v;
            int cost = edge[i].w;
            if (!vis[v] && dist[v].w > cost){
                dist[v].w = cost;
                dist[v].id = i;
                Q.push(dist[v]);
            }
        }
    }
}
int max_cost_on_MST[MAXN][MAXN];
bool used[MAXN];
void dfs(int s, int t, int maxnum){
    max_cost_on_MST[s][t] = maxnum;
    used[t] = 1;
    for (int i = head[s]; i != -1; i = edge[i].next){
        if (edge[i].in_MST == false)
            continue;
        int v = edge[i].v;
        if (!used[v])   dfs(s, v, max(maxnum, edge[i].w));
    }
}
int n, m;
void Second_MST(){
    Prim(1, n);
    int res = sup;
    //ö�ٲ�����С�������еı�
    for (int i = 1; i <= n; i ++){
        mem(used, 0);
        dfs(i, i, 0);
        for (int j = head[i]; j != -1; j = edge[j].next){
            int v = edge[j].v;
            if (edge[j].in_MST == false)
                res = min(res, MST_NUM + edge[j].w - max_cost_on_MST[i][v]);
        }
    }
    if (res == MST_NUM){
        printf("Not Unique!\n");
    }
    else{
        printf("%d\n", MST_NUM);
    }
}
int main(){
    int t;
    scanf("%d", &t);
    while(t --){
        MST_NUM = 0;
        Init();
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i ++){
            int a, b, l;
            scanf("%d %d %d", &a, &b, &l);
            Add_edge(a, b, l);
        }
        Second_MST();
    }
	return 0;
}
