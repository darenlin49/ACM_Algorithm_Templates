/*
	[MaxFlow����Edmonds_Karp]ÿ����bfs����dfsѰ���������·������,���۵�ʱ�临�Ӷ���O(V*E^2)
	PS:��PKU��1459 Power Network(��Դ���ģ����)����ģ��:329MS
*/
#define sup 0x3fffffff
const int MAXN = 105;
struct EK{
    int flow[MAXN][MAXN];			//�����������
    int pre[MAXN];					//������·
    queue <int> Q;
    void init(){
        mem(flow, 0);
    }
    void addflow(int u, int v, int c){
        flow[u][v] = c;
    }
    bool aug(int s, int t, int n){
        mem(pre, 0);
        while(!Q.empty())   Q.pop();
        Q.push(s);
        pre[s] = s;
        while(!Q.empty()){
            int u = Q.front();
            if (u == t) return true;
            Q.pop();
            for (int i = 1; i <= n; i ++){
                if (pre[i] == 0 && flow[u][i] > 0){
                    Q.push(i);  pre[i] = u;
                }
            }
        }
        return false;
    }
    int solve(int s, int t, int n){
        int maxflow = 0;
        while(aug(s, t, n)){
            int v = t;
            int augflow = sup;
            while(pre[v] != v){
                int u = pre[v];
                augflow = min(augflow, flow[u][v]);
                v = u;
            }
            v = t;
            while(pre[v] != v){
                int u = pre[v];
                flow[u][v] -= augflow;
                flow[v][u] += augflow;
                v = u;
            }
            maxflow += augflow;
        }
        return maxflow;
    }
}ek;
int flow[MAXN][MAXN];
int main(){
    int n, np, nc, m;
    while(scanf("%d %d %d %d", &n, &np, &nc, &m) != EOF){
        ek.init();
        for (int i = 0; i < m; i ++){
            int u, v, f;
            scanf("%*1s%d%*1s%d%*1s%d", &u, &v, &f);
            ek.addflow(u+1, v+1, f);
        }
        for (int i = 0; i < np; i ++){
            int u, p;
            scanf("%*1s%d%*1s%d", &u, &p);
            ek.addflow(n+1, u+1, p);     //����Դ��
        }
        for (int i = 0; i < nc; i ++){
            int u, c;
            scanf("%*1s%d%*1s%d", &u, &c);
            ek.addflow(u+1, n+2, c);     //�������
        }
        printf("%d\n", ek.solve(n+1, n+2, n+2));
    }
	return 0;
}
