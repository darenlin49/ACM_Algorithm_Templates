/* Bellman-Ford, O(VE), ֧�ָ�Ȩ������ֵ�ж��Ƿ��и��� */
struct node{
    int u;
    int v;
    int w;
}edge[maxm];
int dis[maxn];
int cnt;
void init(){
    cnt = 0;
}
void add(int u, int v, int w){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt++].w = w;
}
bool bellman_ford(int s){
    for(int i = 0; i < n; i++){
        dis[i] = oo;
    }
    dis[s] = 0;
    for(int i = 1; i < n; i ++){
		bool relax = false;		//�����̲����ɳ�ʱ���˳���һ���ܴ���Ż���Ч�ʿɱƽ�Dijkstra
        for(int j = 0; j < cnt; j++){
            int u = edge[j].u;
            int v = edge[j].v;
            int w = edge[j].w;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
				relax = true;
            }
        }
		if (!relax)
			break;
    }
	//�ж��Ƿ��и���
    for(int j = 0; j < cnt; j++){
        int u = edge[j].u;
        int v = edge[j].v;
        int w = edge[j].w;
        if(dis[v] > dis[u] + w){
            return false;
        }
    }
    return true;
}

/* 
	STL��+Dijkstra: O((V+E)logV) ��ʽǰ����ʵ��
	����ͼ�Ż�Ч��������
 */
const int MAXV = 405;
const int MAXE = 320005;
const int oo = 0x3fffffff;
struct node{
    int u, v, w;
    int next;
}edge[MAXE];
int cnt, head[MAXV];
void init(){
    mem(head, -1);
    cnt = 0;
}
void add(int u, int v, int w){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt ++;
    edge[cnt].v = u;
    edge[cnt].u = v;
    edge[cnt].w = w;
    edge[cnt].next = head[v];
    head[v] = cnt ++;
}
priority_queue <pair<int ,int>,vector<pair<int ,int> >,greater<pair<int,int> > > PQ;
int dist[MAXV];
void Dijkstra(int s,int n){
    for (int i=0;i<n;i++)
        dist[i]=oo;

    int vis[MAXV];
    memset(vis,0,sizeof(vis));

    dist[s]=0;
    while(!PQ.empty())
        PQ.pop();
    PQ.push(make_pair(dist[s],s));
    while(!PQ.empty()){
        int u=PQ.top().second;
        PQ.pop();
        if (!vis[u]){
            vis[u]=1;
            for (int i = head[u]; i != -1 ; i = edge[i].next){
				int v = edge[i].v;
				if (dist[v] > dist[u] + edge[i].w){
					dist[v] = dist[u] + edge[i].w;
					PQ.push(make_pair(dist[v], v));
				}
            }
        }
    }
}

/* Floyd-Warshall */
/* 
	Floyd-Warshall�㷨��Floyd-Warshall algorithm���ǽ���������������·����һ���㷨��������ȷ��������ͼ��Ȩ�����·�����⣬ͬʱҲ�����ڼ�������ͼ�Ĵ��ݱհ��� 
	Floyd-Warshall�㷨��ԭ���Ƕ�̬�滮��
		��D(i,j,k)Ϊ��i��j��ֻ��(1..k)�����еĽڵ�Ϊ�м�ڵ�����·���ĳ��ȡ�
		�����·��������k����D(i,j,k) = D(i,k,k-1) + D(k,j,k-1);
		�����·����������k����D(i,j,k) = D(i,j,k-1);
		��ˣ�D(i,j,k) = min(D(i,j,k-1), D(i,k,k-1) + D(k,j,k-1))��
	��ʵ���㷨�У�Ϊ�˽�Լ�ռ䣬����ֱ����ԭ���ռ��Ͻ��е����������ռ�ɽ�����ά��
*/
void Floyd(int n){
	for (int k = 1; k <= n; k ++){
        for (int i = 1; i <= n; i ++){
            for (int j = 1; j <= n; j ++){
                dis[i][j] = min(dis[i][j] ,dis[i][k] + dis[k][j]);
            }
        }
    }
}