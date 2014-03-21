/*
[POJ  3694]һ������ͼ�������ر�.q������,ÿ������һ���ߣ���ѯ����������ͼ��ʣ�¶�����.

[����]�Ȱ�ͼ��һ�α�˫��ͨ����(BCC)Ȼ�����㣬��Ϊͬһ˫��ͨ������û���ţ��ӱ�û��Ӱ�졣һ������Ҫ�����ʾ��ǣ�һ��ͼ��һ�α�˫��ͨ��������󽫱��һ��������ɭ�֣��������е�ÿ���߶����ţ�����Ϊ������˵���еĵ㶼�б����ţ����������������һ������
��Ȼ������ÿ���һ���ߣ��ͻ��γ�һ��������������еı߽��������ţ��������ǹ����µı�˫��ͨ��������������ÿ�������м�ȥ��Щ�ߣ�������������һ���㡣
��һ����ô�������мӱ�(u,v)���γɵĻ���
	���ǿ������u,v��LCA��Ȼ�󻷾���v->LCA(u,v)->u>(u,v)->v.
�ڶ�����ô���㣿
	��ǰһֱ�����ǡ���̬���㡱��������һ���BCC��ͼ�Ľṹ�Ͳ����ˣ���ʱ���ǿ��������ÿ����������BCC(bcc[i])����BCC�ı������������ĵ㡣������Ƕ�̬�ؼӱߣ���ÿ�ζ�Ҫ�޸�ԭBCC�����еĵ����BCC������ֱ���������в�ͨ�����������ǲ��Ƿ��������񡭡����鼯���ԣ������ò��鼯ά��bcc[]���������������ѧ��������Ҫ�����ƣ��ò��鼯ά����̬�ӱߵ����㡣
��Ȼ����������û���õ�bcc[],��Ϊ����LCAʱ�����õ����صķ���������level[]��ʾÿ���ڵ����ȣ�������ͬʱ������������Ľڵ�������LCA(u,v) = LCA(u, father[v]) ���������ͬʱ������һ������LCA(u, v) = LCA(father[u], father[v]) ����ֱ����������ͬ�������ַ����ĺô��ǿ���һ����LCAһ�����㡣��ô���Ǿ���Ҫһ��father[]��ά���ڵ�ĸ��ڵ㡣�������ǾͲ���Ҫbcc[]�ˣ�ֱ���ò��鼯ά��father[]����������ʾ���㼰����BCC��
*/

const int MAXV = 100005;
const int MAXE = 400005;
struct node{
    int u, v;
    int next;
    int opp;                    //��һ������߲����������ߣ���Ӧ����߱��
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
int level[MAXV];
int father[MAXV];               //��ĸ��ڵ�,������ɽ��(����ڵ���),Ҳ���ڲ��鼯����
int bridge_num, bridge[MAXV];   //��Ǹñ��ǲ�����,�������ŵ��ӽڵ��ʾ
bool vis_arc[MAXE];             //һ���������(���������)ֻ����һ�Σ�
int find(int u){                //���鼯 + ·��ѹ����������, ����ϲ���ʱ���ӽڵ�ĸ�����Ϊ���ڵ�
    if(father[u] != u)
        return father[u] = find(father[u]);
    else
        return u;
}
void tarjan(int u, int l){
    dfn[u] = low[u] = ++id;
    level[u] = l;
    for (int i = head[u]; i != -1; i = arc[i].next){
        int v = arc[i].v;
        if (vis_arc[i]) continue;
        vis_arc[i] = vis_arc[arc[i].opp] = 1;
        if (!dfn[v]){
            father[v] = u;
            tarjan(v, l+1);
            low[u] = min(low[u], low[v]);
        }
        else{
            low[u] = min(low[u], dfn[v]);
        }
        if (dfn[u] < low[v]){
            bridge[v] = 1;
            bridge_num ++;
        }
        else{
            int x = find(u);
            int y = find(v);
            if (x != y)
                father[y] = x;
        }
    }
}
void solve(int n){
    id  = bridge_num = 0;
    mem(dfn, 0);
    mem(low, 0);
    mem(level, 0);
    mem(bridge, 0);
    mem(vis_arc, 0);
    for (int i = 0; i <= n; i ++)
        father[i] = i;
    for (int i = 1; i <= n; i ++){
        if (!dfn[i])
            tarjan(1, 1);
    }
    return ;
}
vector <int> path;
int lca(int u, int v){
    path.clear();
    if (level[u] > level[v])    swap(u, v);
    while(u != v){
        while(level[u] != level[v]){
            if(level[v] > level[u]){
                if (bridge[v]){
                    bridge[v] = 0;
                    bridge_num --;
                }
                path.push_back(v);
                v = father[v];
            }
            else{
                if (bridge[u]){
                    bridge[u] = 0;
                    bridge_num --;
                }
                path.push_back(u);
                u = father[u];
            }
        }
        while(u != v){
            if (bridge[v]){
                bridge[v] = 0;
                bridge_num --;
            }
            if (bridge[u]){
                bridge[u] = 0;
                bridge_num --;
            }
            path.push_back(u);
            path.push_back(v);
            v = father[v];
            u = father[u];
        }
    }
    int lc = u;
    //�Ѽӱߺ�Ļ��ò��鼯����һ����
    for (int i = 0; i < (int)path.size(); i ++){
        int u = path[i];
        father[u] = lc;
    }
    return bridge_num;
}
int main(){
    int n, m, t = 1;
    while(scanf("%d %d", &n, &m) != EOF){
        if (n + m == 0)
            break;
        init();
        for (int i = 0; i < m; i ++){
            int u, v;
            scanf("%d %d", &u, &v);
            add(u, v);
        }
        solve(n);
        int q;
        scanf("%d", &q);
        printf("Case %d:\n", t);
        for (int i = 0; i < q; i ++){
            int u, v;
            scanf("%d %d", &u, &v);
            printf("%d\n", lca(u, v));
        }
        puts("");
        t ++;
    }
	return 0;
}