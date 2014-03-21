/*
	[HDU4571]����N���㣬ÿ������һ��ͣ�������ʱ��Ci����ͣ���ܹ���õ������Si����M���ߣ�ÿ���ߴ������������߶������ʱ��ti���������ڹ涨��Tʱ���ڴ�ָ����һ��S��E�ܹ���õ�����������Ƕ��٣�Ҫ��ͣ���ĵ�������Ҫ��������������ÿ�������ѡ��·����ͣ����
	[����]һ��ʼ�ҵ��뷨�ǽ����ֲ�ͼ����ÿ����u�ֳ����㣬һ��u��ʾͣ����һ��u�� (u+n) ��ʾ·���õ㡣Ȼ������Ӧ�ıߣ�ע�⵱�����߶�ͣ��ʱҪ��������ȴ�С������С���������ߡ���Ҫ���ı��У�u->v or v -> u, u->v��, u�� -> v, v -> u��, v�� -> u, v�� -> u��, u�� -> v����ע����һ��������Դ�㡱����ԭ����Դ��s��s��(�������ǵ�Դ)��Ȼ��������һ���άSPFA��Ҳ���Ƕ�άBellman-Ford��dist[time][node]��ʾtimeʱ�䵽node�ڵ��ܻ�õ��������ȣ������dist[0..T][e]��dist[0..T][e+n]�������ֵ���Ǵ𰸡�
	���ǳ�ʱ��T_T������Ȼ���˱��˵���⣬��Ư��������������ʱ�����ҵĳ���ȷʵ�Ǵ�ģ����ܱ�֤�ӷ��ʽڵ������ȵ�����������

	����floydԤ���������֮�����̾��룬Ȼ���ټӱߣ������Ϳ��Բ��ô���·���ڵ������ˣ��ܾ���~�����ǲ��ǣ�~�������Լӱ�ʱֻ��Ҫ���������㶼ͣ������һ��u->v or v->u���ɣ��������˱ߵĸ��Ӷȣ�������Ϊͼ��ֻ��ͣ���������ߣ��ͱ�֤�˷��ʽڵ�����ȵĵ�����Ȼ����TLE�ˡ����������ϵĳ�����˰��콻��20������ڷ�������ʽǰ���ǳ�ʱ�ˡ��������������ǻ����ڽӱ�͹���
*/
const int sup = 0x3fffffff;
const int MAXV = 105;
const int MAXE = 2015;
int cost[MAXV], value[MAXV];
struct node{
    int v, t;
    node(int _v, int _t){
        v = _v;
        t = _t;
    }
};
vector <node> arc[MAXV];
int mindis[MAXV][MAXV];
void init(int n){
    value[n+1] = 0;
    for (int i = 0; i <= n+1; i ++){
        arc[i].clear();
        for (int j = 0; j <= n+1; j ++){
            if (i == j) mindis[i][i] = 0;
            mindis[i][j] = sup;
        }
    }
}
inline void add(int u, int v, int t){
    arc[u].push_back(node(v, t));
    return ;
}
struct status{
    int t;  //time
    int v;  //nodes
    status(int _t, int _v){
        t = _t;
        v = _v;
    }
};
int dist[305][MAXV];
bool inq[305][MAXV];
queue <status> Q;
inline int spfa(int n, int t, int s, int e){
    for (int i = 0; i <= t; i ++)
        for (int j = 0; j <= n+1; j ++){
            dist[i][j] = 0;
            inq[i][j] = false;
        }
    while(!Q.empty())
        Q.pop();
 
    dist[0][s] = 0;
    inq[0][s] = 1;
    Q.push(status(0, s));
 
    while(!Q.empty()){
        int u = Q.front().v;
        int nowtime = Q.front().t;
        Q.pop();
        inq[nowtime][u] = 0;
 
        for (int i = 0; i < (int)arc[u].size(); i ++){
            int v = arc[u][i].v;
            int time = nowtime + arc[u][i].t;
            if (time > t)   continue;
            if (dist[time][v] < dist[nowtime][u] + value[v]){
                dist[time][v] = dist[nowtime][u] + value[v];
                if (!inq[time][v]){
                    Q.push(status(time, v));
                    inq[time][v] = 1;
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i <= t; i ++){
        res = max(res, dist[i][e]);
        res = max(res, dist[i][n+1]);
    }
    return res;
}
inline void floyd(int n){
    for (int k = 0; k < n; k ++){
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n; j ++){
                mindis[i][j] = min(mindis[i][j], mindis[i][k]+mindis[k][j]);
            }
        }
    }
    return ;
}
int main(){
    int w;
    scanf("%d", &w);
    for (int o = 1; o <= w; o ++){
        int n, m, t, s, e;
        scanf("%d %d %d %d %d", &n, &m, &t, &s, &e);
        init(n);
        for (int i = 0; i < n; i ++){
            scanf("%d", &cost[i]);
        }
        for (int i = 0; i < n; i ++){
            scanf("%d", &value[i]);
        }
        for (int i = 0; i < m; i ++){
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            mindis[u][v] = mindis[v][u] = min(mindis[v][u], c);
        }
        floyd(n);
        for (int u = 0; u < n; u ++){
            for (int v = u + 1; v < n; v ++){
                if (mindis[u][v] != sup){
                    if (value[u] < value[v])
                        add(u, v, mindis[u][v]+cost[v]);
                    else if (value[v] < value[u])
                        add(v, u, mindis[u][v]+cost[u]);
                }
            }
        }
        add(n, s, cost[s]);
        for (int i = 0; i < n; i ++){
            if (i != s && mindis[s][i] != sup)
                add(n, i, mindis[s][i]+cost[i]);
            if (i != e && mindis[e][i] != sup)
                add(i, n+1, mindis[e][i]);
        }
        printf("Case #%d:\n", o);
        printf("%d\n", spfa(n, t, n, e));
    }
    return 0;
}