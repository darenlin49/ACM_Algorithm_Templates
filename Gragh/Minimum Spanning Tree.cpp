/**
	Kruskal.
	算法描述：克鲁斯卡尔算法需要对图的边进行访问，所以克鲁斯卡尔算法的时间复杂度只和边又关系，可以证明其时间复杂度为O(ElogE)，适合稀疏图。
	算法过程：
		1.将图各边按照权值进行排序
		2.将图遍历一次，找出权值最小的边，（条件：此次找出的边不能和已加入最小生成树集合的边构成环），若符合条件，则加入最小生成树的集合中。不符合条件则继续遍历图，寻找下一个最小权值的边。
		3.递归重复步骤1，直到找出n-1条边为止（设图有n个结点，则最小生成树的边数应为n-1条），算法结束。得到的就是此图的最小生成树。
*/
const int MAXN = 505;
const int MAXE = 250005;
int res, maxe;
struct Disjoint_Sets{
    int father, ranks;
}S[MAXN];
void init(){
    res = 0;
    maxe = 0;
    for (int i = 0; i < MAXN; i ++)
        S[i].father = i, S[i].ranks = 0;
}
int Father(int x){
    if (S[x].father == x){
        return x;
    }
    else{
        S[x].father = Father(S[x].father);     //Path compression
        return S[x].father;
    }
}
bool Union(int x, int y, int w){
    int fx = Father(x), fy = Father(y);
    if (fx == fy){
        return false;
    }
    else{                                       //Rank merge
        res += w;						//return sum of the edges of the MST.
        maxe = max(maxe, w);			//return max edge of the edges of the MST.
        if (S[fx].ranks > S[fy].ranks){
            S[fy].father = fx;
        }
        else{
            S[fx].father = fy;
            if (S[fx].ranks == S[fy].ranks){
                ++ S[fy].ranks;
            }
        }
        return true;
    }
}
struct node{
    int u, v, w;
}edge[MAXE];
int cnt;
bool cmp (const node n1, const node n2){
    return n1.w < n2.w;
}
void add(int u, int v, int w){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt ++].w = w;
    return ;
}
int main(){
    int t, n;
    scanf("%d", &t);
    while(t --){
        cnt = 0;
        init();
        scanf("%d", &n);
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n; j ++){
                int tmp;
                scanf("%d", &tmp);
                if (i > j)
                add(i, j, tmp);
            }
        }
        sort(edge, edge+cnt, cmp);
		int num = 0;
        for (int i = 0; i < cnt && num < n - 1; i ++){
            if (Union(edge[i].u, edge[i].v, edge[i].w)){
                num ++;
            }
        }
		//Strictly , only when (num == n - 1) dose the gragh contain a MST.
        printf("%d\n", maxe);
    }
	return 0;
}


/**
	Prim.O((V+E)logV)
	
	//稠密图中优化效果不明显
*/
const int MAX = 305;
struct edge{
    int v, w;
    edge(){
    }
    edge(int _v, int _w){
        v = _v;
        w = _w;
    }
};
struct MST{
    vector <edge> adj[MAX];
    int dist[MAX];
    bool vis[MAX];
    priority_queue <pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > PQ;
    void init(int n){
        for (int i = 0; i <= n; i ++){
            adj[i].clear();
            vis[i] = false;
        }
    }
    void add_edge(int u, int v, int w){
        adj[u].push_back(edge(v, w));
        adj[v].push_back(edge(u, w));
    }
    int solve(int s, int n){
        for (int i = 0; i <= n; i ++)   dist[i] = 0x3fffffff;
        while(!PQ.empty())  PQ.pop();
        dist[s] = 0;
        PQ.push(make_pair(0, s));
        while(!PQ.empty()){
            int u = PQ.top().second;
            PQ.pop();
            vis[u] = true;
            for (int i = 0; i < (int)adj[u].size(); i ++){
                int v = adj[u][i].v, w = adj[u][i].w;
                if (!vis[v] && dist[v] > w){
                    dist[v] = w;
                    PQ.push(make_pair(w, v));
                }
            }
        }
        int res = 0;
        for (int i = 1; i <= n; i ++)   res += dist[i];
        return res;
    }
}prim;