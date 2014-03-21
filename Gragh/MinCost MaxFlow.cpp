/**
	����С���������1.0�����������G��һ���������flow, ʹ�����ܷ�����С.(֧�ָ�Ȩ)(������ = ��λ������ * ����)
	����С����·�㷨����SPFAѰ����̷�������·.
	��ʱ�临�Ӷȡ�O( F*SPFA(V,E) )
	����չ��
		�������ΪFʱ����С������, ֻ���һ������Դ��ͳ����������ԭ����Դ���, ����ΪF, ����Ϊ0.
		���������������ѱ�Ȩȡ������.
**/
const int MAXV = 1005;
const int MAXE = 20005;
const int oo = 0x3fffffff;

template <class NodesType>
struct Nodes{
    NodesType dist;
    int pre, head;      		//pre��ǰ����, head��ǰ����
    bool visit;
};
template <class EdgesType>
struct Edges{
    int u, v, next;
    EdgesType cost, flow;
};
template <class T>
struct MinCostMaxFlow{
    Nodes <T> node[MAXV];
    Edges <T> arc[2*MAXE];
    int vn, en;
    void init(int n){
        vn = n;
        en = 0;
        for (int i = 0; i <= n; i ++){
            node[i].head = -1;
        }
    }
    void insert_flow(int u, int v, T flow, T cost){
        arc[en].u = u;
        arc[en].v = v;
        arc[en].flow = flow;
        arc[en].cost = cost;
        arc[en].next = node[u].head;
        node[u].head = en ++;
        arc[en].v = u;
        arc[en].u = v;
        arc[en].flow = 0;
        arc[en].cost = -cost;
        arc[en].next = node[v].head;
        node[v].head = en ++;
    }
	void print_edges(){
		for (int i = 0; i < en; i ++){
			printf("u = %d v = %d flow = %d cost = %d\n", arc[i].u, arc[i].v, arc[i].flow, arc[i].cost);
		}
    }
    queue <int> q;
    bool spfa(int s, int t){
        for (int i = 1; i <= vn; i ++){
            node[i].dist = oo;
            node[i].pre = -1;
            node[i].visit = false;
        }
        node[s].dist = 0;
        node[s].visit = true;
        q.push(s);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            node[u].visit = false;
            for (int i = node[u].head; i != -1; i = arc[i].next){
                int v = arc[i].v;
                if (arc[i].flow > 0 && node[v].dist > node[u].dist + arc[i].cost){
                    node[v].dist = node[u].dist + arc[i].cost;
                    node[v].pre = i;
                    if (!node[v].visit){
                        node[v].visit = true;
                        q.push(v);
                    }
                }
            }
        }
        if (node[t].pre == -1)
            return 0;
        else
            return 1;
    }
    T solve(int s, int t, T &mincost){
        mincost = 0;
        T maxflow = 0;
        while(spfa(s, t)){
            T minflow = oo;
            for (int i = node[t].pre; i != -1; i = node[arc[i].u].pre){
                minflow = min(minflow, arc[i].flow);
            }
            for (int i = node[t].pre; i != -1; i = node[arc[i].u].pre){
                arc[i].flow -= minflow;
                arc[i^1].flow += minflow;
                mincost += arc[i].cost * minflow;
            }
            maxflow += minflow;
        }
        return maxflow;
    }
};
MinCostMaxFlow <int> mcmf;