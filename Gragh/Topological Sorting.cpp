/* 
	�������򣬲��ұ�֤�������ֵ�����С(BFS���ȶ���ʵ��)
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
    //������Ψһ(һ����)����1��������Ψһ����0��������ì��(���ڻ�)����-1.
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