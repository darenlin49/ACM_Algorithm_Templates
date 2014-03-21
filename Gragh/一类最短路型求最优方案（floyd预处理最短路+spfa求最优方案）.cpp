/*
	[HDU4571]给定N个点，每个点有一个停留所需的时间Ci，和停留能够获得的满意度Si，有M条边，每条边代表着两个点走动所需的时间ti，现在问在规定的T时间内从指定的一点S到E能够获得的最大的满意度是多少？要求停留的点的满意度要依次上升，并且每个点可以选择路过和停留。
	[分析]一开始我的想法是建立分层图，把每个点u分成两层，一个u表示停留，一个u’ (u+n) 表示路过该点。然后建立相应的边，注意当两个边都停留时要根据满意度大小建立从小到大的有向边。需要连的边有：u->v or v -> u, u->v’, u’ -> v, v -> u’, v’ -> u, v’ -> u’, u’ -> v’。注意用一个”超级源点”连向原来的源点s和s’(这样才是单源)，然后我们做一遍二维SPFA（也就是二维Bellman-Ford）dist[time][node]表示time时间到node节点能获得的最大满意度，最后在dist[0..T][e]和dist[0..T][e+n]中找最大值就是答案。
	但是超时了T_T。。。然后看了别人的题解，很漂亮。（后来对拍时发现我的程序确实是错的，不能保证从访问节点的满意度递增。。。）

	先用floyd预处理出两两之间的最短距离，然后再加边，这样就可以不用处理路过节点的情况了（很精彩~想想是不是？~），所以加边时只需要考虑两个点都停留，加一条u->v or v->u即可，大大减少了边的复杂度，而且因为图中只有停留点的有向边，就保证了访问节点满意度的递增。然后又TLE了。。。跟网上的程序对了半天交了20多次终于发现是链式前向星超时了。。。。。。于是换成邻接表就过了
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