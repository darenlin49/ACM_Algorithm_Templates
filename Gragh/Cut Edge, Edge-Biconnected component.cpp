/**
	POJ 3352 && POJ 3177 ���⣺�Ӽ�����ԭͼ���ܱ�ɱ�˫��ͨ����
	[����]��ͼ�����������������DFS(u)Ϊu�������������¼��Ϊ�����б��������Ĵ���š�����Low(u)Ϊu��u����������ͨ���Ǹ��ӱ�׷�ݵ�������Ľڵ㣬��DFS�����С�Ľڵ㡣���ݶ��壬���У�Low(u)=Min {DFS(u),DFS(v)|(u,v)Ϊ�����(�ȼ���DFS(v)<DFS(u)��v��Ϊu�ĸ��׽ڵ�),Low(v)|(u,v)Ϊ��֦��}
	
	[����]һ�������(u,v)���ţ����ҽ���(u,v)Ϊ��֦�ߣ�������DFS(u)<Low(v)
	[���˫��ͨ��֧]ֻ����������е����Ժ󣬰��ű�ɾ����ԭͼ����˶����ͨ�飬��ÿ����ͨ�����һ����˫��ͨ��֧���Ų������κ�һ����˫��ͨ��֧������ıߺ�ÿ�����㶼������ֻ����һ����˫��ͨ��֧��
	
	[ע]�ر߶����ߺͱ���ͨ������Ӱ�죬�رߴ���������DFSʱ���ÿ���߼��䷴����Ƿ񱻷��ʹ��������߷��ʣ����������ж϶��㣨������ʣ���
**/

/* ���ر� */
const int MAXV = 5005;
const int MAXE = 20005;
struct node{
    int u, v;
    int next;
    int opp;        //��һ������߲����������ߣ���Ӧ����߱��
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
int bridge[MAXE];                //��Ǹñ��ǲ�����
void tarjan(int u, int father){
    dfn[u] = low[u] = ++id;
    for (int i = head[u]; i != -1; i = arc[i].next){
        int v = arc[i].v;
        if (v == father)    continue;
        if (!dfn[v]){
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v]){
                bridge[i] = 1;					//�������������߱�ʾ�����
                bridge[arc[i].opp] = 1;
            }
        }
        else{
            low[u] = min(low[u], dfn[v]);
        }
    }
}
bool vis[MAXV];
int bcc_num;					//��˫��ͨ������
int bcc[MAXV];                  //��ǵ������ĸ���˫��ͨ��֧
void fill(int u){				//��ɾ���ŵ�ͼ�ж�ÿ����Ⱦɫ��ȷ���������ı�˫��ͨ����
    vis[u] = 1;
    bcc[u] = bcc_num;
    for (int i = head[u]; i != -1; i = arc[i].next){
        if (bridge[i])  continue;
        int v = arc[i].v;
        if (!vis[v])
            fill(v);
    }
}
int deg[MAXV];                  //��������ͼ�ڵ���������ڼ���Ҷ�ӽ����
bool vis_arc[MAXE];             //ĳ�����(���������)ֻ����һ�Σ�
int find_bcc(int n){			//���ػ�����Ӽ����߲��ܳ�Ϊ��˫��ͨͼ
    mem(vis, 0);
    mem(deg, 0);
    //ȷ��ÿ����������˫��ͨ����
    for (int i = 1; i <= n; i ++){
        if (!vis[i]){
            ++ bcc_num;
            fill(i);
        }
    }
    mem(vis_arc, 0);
    //���㻹���������߲��ܹ���˫��ͨͼ
    for (int i = 0; i < cnt; i ++){
        if (!vis_arc[i]){
			//����һ��Ҫע��������ʱһ�������ֻ����һ��
            vis_arc[i] = vis_arc[arc[i].opp] = 1;
            int u = arc[i].u;
            int v = arc[i].v;
            if (bcc[u] != bcc[v]){
                deg[bcc[u]] ++;
                deg[bcc[v]] ++;
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= bcc_num; i ++){
        if (deg[i] == 1)
            res ++;
    }
    return (res+1)/2;
}
void solve(int n){
    id = bcc_num =0;
    mem(dfn, 0);
    mem(low, 0);
    mem(bridge, 0);
    for (int i = 1; i <= n; i ++){
        if (!dfn[i])
            tarjan(1, 0);
    }
    printf("%d\n", find_bcc(n));
    return ;
}

int main(){
    int F,R;
    while(scanf("%d %d", &F, &R) != EOF){
        init();
        for (int i = 0; i < R; i ++){
            int u, v;
            scanf("%d %d", &u, &v);
            add(u, v);
        }
        solve(F);
    }
	return 0;
}


/* ���ر�BCC������DFS */
const int MAXV = 200005;
const int MAXE = 2000005;
struct node{
    int u, v;
    int next;
    bool bridge;
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
    arc[cnt].bridge = false;
    head[u] = cnt ++;
    arc[cnt].u = v;
    arc[cnt].v = u;
    arc[cnt].next = head[v];
    arc[cnt].bridge = false;
    head[v] = cnt ++;
    return ;
}
int id, dfn[MAXV], low[MAXV];
int bridge_num;
bool vis_arc[MAXE];              			//һ���������(���������)ֻ����һ�Σ�
void tarjan(int u){
    dfn[u] = low[u] = ++ id;
    for (int i = head[u]; i != -1; i = arc[i].next){
        if (vis_arc[i]) continue;
        int v = arc[i].v;
        vis_arc[i] = vis_arc[i^1] = 1;		//���ر�
        if (!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v]){
                arc[i].bridge = true;
                arc[i^1].bridge = true;
                bridge_num ++;
            }
        }
        else{
            low[u] = min(low[u], dfn[v]);
        }
    }
}
int bcc_num;
bool vis[MAXV];
int mark[MAXV];                  //��ǵ������ĸ���˫��ͨ��֧
vector <int> bcc[MAXV];

void fill(int u){
    bcc[bcc_num].push_back(u);
    mark[u] = bcc_num;
    for (int i = head[u]; i != -1; i = arc[i].next){
        if (arc[i].bridge)  continue;
        int v = arc[i].v;
        if (mark[v] == 0)
            fill(v);
    }
}
void find_bcc(int n){
    mem(vis, 0);
    mem(mark, 0);
    //ȷ��ÿ����������˫��ͨ����
    for (int i = 1; i <= n; i ++){
        if (mark[i] == 0){
            ++ bcc_num;
            bcc[bcc_num].clear();
            fill(i);
        }
    }
    return ;
}
void solve(int n){
    id = bcc_num = bridge_num = 0;
    mem(dfn, 0);
    mem(low, 0);
    mem(vis_arc, 0);
    for (int i = 1; i <= n; i ++){
        if (!dfn[i])
            tarjan(i);
    }
    find_bcc(n);
    return ;
}
int main(){
	return 0;
}