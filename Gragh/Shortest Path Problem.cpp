/* Bellman-Ford, O(VE), 支持负权、返回值判断是否有负环 */
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
		bool relax = false;		//当过程不再松弛时便退出，一个很大的优化，效率可逼近Dijkstra
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
	//判断是否有负环
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
	STL堆+Dijkstra: O((V+E)logV) 链式前向星实现
	稠密图优化效果不明显
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
	Floyd-Warshall算法（Floyd-Warshall algorithm）是解决任意两点间的最短路径的一种算法，可以正确处理有向图或负权的最短路径问题，同时也被用于计算有向图的传递闭包。 
	Floyd-Warshall算法的原理是动态规划。
		设D(i,j,k)为从i到j的只以(1..k)集合中的节点为中间节点的最短路径的长度。
		若最短路径经过点k，则D(i,j,k) = D(i,k,k-1) + D(k,j,k-1);
		若最短路径不经过点k，则D(i,j,k) = D(i,j,k-1);
		因此，D(i,j,k) = min(D(i,j,k-1), D(i,k,k-1) + D(k,j,k-1))。
	在实际算法中，为了节约空间，可以直接在原来空间上进行迭代，这样空间可降至二维。
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