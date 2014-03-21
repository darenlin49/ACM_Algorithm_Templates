/* 
	拓扑排序，并且保证顶点标号字典序最小(BFS优先队列实现)
*/
const int MAXV = 1002;
const int MAXE = 10002;
struct Toposort{
    int ind[MAXV];
	int head[MAXV], cnt;
    vector <int> top_res;
    priority_queue <int , vector<int> , greater<int> > PQ;
    struct node{
        int u, v;
        int next;
    }arc[MAXE];
    void init(){
        cnt = 0;
        mem(head, -1);
    }
    void add(int u, int v){
        arc[cnt].u = u;
        arc[cnt].v = v;
        arc[cnt].next = head[u];
        head[u] = cnt ++;
    }
    void cal_indegree(){
        mem(ind, 0);
        for (int i = 0; i < cnt; i ++){
            ind[arc[i].v] ++;
        }
        return ;
    }
    //拓扑序唯一(一条链)返回1，拓扑序不唯一返回0，拓扑序矛盾(存在环)返回-1.
    bool topsort(int n){
        while(!PQ.empty())
            PQ.pop();
        top_res.clear();
        cal_indegree();
        for (int i = 1; i <= n; i ++)
            if (ind[i] == 0)
                PQ.push(i);
        while(!PQ.empty()){
            if (PQ.size() > 1)
                return 0;
            int u = PQ.top();
            PQ.pop();
            top_res.push_back(u);
            for (int i = head[u]; i != -1; i = arc[i].next){
                if ((-- ind[arc[i].v]) == 0)
                    PQ.push(arc[i].v);
            }
        }
        if (top_res.size() < n)
            return -1;
        return 1;
    }
}T;